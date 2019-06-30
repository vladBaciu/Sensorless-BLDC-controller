/*-------------------------------------------------------------------------------------------------------------------*/
/**
 *    \file       Os_Timer_Cfg.c
 *    \author     Nicolae-Bogdan Bacrau
 *    \brief      Sets up all the timer configuration registers to be loaded with the masked RegInit 32 bit registers
 *                API and configures the address of the count register that is used in the OS core for keeping track
 *                of the time.
 */
/*-------------------------------------------------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------------------------------------------------*/
/*                                                     Inclusions                                                    */
/*-------------------------------------------------------------------------------------------------------------------*/

#include "Os_Timer_Cfg.h"
#include "Os_Core.h"
#include "stm32f407xx.h"

/*-------------------------------------------------------------------------------------------------------------------*/
/*                                             Definition Of Local Macros                                            */
/*-------------------------------------------------------------------------------------------------------------------*/

/** \brief  Defines the total number of OS timer configuration registers to be loaded in the initialization phase. */
#define OS_NUMBER_OF_TIMER_CFG_REGISTERS   (3U)

/*-------------------------------------------------------------------------------------------------------------------*/
/*                                           Definition Of Local Data Types                                          */
/*-------------------------------------------------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------------------------------------------------*/
/*                                           Declaration Of Local Variables                                          */
/*-------------------------------------------------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------------------------------------------------*/
/*                                          Declaration Of Global Variables                                          */
/*-------------------------------------------------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------------------------------------------------*/
/*                                           Declaration Of Local Constants                                          */
/*-------------------------------------------------------------------------------------------------------------------*/

/** \brief  Defines the list of all the OS timer configuration registers and their load values with OR and AND masks.
 *
 *          The used timer is the SysTick, which is a 24-bit downcounting timer integrated in the processor core. It is
 *          configured as a free running timer that continuously counts from 0x00FFFFFF to 0. */
static const RegInit_Masked32BitsSingleType Os_kat_TimerCfgRegs[OS_NUMBER_OF_TIMER_CFG_REGISTERS] =
   {
      /* Set the load value to be set into the current value register when the counter reaches 0. */
      {
         (volatile uint32*) (&SysTick->LOAD),

         (uint32) (~0xFFFFFFFFUL),

         (uint32) (0x00FFFFFFUL),
      },

      /* Set the current value register to 0. */
      {
         (volatile uint32*) (&SysTick->VAL),

         (uint32) (~0xFFFFFFFFUL),

         (uint32) (0x00000000UL)
      },

      /* Set the clock source as the system clock and enable the timer. Interrupts are disabled. */
      {
         (volatile uint32*) (&SysTick->CTRL),

         (uint32) (~0xFFFFFFFFUL),

         (uint32) (SysTick_CTRL_CLKSOURCE_Msk | SysTick_CTRL_ENABLE_Msk)
      },
   };

/*-------------------------------------------------------------------------------------------------------------------*/
/*                                          Declaration Of Global Constants                                          */
/*-------------------------------------------------------------------------------------------------------------------*/

/** \brief  Defines the timer configuration to be loaded in the initialization phase. */
const Os_TimerCfgType Os_gkt_TimerCfg =
   {
      Os_kat_TimerCfgRegs,
      OS_NUMBER_OF_TIMER_CFG_REGISTERS
   };

/** \brief  Defines the timer current value (count) register. */
const TickRefType Os_gkt_TimerCntReg = (TickRefType) (&SysTick->VAL);

/*-------------------------------------------------------------------------------------------------------------------*/
/*                                           Declaration Of Local Functions                                          */
/*-------------------------------------------------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------------------------------------------------*/
/*                                         Implementation Of Local Functions                                         */
/*-------------------------------------------------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------------------------------------------------*/
/*                                         Implementation Of Global Functions                                        */
/*-------------------------------------------------------------------------------------------------------------------*/
