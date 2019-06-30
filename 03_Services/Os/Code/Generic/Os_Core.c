/*-------------------------------------------------------------------------------------------------------------------*/
/**
 *    \file       Os_Core.c
 *    \author     Nicolae-Bogdan Bacrau
 *    \brief      Implements the OS scheduling algorithm which activates all the configured tasks. Once started,
 *                the OS cannot be stopped. The function that starts the OS never returns.
 */
/*-------------------------------------------------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------------------------------------------------*/
/*                                                     Inclusions                                                    */
/*-------------------------------------------------------------------------------------------------------------------*/

#include "Os_Core.h"
#include "Os_Measurements.h"
#include "Os_Cfg.h"
#include "Os_Interrupts_Cfg.h"
#include "RegInit.h"
/*-------------------------------------------------------------------------------------------------------------------*/
/*                                             Definition Of Local Macros                                            */
/*-------------------------------------------------------------------------------------------------------------------*/

#if (STD_OFF == OS_USE_FAST_TASK) && (STD_OFF == OS_USE_SLOW_TASKS)
#error "Wrong OS configuration. Activate OS_USE_FAST_TASK or OS_USE_SLOW_TASKS."
#endif

/** \brief  Definition of modulus difference between two unsigned values. */
#define OS_MOD_DIFF(Modulus, New, Old)          ((((Modulus) - (Old)) + (New)) % (Modulus))

/** \brief  Function-like macro to compute the delay between two adjacent slow task activation timestamps. */
#define OS_SCH_TABLE_DELAY(tPrevPt, tNextPt)    (OS_MOD_DIFF(OS_SCHEDULE_TABLE_TIME_WINDOW, \
                                                            (Os_gkat_ScheduleTable)[(tNextPt)].t_ActivationTimestamp, \
                                                            (Os_gkat_ScheduleTable)[(tPrevPt)].t_ActivationTimestamp))

/*-------------------------------------------------------------------------------------------------------------------*/
/*                                           Definition Of Local Data Types                                          */
/*-------------------------------------------------------------------------------------------------------------------*/

/** \brief  Type definition for the state of the fast task. */
typedef struct
{
   /** \brief  The time (in ticks) of the last activation of the fast task. */
   TickType t_LastActivation;

   /** \brief  The time (in ticks) from the last activation until the next scheduled activation of the fast task. */
   TickType t_ScheduledActivation;

   /** \brief  The time (in ticks) of the cumulated delay of the fast task. */
   TickType t_CumulatedDelay;
} Os_FastTaskStateType;

/** \brief  Type definition for the state of the schedule table. */
typedef struct
{
   /** \brief  The ID of the last activated slow task. */
   uint8 t_LastSlowTaskId;

   /** \brief  The ID of the slow task that is next in the activation list. */
   uint8 t_NextSlowTaskId;

   /** \brief  The time (in ticks) of the last activation of a slow task. */
   TickType t_LastActivation;

   /** \brief  The time (in ticks) from the last activation until the next scheduled activation. */
   TickType t_ScheduledActivation;

   /** \brief  The time (in ticks) of the cumulated delay of the schedule table. */
   TickType t_CumulatedDelay;
} Os_ScheduleTableStateType;

/*-------------------------------------------------------------------------------------------------------------------*/
/*                                           Declaration Of Local Variables                                          */
/*-------------------------------------------------------------------------------------------------------------------*/

#if (STD_ON == OS_USE_FAST_TASK)
/** \brief  Variable containing the dynamic state used for the fast task activation. */
static Os_FastTaskStateType Os_t_FastTaskState;
#endif

#if (STD_ON == OS_USE_SLOW_TASKS)
/** \brief  Variable containing the dynamic state of the schedule table for slow tasks activation. */
static Os_ScheduleTableStateType Os_t_ScheduleTableState;
#endif

