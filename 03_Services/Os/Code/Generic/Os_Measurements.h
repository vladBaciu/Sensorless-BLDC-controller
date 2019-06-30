/*-------------------------------------------------------------------------------------------------------------------*/
/**
 *    \file       Os_Measurements.h
 *    \author     Nicolae-Bogdan Bacrau
 *    \brief      Exports all the necessary constants, variables and routines for performing the timing measurements.
 */
/*-------------------------------------------------------------------------------------------------------------------*/

#ifndef OS_MEASUREMENTS_H
#define OS_MEASUREMENTS_H

/*-------------------------------------------------------------------------------------------------------------------*/
/*                                                     Inclusions                                                    */
/*-------------------------------------------------------------------------------------------------------------------*/

#include "Os_Cfg.h"
#include "Os_Tasks_Cfg.h"
#include "Os_Core.h"

#if (STD_ON == OS_USE_TIMING_MEASUREMENTS)

/*-------------------------------------------------------------------------------------------------------------------*/
/*                                            Definition Of Global Macros                                            */
/*-------------------------------------------------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------------------------------------------------*/
/*                                          Definition Of Global Data Types                                          */
/*-------------------------------------------------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------------------------------------------------*/
/*                                             Export Of Global Variables                                            */
/*-------------------------------------------------------------------------------------------------------------------*/

extern volatile uint16 Os_gusCPULoad;
extern volatile TickType Os_gtTasksCurrentRuntimes[OS_NR_OF_RUN_TIME_TASKS];
extern volatile TickType Os_gtTasksMaxRuntimes[OS_NR_OF_RUN_TIME_TASKS];
extern volatile uint16 Os_gusTasksMinNrCalls[OS_NR_OF_RUN_TIME_TASKS];
extern volatile uint16 Os_gusTasksMaxNrCalls[OS_NR_OF_RUN_TIME_TASKS];
extern volatile boolean Os_gbTasksOvergrowthFlags[OS_NR_OF_RUN_TIME_TASKS];

/*-------------------------------------------------------------------------------------------------------------------*/
/*                                             Export Of Global Constants                                            */
/*-------------------------------------------------------------------------------------------------------------------*/

extern const TickType Os_gkatTasksRuntimeLimits[OS_NR_OF_RUN_TIME_TASKS];
extern const TickType Os_gkatTasksGrowthLimits[OS_NR_OF_RUN_TIME_TASKS];

/*-------------------------------------------------------------------------------------------------------------------*/
/*                                             Export Of Global Functions                                            */
/*-------------------------------------------------------------------------------------------------------------------*/

void Os_MeasurementsInit(void);
void Os_MeasurementsEnterTask(TaskType tTaskId);
void Os_MeasurementsExitTask(TaskType tTaskId);
void Os_MeasurementsEnterIsr(void);
void Os_MeasurementsExitIsr(void);
void Os_MeasurementsEnterIdle(void);
void Os_MeasurementsExitIdle(void);

#endif /* (STD_ON == OS_USE_TIMING_MEASUREMENTS) */

/*-------------------------------------------------------------------------------------------------------------------*/
#endif /* OS_MEASUREMENTS_H */
