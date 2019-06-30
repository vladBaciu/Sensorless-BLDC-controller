/*-------------------------------------------------------------------------------------------------------------------*/
/**
 *    \file       Os_Measurements.c
 *    \author     Nicolae-Bogdan Bacrau
 *    \brief      Implements all the needed routines for performing timing measurements.
 *
 *    The purpose of the measurements is to make sure that the global timing of the system is correct (acceptable CPU
 *    load, tasks are always executed according to the configuration) and, if not, to provide the means for identifying
 *    which tasks have unacceptable loads.
 */
/*-------------------------------------------------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------------------------------------------------*/
/*                                                     Inclusions                                                    */
/*-------------------------------------------------------------------------------------------------------------------*/

#include "Os_Measurements.h"
#include "Os_Measurements_Cfg.h"

#if (STD_ON == OS_USE_TIMING_MEASUREMENTS)

/*-------------------------------------------------------------------------------------------------------------------*/
/*                                             Definition Of Local Macros                                            */
/*-------------------------------------------------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------------------------------------------------*/
/*                                           Definition Of Local Data Types                                          */
/*-------------------------------------------------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------------------------------------------------*/
/*                                           Declaration Of Local Variables                                          */
/*-------------------------------------------------------------------------------------------------------------------*/

static TickType Os_t_IdleRuntime = 0U;
static TickType Os_t_EnterTaskTimestamp = 0U;
static TickType Os_t_EnterIsrTimestamp = 0U;
static TickType Os_t_LastEnterTaskTimestamp = 0U;
static TickType Os_t_IdleEnterTimestamp = 0U;
static TickType Os_t_TimeWindow = 0U;
static boolean Os_b_IdleIsActive = FALSE;
static uint16 Os_us_TasksNrCallsCounters[OS_NR_OF_RUN_TIME_TASKS];
static TickType Os_t_TasksGrowths[OS_NR_OF_RUN_TIME_TASKS];

/*-------------------------------------------------------------------------------------------------------------------*/
/*                                          Declaration Of Global Variables                                          */
/*-------------------------------------------------------------------------------------------------------------------*/

volatile uint16 Os_gus_CPULoad = 0U;
volatile TickType Os_gt_TasksCurrentRuntimes[OS_NR_OF_RUN_TIME_TASKS];
volatile TickType Os_gt_TasksMaxRuntimes[OS_NR_OF_RUN_TIME_TASKS];
volatile uint16 Os_gus_TasksMinNrCalls[OS_NR_OF_RUN_TIME_TASKS];
volatile uint16 Os_gus_TasksMaxNrCalls[OS_NR_OF_RUN_TIME_TASKS];
volatile boolean Os_gb_TasksOvergrowthFlags[OS_NR_OF_RUN_TIME_TASKS];

/*-------------------------------------------------------------------------------------------------------------------*/
/*                                           Declaration Of Local Constants                                          */
/*-------------------------------------------------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------------------------------------------------*/
/*                                          Declaration Of Global Constants                                          */
/*-------------------------------------------------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------------------------------------------------*/
/*                                           Declaration Of Local Functions                                          */
/*-------------------------------------------------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------------------------------------------------*/
/*                                         Implementation Of Local Functions                                         */
/*-------------------------------------------------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------------------------------------------------*/
/*                                         Implementation Of Global Functions                                        */
/*-------------------------------------------------------------------------------------------------------------------*/

/**
 * \brief      Initializes all the timing measurement variables.
 * \param      -
 * \return     -
 */
void Os_MeasurementsInit(void)
{
   uint8 uc_I;

   Os_gus_CPULoad = 0U;
   Os_t_IdleRuntime = 0U;
   Os_t_EnterTaskTimestamp = 0U;
   Os_t_EnterIsrTimestamp = 0U;
   Os_t_LastEnterTaskTimestamp = 0U;
   Os_t_IdleEnterTimestamp = 0U;
   Os_t_TimeWindow = 0U;
   Os_b_IdleIsActive = FALSE;

   for (uc_I = 0U; uc_I < OS_NR_OF_RUN_TIME_TASKS; uc_I++)
   {
      Os_gt_TasksCurrentRuntimes[uc_I] = 0U;
      Os_gt_TasksMaxRuntimes[uc_I] = 0U;
      Os_gb_TasksOvergrowthFlags[uc_I] = FALSE;
      Os_gus_TasksMinNrCalls[uc_I] = 0xFFFFU;
      Os_gus_TasksMaxNrCalls[uc_I] = 0U;
      Os_us_TasksNrCallsCounters[uc_I] = 0U;
      Os_t_TasksGrowths[uc_I] = 0U;
   }
}

/**
 * \brief      Marks the event of entering a task.
 * \param      tTaskId : ID of the entered task.
 * \return     -
 */
void Os_MeasurementsEnterTask(TaskType tTaskId)
{
   Os_t_EnterTaskTimestamp = (TickType) *Os_gkt_TimerCntReg;
   /* Reference unused parameter. */
   tTaskId++;
}

/**
 * \brief      Marks the event of exiting a task by computing the elapsed time in the specified task. Furthermore,
 *             checks if a runtime overgrowth took place and computes the CPU load.
 * \param      tTaskId : ID of the entered task.
 * \return     -
 */