/*-------------------------------------------------------------------------------------------------------------------*/
/*                                          Declaration Of Global Variables                                          */
/*-------------------------------------------------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------------------------------------------------*/
/*                                           Declaration Of Local Constants                                          */
/*-------------------------------------------------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------------------------------------------------*/
/*                                          Declaration Of Global Constants                                          */
/*-------------------------------------------------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------------------------------------------------*/
/*                                           Declaration Of Local Functions                                          */
/*-------------------------------------------------------------------------------------------------------------------*/

static void Os_v_Init(void);
static void Os_v_RunScheduler(void);

/*-------------------------------------------------------------------------------------------------------------------*/
/*                                         Implementation Of Local Functions                                         */
/*-------------------------------------------------------------------------------------------------------------------*/

/**
 * \brief      Initializes the OS timer configuration registers, global variables that are used in the scheduling
 *             algorithm and enables the OS timer.
 * \param      -
 * \return     -
 */
static void Os_v_Init(void)
{
   TickType t_TimerValue;

   /* Configures and starts the hardware OS timer. */
   OS_TIMER_REGISTERS_INIT();

   /* Read the value that the counter starts with for setting it up as the last activation for both the fast task and
    * slow tasks. */
   t_TimerValue = (TickType) *Os_gkt_TimerCntReg;

#if (STD_ON == OS_USE_SLOW_TASKS)
   Os_t_ScheduleTableState.t_LastActivation = t_TimerValue;
   /* Initially, there is no cumulated delay of the schedule table. */
   Os_t_ScheduleTableState.t_CumulatedDelay = (TickType) 0;

   /* The first run of the schedule table is similar to a new run in which the last slow task activation took place and
    * the next slow task is the first one. */
   Os_t_ScheduleTableState.t_LastSlowTaskId = OS_SCHEDULE_TABLE_NR_OF_ACTIVATIONS - 1U;
   Os_t_ScheduleTableState.t_NextSlowTaskId = 0U;

   /* The initial scheduled activation time is equal to the offset of the first task. */
   Os_t_ScheduleTableState.t_ScheduledActivation = Os_gkat_ScheduleTable[Os_t_ScheduleTableState.t_NextSlowTaskId]
      .t_ActivationTimestamp;
#endif

#if (STD_ON == OS_USE_FAST_TASK)
   Os_t_FastTaskState.t_LastActivation = t_TimerValue;

   /* Initially, there is no cumulated delay of the alarm. */
   Os_t_FastTaskState.t_CumulatedDelay = (TickType) 0;

   /* The initial scheduled activation time is equal to the periodicity of the fast task. */
   Os_t_FastTaskState.t_ScheduledActivation = OS_FAST_TASK_PERIODICITY;
#endif

   /* Setup all the used interrupts. */
   OS_INTERRUPTS_INIT(&Os_gkt_IrqConfig);

#if (STD_ON == OS_USE_TIMING_MEASUREMENTS)
   Os_MeasurementsInit();
#endif
}

/**
 * \brief      Implements the polling based, non-preemptive, three static priorities scheduling algorithm.
 * \param      -
 * \return     -
 *
 * If activated, there is only one fast task, one schedule table and a background task. In one poll of the scheduler
 * only one of the tree task types can be activated, based on a simple three static priorities:
 *    -Highest priority: the fast task,
 *    -Medium priority: a slow task,
 *    -Lowest priority: the background task.
 */
