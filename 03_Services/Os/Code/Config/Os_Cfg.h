/*-------------------------------------------------------------------------------------------------------------------*/
/**
 *    \file       Os_Cfg.h
 *    \author     Nicolae-Bogdan Bacrau
 *    \brief      Exports all the OS global configurations and sets up the used APIs.
 */
/*-------------------------------------------------------------------------------------------------------------------*/

#ifndef OS_CFG_H
#define OS_CFG_H

/*-------------------------------------------------------------------------------------------------------------------*/
/*                                                     Inclusions                                                    */
/*-------------------------------------------------------------------------------------------------------------------*/

#include "Os_GlobalDefs.h"
#include "stm32f407xx.h"

/*-------------------------------------------------------------------------------------------------------------------*/
/*                                            Definition Of Global Macros                                            */
/*-------------------------------------------------------------------------------------------------------------------*/

/** \brief  Activates (STD_ON) or deactivates (STD_OFF) the usage of the fast task. */
#define OS_USE_FAST_TASK               (STD_ON)

/** \brief  Activates (STD_ON) or deactivates (STD_OFF) the usage of the schedule table based slow tasks. */
#define OS_USE_SLOW_TASKS              (STD_ON)

/** \brief  Activates (STD_ON) or deactivates (STD_OFF) the usage of the background task. */
#define OS_USE_BACKGROUND_TASK         (STD_ON)

/** \brief  Activates (STD_ON) or deactivates (STD_OFF) the usage of the timing measurements. */
#define OS_USE_TIMING_MEASUREMENTS     (STD_OFF)

/** \brief  Function-like macro which implements the AUTOSAR service to disable all interrupts.
 *
 * When using this function inside a critical section the following should be considered:
 * - Start Critical Section 0 (DisableAllInterrupts);
 * - Code 1;
 * - Start Critical Section 1 (DisableAllInterrupts);
 * - Code 2;
 * - End Critical Section 1 (EnableAllInterrupts);
 * - Code 3;
 * - End Critical Section 0 (EnableAllInterrupts);
 *
 * Code 3 is not critical section protected in this case. */
#define DisableAllInterrupts()         (__disable_irq())

/** \brief  Function-like macro which implements the AUTOSAR service to enable all interrupts.
 *
 * When using this function inside a critical section the following should be considered:
 * - Start Critical Section 0 (DisableAllInterrupts);
 * - Code 1;
 * - Start Critical Section 1 (DisableAllInterrupts);
 * - Code 2;
 * - End Critical Section 1 (EnableAllInterrupts);
 * - Code 3;
 * - End Critical Section 0 (EnableAllInterrupts);
 *
 * Code 3 is not critical section protected in this case. */
#define EnableAllInterrupts()          (__enable_irq())

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

/*-------------------------------------------------------------------------------------------------------------------*/
#endif /* OS_CFG_H */
