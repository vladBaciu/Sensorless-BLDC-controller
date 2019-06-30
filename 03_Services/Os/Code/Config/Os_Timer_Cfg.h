/*-------------------------------------------------------------------------------------------------------------------*/
/**
 *    \file       Os_Timer_Cfg.h
 *    \author     Nicolae-Bogdan Bacrau
 *    \brief      Defines global conversion macros from standard international time units to OS timer ticks, macro for
 *                calculating the elapsed time between two timestamps, and sets up how the OS timer control registers
 *                are initialized.
 */
/*-------------------------------------------------------------------------------------------------------------------*/

#ifndef OS_TIMER_CFG_H
#define OS_TIMER_CFG_H

/*-------------------------------------------------------------------------------------------------------------------*/
/*                                                     Inclusions                                                    */
/*-------------------------------------------------------------------------------------------------------------------*/

#include "RegInit.h"

/*-------------------------------------------------------------------------------------------------------------------*/
/*                                            Definition Of Global Macros                                            */
/*-------------------------------------------------------------------------------------------------------------------*/

/** \brief  Function-like macro to convert from microseconds to timer ticks. 1 us = 160 ticks. */
#define OS_US2TICKS(NrOfUs)                  ((TickType) ((((uint32) (NrOfUs)) * 5UL) << 5UL))

/** \brief  Function-like macro to convert from milliseconds to timer ticks. 1 ms = 160000 ticks. */
#define OS_MS2TICKS(NrOfMs)                  ((TickType) ((((uint32) (NrOfMs)) * 625UL) << 8UL))

/** \brief  Macro for calculating how much time has passed (in counter ticks) between two timestamps. */
#define OS_GET_ELAPSED_TIME(New, Old)        ((Old >= New) ? \
                                                   ((TickType)(Old - New)) : \
                                                   ((TickType)(0x00FFFFFFUL - New + Old)))

/** \brief  Function-like macro which initializes all the OS timer configuration registers through the masked RegInit
 *          32 bit registers API. */
#define OS_TIMER_REGISTERS_INIT()            (RegInit_gv_Masked32Bits(&Os_gkt_TimerCfg))

/*-------------------------------------------------------------------------------------------------------------------*/
/*                                          Definition Of Global Data Types                                          */
/*-------------------------------------------------------------------------------------------------------------------*/

/** \brief  Defines the length of the OS timer count (current value) register. */
typedef uint32 TickType;

/** \brief  Defines the type for the configuration of the OS timer control registers. */
typedef RegInit_Masked32BitsConfigType Os_TimerCfgType;

/*-------------------------------------------------------------------------------------------------------------------*/
/*                                             Export Of Global Variables                                            */
/*-------------------------------------------------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------------------------------------------------*/
/*                                             Export Of Global Constants                                            */
/*-------------------------------------------------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------------------------------------------------*/
/*                                             Export Of Global Functions                                            */
/*-------------------------------------------------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------------------------------------------------*/
#endif /* OS_TIMER_CFG_H */