void Os_MeasurementsExitTask(TaskType tTaskId)
{
   uint8 uc_I;
   TickType t_ExitTaskTimestamp;

   t_ExitTaskTimestamp = (TickType) *Os_gkt_TimerCntReg;
   Os_gt_TasksCurrentRuntimes[tTaskId] = OS_GET_ELAPSED_TIME(t_ExitTaskTimestamp, Os_t_EnterTaskTimestamp);
   Os_t_TimeWindow += OS_GET_ELAPSED_TIME(Os_t_EnterTaskTimestamp, Os_t_LastEnterTaskTimestamp);
   Os_t_LastEnterTaskTimestamp = Os_t_EnterTaskTimestamp;
   if (Os_t_TimeWindow >= OS_MEASUREMENTS_TIME_WINDOW)
   {
      /* Compute the CPU load.
       * - The used formula is: CPULoad [%] = (100 * (MeasurementTimeWindow - IdleTime) / MeasurementTimeWindow) * 10
       * - The result represents the CPU load percentage multiplied by 10, so that the first decimal is visible. */
      Os_gus_CPULoad = (uint16) ((((uint32) OS_MEASUREMENTS_TIME_WINDOW - (uint32) Os_t_IdleRuntime) * 1000UL)
         / (uint32) OS_MEASUREMENTS_TIME_WINDOW);
      Os_t_TimeWindow -= OS_MEASUREMENTS_TIME_WINDOW;
      Os_t_IdleRuntime = 0U;
      for (uc_I = 0U; uc_I < OS_NR_OF_RUN_TIME_TASKS; uc_I++)
      {
         if (Os_us_TasksNrCallsCounters[uc_I] > Os_gus_TasksMaxNrCalls[uc_I])
         {
            Os_gus_TasksMaxNrCalls[uc_I] = Os_us_TasksNrCallsCounters[uc_I];
         }
         else if (Os_us_TasksNrCallsCounters[uc_I] < Os_gus_TasksMinNrCalls[uc_I])
         {
            Os_gus_TasksMinNrCalls[uc_I] = Os_us_TasksNrCallsCounters[uc_I];
         }
         else
         {
            /* Nothing to do. */
         }
         Os_us_TasksNrCallsCounters[uc_I] = 0U;
      }
   }
   else
   {
      /* Nothing to do. It is not yet time to compute the CPU load. */
   }
   Os_us_TasksNrCallsCounters[tTaskId]++;

   if (Os_gt_TasksCurrentRuntimes[tTaskId] > Os_gt_TasksMaxRuntimes[tTaskId])
   {
      Os_gt_TasksMaxRuntimes[tTaskId] = Os_gt_TasksCurrentRuntimes[tTaskId];
   }
   else
   {
      /* Nothing to do. */
   }

   if (Os_t_TasksGrowths[tTaskId] <= Os_gkatTasksGrowthLimits[tTaskId])
   {
      if ((Os_t_TasksGrowths[tTaskId] + Os_gt_TasksCurrentRuntimes[tTaskId]) > Os_gkatTasksRuntimeLimits[tTaskId])
      {
         Os_t_TasksGrowths[tTaskId] += (Os_gt_TasksCurrentRuntimes[tTaskId] - Os_gkatTasksRuntimeLimits[tTaskId]);
      }
      else
      {
         Os_t_TasksGrowths[tTaskId] = 0U;
      }
   }
   else
   {
      Os_gb_TasksOvergrowthFlags[tTaskId] = TRUE;
   }
}

/**
 * \brief      Marks the event of entering an interrupt service routine execution.
 * \param      -
 * \return     -
 */
void Os_MeasurementsEnterIsr(void)
{
   Os_t_EnterIsrTimestamp = (TickType) *Os_gkt_TimerCntReg;
}

/**
 * \brief      Marks the event of exiting an interrupt service routine execution.
 * \param      -
 * \return     -
 */
void Os_MeasurementsExitIsr(void)
{
   TickType t_ExitIsrTimestamp;
   if (TRUE == Os_b_IdleIsActive)
   {
      t_ExitIsrTimestamp = (TickType) *Os_gkt_TimerCntReg;
      Os_t_IdleRuntime -= OS_GET_ELAPSED_TIME(t_ExitIsrTimestamp, Os_t_EnterIsrTimestamp);
   }
   else
   {
      /* Nothing to do. */
   }
}

/**
 * \brief      Marks the event of entering the idle time.
 * \param      -
 * \return     -
 */
void Os_MeasurementsEnterIdle(void)
{
   if (FALSE == Os_b_IdleIsActive)
   {
      Os_b_IdleIsActive = TRUE;
      Os_t_IdleEnterTimestamp = (TickType) *Os_gkt_TimerCntReg;
   }
   else
   {
      /* Nothing to do. */
   }
}

/**
 * \brief      Marks the event of exiting the idle time.
 * \param      -
 * \return     -
 */
void Os_MeasurementsExitIdle(void)
{
   TickType t_ExitIsrTimestamp;
   if (TRUE == Os_b_IdleIsActive)
   {
      Os_b_IdleIsActive = FALSE;
      t_ExitIsrTimestamp = (TickType) *Os_gkt_TimerCntReg;
      Os_t_IdleRuntime += OS_GET_ELAPSED_TIME(t_ExitIsrTimestamp, Os_t_IdleEnterTimestamp);
   }
   else
   {
      /* Nothing to do. */
   }
}

#endif /* (STD_ON == OS_USE_TIMING_MEASUREMENTS) */
