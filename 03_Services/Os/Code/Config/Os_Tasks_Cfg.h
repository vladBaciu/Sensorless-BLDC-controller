/*-------------------------------------------------------------------------------------------------------------------*/
/**
 *    \file       Os_Tasks_Cfg.h
 *    \author     Nicolae-Bogdan Bacrau
 *    \brief      Defines the global timing values (schedule table time window, task periodicities and maximum recovery
 *                times), global task IDs and exports the tasks.
 */
/*-------------------------------------------------------------------------------------------------------------------*/

#ifndef OS_TASKS_CFG_H
#define OS_TASKS_CFG_H

/*-------------------------------------------------------------------------------------------------------------------*/
/*                                                     Inclusions                                                    */
/*-------------------------------------------------------------------------------------------------------------------*/

#include "Os_GlobalDefs.h"
#include "Os_Timer_Cfg.h"

/*-------------------------------------------------------------------------------------------------------------------*/
/*                                            Definition Of Global Macros                                            */
/*-------------------------------------------------------------------------------------------------------------------*/

/** \brief  Defines the total time window in which slow task activations are scheduled. */
#define OS_SCHEDULE_TABLE_TIME_WINDOW           (OS_MS2TICKS(100U))

/** \brief  Defines the total number of activations of slow tasks in the configured schedule table time window. */
#define OS_SCHEDULE_TABLE_NR_OF_ACTIVATIONS     (36U)

/** \brief  Defines the periodicity of the fast task. */
#define OS_FAST_TASK_PERIODICITY                (OS_US2TICKS(500U))

/** \brief  Defines the maximum recovery time of the fast task. */
#define OS_FAST_TASK_RECOVERY                   (OS_US2TICKS(100U))

/** \brief  Defines the maximum recovery time of the slow tasks. */
#define OS_SLOW_TASK_RECOVERY                   (OS_US2TICKS(500U))

/** \brief  Defines the total number of run time tasks (including the background task). */
#define OS_NR_OF_RUN_TIME_TASKS                 (6U)

/** \brief  Defines the ID of the slow task with the periodicity of 5 ms. */
#define OS_5MS_TASK                             (0U)

/** \brief  Defines the ID of the slow task with the periodicity of 10 ms. */
#define OS_10MS_TASK                            (1U)

/** \brief  Defines the ID of the slow task with the periodicity of 20 ms. */
#define OS_20MS_TASK                            (2U)

/** \brief  Defines the ID of the slow task with the periodicity of 100 ms. */
#define OS_100MS_TASK                           (3U)

/** \brief  Defines the ID of the fast task. */
#define OS_FAST_TASK                            (4U)

/** \brief  Defines the ID the background task. */
#define OS_BACKGROUND_TASK                      (5U)

/*-------------------------------------------------------------------------------------------------------------------*/
/*                                          Definition Of Global Data Types                                          */
/*-------------------------------------------------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------------------------------------------------*/
/*                                             Export Of Global Variables                                            */
/*-------------------------------------------------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------------------------------------------------*/
/*                                             Export Of Global Constants                                            */
/*-------------------------------------------------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------------------------------------------------*/
/*                                             Export Of Global Functions                                            */
/*-------------------------------------------------------------------------------------------------------------------*/

extern TASK(OS_5MS_TASK);
extern TASK(OS_10MS_TASK);
extern TASK(OS_20MS_TASK);
extern TASK(OS_20MS_2_TASK);
extern TASK(OS_100MS_TASK);
extern TASK(OS_FAST_TASK);
extern TASK(OS_BACKGROUND_TASK);

/*-------------------------------------------------------------------------------------------------------------------*/
#endif /* OS_TASKS_CFG_H */