static void Os_v_RunScheduler(void)
{
#if (STD_ON == OS_USE_FAST_TASK)
   TickType t_FastTaskElapsedTime;
#endif
#if (STD_ON == OS_USE_SLOW_TASKS)
   TickType t_SlowTaskElapsedTime;
#endif
   TickType t_TimerValue;

   /* The value of the OS timer is sampled. */
   t_TimerValue = (TickType) *Os_gkt_TimerCntReg;

#if (STD_ON == OS_USE_FAST_TASK)
   /* The time difference from the last fast alarm activation is computed. */
   t_FastTaskElapsedTime = (TickType) OS_GET_ELAPSED_TIME(t_TimerValue, Os_t_FastTaskState.t_LastActivation);

   /* Check if it's time to trigger the fast alarm. */
   if (t_FastTaskElapsedTime >= Os_t_FastTaskState.t_ScheduledActivation)
   {
      /* The fast alarm is triggered. */
      Os_t_FastTaskState.t_LastActivation = t_TimerValue;

      /* Add the last delay to the total delay. */
      Os_t_FastTaskState.t_CumulatedDelay += (t_FastTaskElapsedTime - Os_t_FastTaskState.t_ScheduledActivation);

      /* Check if the total delay can be recovered in one step, or more steps are necessary. */
      if (Os_t_FastTaskState.t_CumulatedDelay < OS_FAST_TASK_RECOVERY)
      {
         /* The entire delay can be recovered in one step by scheduling the next alarm to trigger earlier than
          * normal with the exact amount of time of the total delay. */
         Os_t_FastTaskState.t_ScheduledActivation = OS_FAST_TASK_PERIODICITY - Os_t_FastTaskState.t_CumulatedDelay;
         Os_t_FastTaskState.t_CumulatedDelay = (TickType) 0;
      }
      else
      {
         /* The total delay is greater than the maximum amount the wait time between two alarm activations can be
          * shortened. Thus, the wait time is shortened by the maximum amount and the same amount is subtracted
          * from the total delay. */
         Os_t_FastTaskState.t_ScheduledActivation = OS_FAST_TASK_PERIODICITY - OS_FAST_TASK_RECOVERY;
         Os_t_FastTaskState.t_CumulatedDelay -= OS_FAST_TASK_RECOVERY;
      }

#if (STD_ON == OS_USE_TIMING_MEASUREMENTS)
      Os_MeasurementsExitIdle();
      Os_MeasurementsEnterTask(OS_FAST_TASK);
#endif

      /* Execute the task associated with the time event of the fast alarm trigger. */
      Os_gkat_Tasks[OS_FAST_TASK]();

#if (STD_ON == OS_USE_TIMING_MEASUREMENTS)
      Os_MeasurementsExitTask(OS_FAST_TASK);
#endif
   }
   else
   /* It's not time to trigger the fast alarm yet. Moving on to the next items in the list by priorities, i.e.
    * the schedule table, followed by the background task. */
#endif /* (STD_ON == OS_USE_FAST_TASK) */
   {

#if (STD_ON == OS_USE_SLOW_TASKS)
      /* The time difference from the last activation of an expiry point is computed. */
      t_SlowTaskElapsedTime = (TickType) OS_GET_ELAPSED_TIME(t_TimerValue, Os_t_ScheduleTableState.t_LastActivation);

      /* Check if it's time to activate the next expiry point in the schedule table. */
      if (t_SlowTaskElapsedTime >= Os_t_ScheduleTableState.t_ScheduledActivation)
      {
         /* The next expiry point in the schedule table is activated. */
         Os_t_ScheduleTableState.t_LastActivation = t_TimerValue;

         /* Add the last delay to the total delay. */
         Os_t_ScheduleTableState.t_CumulatedDelay += (t_SlowTaskElapsedTime
            - Os_t_ScheduleTableState.t_ScheduledActivation);

#if (STD_ON == OS_USE_TIMING_MEASUREMENTS)
         Os_MeasurementsExitIdle();
         Os_MeasurementsEnterTask(Os_gkat_ScheduleTable[Os_t_ScheduleTableState.t_NextSlowTaskId].t_SlowTaskId);
#endif
         /* Execute the task associated with the time event of the next expiry point. */
         Os_gkat_Tasks[Os_gkat_ScheduleTable[Os_t_ScheduleTableState.t_NextSlowTaskId].t_SlowTaskId]();

#if (STD_ON == OS_USE_TIMING_MEASUREMENTS)
         Os_MeasurementsExitTask(Os_gkat_ScheduleTable[Os_t_ScheduleTableState.t_NextSlowTaskId].t_SlowTaskId);
#endif

         /* Compute the next expiry point which needs to be activated in the schedule table. */
         Os_t_ScheduleTableState.t_LastSlowTaskId = Os_t_ScheduleTableState.t_NextSlowTaskId;
         Os_t_ScheduleTableState.t_NextSlowTaskId =
         (((Os_t_ScheduleTableState.t_LastSlowTaskId) + 1U) % OS_SCHEDULE_TABLE_NR_OF_ACTIVATIONS);

         /* Check if the total delay can be recovered in one step, or more steps are necessary. */
         if (Os_t_ScheduleTableState.t_CumulatedDelay < OS_SLOW_TASK_RECOVERY)
         {
            /* The entire delay can be recovered in one step by scheduling the next expiry point to trigger earlier
             * than normal with the exact amount of time of the total delay. */
            Os_t_ScheduleTableState.t_ScheduledActivation =
            OS_SCH_TABLE_DELAY(Os_t_ScheduleTableState.t_LastSlowTaskId, Os_t_ScheduleTableState.t_NextSlowTaskId)
               - Os_t_ScheduleTableState.t_CumulatedDelay;
            Os_t_ScheduleTableState.t_CumulatedDelay = (TickType) 0;
         }
         else
         {
            /* The total delay is greater than the maximum amount the wait time between two expiry points activations
             * can be shortened. Thus, the wait time is shortened by the maximum amount and the same amount is
             * subtracted from the total delay. */
            Os_t_ScheduleTableState.t_ScheduledActivation =
            OS_SCH_TABLE_DELAY(Os_t_ScheduleTableState.t_LastSlowTaskId, Os_t_ScheduleTableState.t_NextSlowTaskId)
               - OS_SLOW_TASK_RECOVERY;
            Os_t_ScheduleTableState.t_CumulatedDelay -= OS_SLOW_TASK_RECOVERY;
         }
      }
      else
      #endif /* #if (STD_ON == OS_USE_SLOW_TASKS) */
      {
#if (STD_ON == OS_USE_BACKGROUND_TASK)
#if (STD_ON == OS_USE_TIMING_MEASUREMENTS)
         Os_MeasurementsEnterIdle();
         Os_MeasurementsEnterTask(OS_BACKGROUND_TASK);
#endif
         /* The time events for the alarm and expiry points have not triggered. The last event in the list of
          * priorities, the background event, is thus triggered and the associated task is called. */
         Os_gkat_Tasks[OS_BACKGROUND_TASK]();

#if (STD_ON == OS_USE_TIMING_MEASUREMENTS)
         Os_MeasurementsExitTask(OS_BACKGROUND_TASK);
#endif
#endif /* #if (STD_ON == OS_USE_BACKGROUND_TASK) */
      }
   }
}

