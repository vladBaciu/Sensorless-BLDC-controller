/*-------------------------------------------------------------------------------------------------------------------*/
/**
 *    \file       Os_Core.h
 *    \author     Nicolae-Bogdan Bacrau
 *    \brief      Defines the global types used in the scheduling algorithm and exports all the tasks and OS timer
 *                configurations.
 */
/*-------------------------------------------------------------------------------------------------------------------*/

#ifndef OS_CORE_H
#define OS_CORE_H

/*-------------------------------------------------------------------------------------------------------------------*/
/*                                                     Inclusions                                                    */
/*-------------------------------------------------------------------------------------------------------------------*/

#include "Os_Timer_Cfg.h"
#include "Os_Cfg.h"
#include "Os_Tasks_Cfg.h"

/*-------------------------------------------------------------------------------------------------------------------*/
/*                                            Definition Of Global Macros                                            */
/*-------------------------------------------------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------------------------------------------------*/
/*                                          Definition Of Global Data Types                                          */
/*-------------------------------------------------------------------------------------------------------------------*/

/*-------------------------------------------------- AUTOSAR Types --------------------------------------------------*/

/** \brief  Defines the type for identifying OS tasks by ID. */
typedef uint8 TaskType;

/** \brief  Defines a reference to an OS timer timestamp. */
typedef TickType* TickRefType;

/*----------------------------------------------- Implementation Types -----------------------------------------------*/

/** \brief  Defines the type for building a schedule table entry: the activation timestamp and the slow task to be
 *          activated (by ID). */
typedef struct
{
   /** \brief  Contains the timestamp relative to the start of the schedule table window when to activate a task. */
   TickType t_ActivationTimestamp;

   /** \brief  Contains the ID of the OS slow task to be activated when the timestamp is reached. */
   TaskType t_SlowTaskId;
} Os_SlowTaskActivationType;

/** \brief  Type for the configuration of OS tasks. */
typedef void (*Os_Task)(void);

/*-------------------------------------------------------------------------------------------------------------------*/
/*                                             Export Of Global Variables                                            */
/*-------------------------------------------------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------------------------------------------------*/
/*                                             Export Of Global Constants                                            */
/*-------------------------------------------------------------------------------------------------------------------*/

extern const Os_TimerCfgType Os_gkt_TimerCfg;
extern const TickRefType Os_gkt_TimerCntReg;
extern const Os_SlowTaskActivationType Os_gkat_ScheduleTable[OS_SCHEDULE_TABLE_NR_OF_ACTIVATIONS];
extern const Os_Task Os_gkat_Tasks[OS_NR_OF_RUN_TIME_TASKS];

/*-------------------------------------------------------------------------------------------------------------------*/
/*                                             Export Of Global Functions                                            */
/*-------------------------------------------------------------------------------------------------------------------*/

extern TASK(OS_INIT_TASK);

/*-------------------------------------------------------------------------------------------------------------------*/
#endif /* OS_CORE_H */
