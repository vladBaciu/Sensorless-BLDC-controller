/*-------------------------------------------------------------------------------------------------------------------*/
/**
 *    \file       Os_Interrupts_Cfg.h
 *    \author     Nicolae-Bogdan Bacrau
 *    \brief      Defines the custom interrupts initialization macro and exports all the interrupt routines.
 */
/*-------------------------------------------------------------------------------------------------------------------*/

#ifndef OS_INTERRUPTS_CFG_H
#define OS_INTERRUPTS_CFG_H

/*-------------------------------------------------------------------------------------------------------------------*/
/*                                                     Inclusions                                                    */
/*-------------------------------------------------------------------------------------------------------------------*/
#include "RegInit.h"
/*-------------------------------------------------------------------------------------------------------------------*/
/*                                            Definition Of Global Macros                                            */
/*-------------------------------------------------------------------------------------------------------------------*/
/** \brief   Enable interrupts interrupt set-enable register  */
#define OS_IRQ_ENABLE(IRQ)  (0x01 << (IRQ & (uint8) 0x1F))

/** \brief   Disable interrupts interrupt set-disable register  */
#define OS_IRQ_DISABLE(IRQ)  (0x01 << (IRQ & (uint8) 0x1F))

/** \brief   Position of interrupt in ISER register */
#define OS_IRQ_POSITION(INDEX)   (INDEX >> 0x05)

/** \brief   PA2 channel interrupt */
#define OS_IRQ_PA2               (EXTI2_IRQn)

/** \brief   Define priority for OS_IRQ_PA2 */
#define OS_IRQ_PA2_PRIORITY      (0x01)

/** \brief   PA3 channel interrupt */
#define OS_IRQ_PA3               (EXTI3_IRQn)

/** \brief   Define priority for OS_IRQ_PA3 */
#define OS_IRQ_PA3_PRIORITY      (0x01)

/** \brief   PA4 channel interrupt */
#define OS_IRQ_PA4               (EXTI4_IRQn)

/** \brief   Define priority for OS_IRQ_PA4 */
#define OS_IRQ_PA4_PRIORITY      (0x01)

/** \brief  Tim2 interrupt */
#define OS_IRQ_TIM2  (TIM2_IRQn)

/** \brief   Define priority for OS_IRQ_TIM2 */
#define OS_IRQ_TIM2_PRIORITY      (0x00)

/** \brief  Tim2 interrupt */
#define OS_IRQ_TIM5  (TIM5_IRQn)

/** \brief   Define priority for OS_IRQ_TIM2 */
#define OS_IRQ_TIM5_PRIORITY      (0x00)

/** \brief  Defines the interrupt initialization actions to take place at the end of the OS core initialization
 *          routine. No interrupts are used, therefore the macro is empty. */
#define OS_INTERRUPTS_INIT(Os_gkt_IrqConfig)     Os_gv_InitIRQ(Os_gkt_IrqConfig)

/*-------------------------------------------------------------------------------------------------------------------*/
/*                                          Definition Of Global Data Types                                          */
/*-------------------------------------------------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------------------------------------------------*/
/*                                             Export Of Global Variables                                            */
/*-------------------------------------------------------------------------------------------------------------------*/
volatile uint32 uc_StepIrq;
volatile uint32 uc_IndexIrq;
volatile uint8 uc_StartupRampFlag;
volatile uint8 uc_InterruptNumber;
/*-------------------------------------------------------------------------------------------------------------------*/
/*                                             Export Of Global Constants                                            */
/*-------------------------------------------------------------------------------------------------------------------*/
/** \brief Configuration type for interrupts */
typedef RegInit_Masked32BitsConfigType Os_IRQType;
/*-------------------------------------------------------------------------------------------------------------------*/
/*                                             Export Of Global Functions                                            */
/*-------------------------------------------------------------------------------------------------------------------*/
extern const Os_IRQType Os_gkt_IrqConfig;
extern void Os_gv_ExceptionHandler(void);
extern void Os_gv_InitIRQ(const Os_IRQType* Os_gkt_IrqConfig);
extern void Os_Exti2_Handler();
extern void Os_Exti3_Handler();
extern void Os_Exti4_Handler();
extern void Os_Tim2_Handler();
extern void Os_Tim5_Handler();
/*-------------------------------------------------------------------------------------------------------------------*/
#endif /* OS_INTERRUPTS_CFG_H */