/*-------------------------------------------------------------------------------------------------------------------*/
/*                                         Implementation Of Global Functions                                        */
/*-------------------------------------------------------------------------------------------------------------------*/

/**
 * \brief      Non-returning function which initializes and starts the operating system.
 * \param      AppMode : The ID of the OS application mode in which the OS should be started.
 * \return     -
 *
 * This function performs the initialization of the Operating System. The input parameter defines the OS application
 * mode in which the OS should be started. However, only one application mode is possible: default. If any other mode
 * is used then the OS enters in an infinite loop.
 * There are two steps in the initialization phase: initializing the OS timer and global variables (though Os_v_Init)
 * and initializing the application software (through FUNC_OS_INIT_TASK). While the initializations are performed the
 * interrupts are (globally) disabled.
 * After the initializations are finished the OS schedule algorithm is continuously called. */
void StartOS(AppModeType AppMode)
{
   switch (AppMode)
   {
      case (OSDEFAULTAPPMODE):
      {
         DisableAllInterrupts();

         /* Initializes the OS timer and variables. */
         Os_v_Init();

         /* Call the RTE and SWCs initialization task. */
         FUNC_OS_INIT_TASK();

         EnableAllInterrupts();

         /* Main OS infinite loop. */
         while (TRUE)
         {
            /* The scheduler executes exactly one task per iteration, according to the configured settings and the
             * value of the main counter. */
            Os_v_RunScheduler();
         }
         break;
      }
      default:
      {
         /* Unsupported application mode requested. */
         while (TRUE)
         {
         }
         break;
      }
   }
}
