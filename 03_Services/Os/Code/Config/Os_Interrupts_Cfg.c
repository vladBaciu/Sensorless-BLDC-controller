/*-------------------------------------------------------------------------------------------------------------------*/
/**
 *    \file       Os_Interrupts_Cfg.c
 *    \author     Nicolae-Bogdan Bacrau
 *    \brief      Performs initializations of all interrupts and defines the interrupt vector which contains: the
 *                stack pointer, reset handler, exception handles and interrupt handles.
 */
/*-------------------------------------------------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------------------------------------------------*/
/*                                                     Inclusions                                                    */
/*-------------------------------------------------------------------------------------------------------------------*/

#include "Os_Interrupts_Cfg.h"
#include "Os_Measurements.h"
#include "Linker_Symbols.h"
#include "EcuM.h"
#include "Dio.h"
#include "Pwm.h"
#include "Delay.h"
#include "MotorControl.h"
#include "MotorController.h"
/*-------------------------------------------------------------------------------------------------------------------*/
/*                                             Definition Of Local Macros                                            */
/*-------------------------------------------------------------------------------------------------------------------*/
/** \brief   Number of registers from interrupt configuration array */
#define OS_NUMBER_OF_REGISTERS   (22U)
/*-------------------------------------------------------------------------------------------------------------------*/
/*                                           Definition Of Local Data Types                                          */
/*-------------------------------------------------------------------------------------------------------------------*/

/** \brief  Defines the interface of all the handlers inside the interrupt vector. */
typedef void (* const Os_InterruptsHandler)(void);

/*-------------------------------------------------------------------------------------------------------------------*/
/*                                           Declaration Of Local Variables                                          */
/*-------------------------------------------------------------------------------------------------------------------*/
volatile uint32 uc_StepIrq;
volatile uint32 uc_IndexIrq = 0;
volatile uint8 uc_StartupRampFlag = 0;
volatile uint8 uc_InterruptNumber = 0;
volatile uint8 uc_BemfA;
const MotorControl_ConfigType *ConfigPtr;
/*-------------------------------------------------------------------------------------------------------------------*/
/*                                          Declaration Of Global Variables                                          */
/*-------------------------------------------------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------------------------------------------------*/
/*                                           Declaration Of Local Constants                                          */
/*-------------------------------------------------------------------------------------------------------------------*/
/**   \brief
 *
 */
static const RegInit_Masked32BitsSingleType Os_gkt_IrqRegisters[OS_NUMBER_OF_REGISTERS] =
{
   /*                                     CONFIGURATION OF EXTERNAL INTERRUPT CHANNEL 2                               */

   /* Configure external interrupt configuration register
    * Set in SYSCFG_EXTICR1   on EXTI2 as PA2 external interrupt*/
   {
      &SYSCFG->EXTICR[0],
      (uint32) ~(SYSCFG_EXTICR1_EXTI2),
      (uint32) (SYSCFG_EXTICR1_EXTI2_PA),

   },
   /* Configure rising trigger selection register for EXTI2 as enable*/
   {
      &EXTI->RTSR,
      (uint32) ~(EXTI_RTSR_TR2),
      (uint32) (0x00),
   },
   /* Configure falling trigger selection register for EXTI2 as enable*/
   {
      &EXTI->FTSR,
      (uint32) ~(EXTI_RTSR_TR2),
      (uint32) (0x00),
   },
   /* Configure interrupt mask register
    * Set MR2 for EXTI2 as not masked*/
   {
      &EXTI->IMR,
      (uint32) ~(EXTI_IMR_MR2),
      (uint32) (EXTI_IMR_MR2),
   },
   /* Configure interrupt priority registers
    * SET OS_IRQ_PA2 priority as 0x01*/
   {
      (volatile uint32*) &NVIC->IP[OS_IRQ_PA2],
      (uint32) ~(OS_IRQ_PA2_PRIORITY),
      (uint32) (OS_IRQ_PA2_PRIORITY)
   },
   /* Enable interrupt in the NVIC controller
    * Disable EXTI2 interrupt*/
   {
      &NVIC->ISER[OS_IRQ_POSITION(OS_IRQ_PA2)],
      (uint32) ~(OS_IRQ_ENABLE(OS_IRQ_PA2)),
      (uint32) (0x00),
   },
   /*                                     CONFIGURATION OF EXTERNAL INTERRUPT CHANNEL 3                               */

   /* Configure external interrupt configuration register
    * Set in SYSCFG_EXTICR1   on EXTI2 as PA2 external interrupt*/
   {
      &SYSCFG->EXTICR[1],
      (uint32) ~(SYSCFG_EXTICR1_EXTI3),
      (uint32) (SYSCFG_EXTICR1_EXTI3_PA),

   },
   /* Configure rising trigger selection register for EXTI3 as enable*/
   {
      &EXTI->RTSR,
      (uint32) ~(EXTI_RTSR_TR3),
      (uint32) (0x00),
   },
   /* Configure falling trigger selection register for EXTI3 as disable*/
   {
      &EXTI->FTSR,
      (uint32) ~(EXTI_RTSR_TR3),
      (uint32) (0x00),
   },
   /* Configure interrupt mask register
    * Set MR2 for EXTI2 as not masked*/
   {
      &EXTI->IMR,
      (uint32) ~(EXTI_IMR_MR3),
      (uint32) (EXTI_IMR_MR3),
   },
   /* Configure interrupt priority registers
    * SET OS_IRQ_PA2 priority as 0x01*/
   {
      (volatile uint32*) &NVIC->IP[OS_IRQ_PA3],
      (uint32) ~(OS_IRQ_PA3_PRIORITY),
      (uint32) (OS_IRQ_PA3_PRIORITY)
   },
   /* Enable interrupt in the NVIC controller
    * Disable EXTI2 interrupt*/
   {
      &NVIC->ISER[OS_IRQ_POSITION(OS_IRQ_PA3)],
      (uint32) ~(OS_IRQ_ENABLE(OS_IRQ_PA3)),
      (uint32) (0x00),
   },

   /*                                     CONFIGURATION OF EXTERNAL INTERRUPT CHANNEL 4                               */

   /* Configure external interrupt configuration register
    * Set in SYSCFG_EXTICR1   on EXTI2 as PA2 external interrupt*/
   {
      &SYSCFG->EXTICR[2],
      (uint32) ~(SYSCFG_EXTICR2_EXTI4),
      (uint32) (SYSCFG_EXTICR2_EXTI4_PA),

   },
   /* Configure rising trigger selection register for EXTI4 as enable*/
   {
      &EXTI->RTSR,
      (uint32) ~(EXTI_RTSR_TR4),
      (uint32) (0x00),
   },
   /* Configure falling trigger selection register for EXTI4 as disable*/
   {
      &EXTI->FTSR,
      (uint32) ~(EXTI_RTSR_TR4),
      (uint32) (0x00),
   },
   /* Configure interrupt mask register
    * Set MR2 for EXTI2 as not masked*/
   {
      &EXTI->IMR,
      (uint32) ~(EXTI_IMR_MR4),
      (uint32) (EXTI_IMR_MR4),
   },
   /* Configure interrupt priority registers
    * SET OS_IRQ_PA2 priority as 0x01*/
   {
      (volatile uint32*) &NVIC->IP[OS_IRQ_PA4],
      (uint32) ~(OS_IRQ_PA4_PRIORITY),
      (uint32) (OS_IRQ_PA4_PRIORITY)
   },
   /* Enable interrupt in the NVIC controller
    * Disable EXTI4 interrupt*/
   {
      &NVIC->ISER[OS_IRQ_POSITION(OS_IRQ_PA4)],
      (uint32) ~(OS_IRQ_ENABLE(OS_IRQ_PA4)),
      (uint32) (0x00),
   },
   /*                                      CONFIGURATION OF TIM2 INTERRUPT CHANNEL                                    */
   /* Configure interrupt priority registers
    * SET OS_IRQ_TIM2 priority as 0x01*/
   {
      (volatile uint32*) &NVIC->IP[OS_IRQ_TIM2],
      (uint32) ~(OS_IRQ_TIM2_PRIORITY),
      (uint32) (OS_IRQ_TIM2_PRIORITY),
   },
   /* Enable interrupt in the NVIC controller
    * Enable TIM2 overflow interrupt*/
   {
      &NVIC->ISER[OS_IRQ_POSITION(OS_IRQ_TIM2)],
      (uint32) ~(OS_IRQ_ENABLE(OS_IRQ_TIM2)),
      (uint32) (OS_IRQ_ENABLE(OS_IRQ_TIM2)),
   },

   /*                                      CONFIGURATION OF TIM5 INTERRUPT CHANNEL                                    */
   /* Configure interrupt priority registers
    * SET OS_IRQ_TIM5 priority as 0x01*/
   {
      (volatile uint32*) &NVIC->IP[OS_IRQ_TIM5],
      (uint32) ~(OS_IRQ_TIM5_PRIORITY),
      (uint32) (OS_IRQ_TIM5_PRIORITY),
   },
   /* Enable interrupt in the NVIC controller
    * Enable TIM5 overflow interrupt*/
   {
      &NVIC->ISER[OS_IRQ_POSITION(OS_IRQ_TIM5)],
      (uint32) ~(OS_IRQ_ENABLE(OS_IRQ_TIM5)),
      (uint32) (OS_IRQ_ENABLE(OS_IRQ_TIM5)),
   },

};
/*-------------------------------------------------------------------------------------------------------------------*/
/*                                          Declaration Of Global Constants                                          */
/*-------------------------------------------------------------------------------------------------------------------*/
/**   \brief   Configuration array that stores the interrupt registers and number of registers macro. */

const Os_IRQType Os_gkt_IrqConfig =
{
   Os_gkt_IrqRegisters,
   OS_NUMBER_OF_REGISTERS
};

/** \brief  Defines the list of all the interrupt routines. It has an explicit section name and relies on the linker
 *          script for being placed at the correct location in memory. */
__attribute__ ((section(".isr_vector"), used)) const Os_InterruptsHandler Os_kapf_InterruptVector[] =
{
   /* ----------------------------------------------------------------------------------- */
   /* Cortex-M core handlers. */
   (Os_InterruptsHandler) &_Linker_StackHead_, /*   The stack pointer                     */
   EcuM_Init, /*                                    The reset handler                     */
   Os_gv_ExceptionHandler, /*                       The NMI handler                       */
   Os_gv_ExceptionHandler, /*                       The hard fault handler                */
   Os_gv_ExceptionHandler, /*                       The MPU fault handler                 */
   Os_gv_ExceptionHandler, /*                       The bus fault handler                 */
   Os_gv_ExceptionHandler, /*                       The usage fault handler               */
   NULL_PTR, /*                                     Reserved                              */
   NULL_PTR, /*                                     Reserved                              */
   NULL_PTR, /*                                     Reserved                              */
   NULL_PTR, /*                                     Reserved                              */
   Os_gv_ExceptionHandler, /*                       SVCall handler                        */
   Os_gv_ExceptionHandler, /*                       Debug monitor handler                 */
   NULL_PTR, /*                                     Reserved                              */
   Os_gv_ExceptionHandler, /*                       The PendSV handler                    */
   Os_gv_ExceptionHandler, /*                       The SysTick handler                   */
   /* ----------------------------------------------------------------------------------- */
   /* External interrupt handlers. */
   NULL_PTR, /*                                     Window WatchDog                       */
   NULL_PTR, /*                                     PVD - EXTI Line                       */
   NULL_PTR, /*                                     Tamper and TimeStamps - EXTI line     */
   NULL_PTR, /*                                     RTC wake-up - EXTI line               */
   NULL_PTR, /*                                     FLASH                                 */
   NULL_PTR, /*                                     RCC                                   */
   NULL_PTR, /*                                     EXTI Line0                            */
   NULL_PTR, /*                                     EXTI Line1                            */
   Os_Exti2_Handler, /*                             EXTI Line2                            */
   Os_Exti3_Handler, /*                             EXTI Line3                            */
   Os_Exti4_Handler, /*                             EXTI Line4                            */
   NULL_PTR, /*                                     DMA1 Stream 0                         */
   NULL_PTR, /*                                     DMA1 Stream 1                         */
   NULL_PTR, /*                                     DMA1 Stream 2                         */
   NULL_PTR, /*                                     DMA1 Stream 3                         */
   NULL_PTR, /*                                     DMA1 Stream 4                         */
   NULL_PTR, /*                                     DMA1 Stream 5                         */
   NULL_PTR, /*                                     DMA1 Stream 6                         */
   NULL_PTR, /*                                     ADC1, ADC2 and ADC3s                  */
   NULL_PTR, /*                                     CAN1 TX                               */
   NULL_PTR, /*                                     CAN1 RX0                              */
   NULL_PTR, /*                                     CAN1 RX1                              */
   NULL_PTR, /*                                     CAN1 SCE                              */
   NULL_PTR, /*                                     External Line[9:5]s                   */
   NULL_PTR, /*                                     TIM1 Break and TIM9                   */
   NULL_PTR, /*                                     TIM1 Update and TIM10                 */
   NULL_PTR, /*                                     TIM11, TIM1 Trigger and commutation   */
   NULL_PTR, /*                                     TIM1 Capture Compare                  */
   Os_Tim2_Handler, /*                              TIM2                                  */
   NULL_PTR, /*                                     TIM3                                  */
   NULL_PTR, /*                                     TIM4                                  */
   NULL_PTR, /*                                     I2C1 Event                            */
   NULL_PTR, /*                                     I2C1 Error                            */
   NULL_PTR, /*                                     I2C2 Event                            */
   NULL_PTR, /*                                     I2C2 Error                            */
   NULL_PTR, /*                                     SPI1                                  */
   NULL_PTR, /*                                     SPI2                                  */
   NULL_PTR, /*                                     USART1                                */
   NULL_PTR, /*                                     USART2                                */
   NULL_PTR, /*                                     USART3                                */
   NULL_PTR, /*                                     External Line[15:10]s                 */
   NULL_PTR, /*                                     RTC Alarm (A and B) through EXTI Line */
   NULL_PTR, /*                                     USB OTG FS wake-up through EXTI line  */
   NULL_PTR, /*                                     TIM8 Break and TIM12                  */
   NULL_PTR, /*                                     TIM8 Update and TIM13                 */
   NULL_PTR, /*                                     TIM14, TIM8 Trigger and commutation   */
   NULL_PTR, /*                                     TIM8 Capture Compare                  */
   NULL_PTR, /*                                     DMA1 Stream7                          */
   NULL_PTR, /*                                     FMC                                   */
   NULL_PTR, /*                                     SDIO                                  */
   Os_Tim5_Handler, /*                              TIM5                                  */
   NULL_PTR, /*                                     SPI3                                  */
   NULL_PTR, /*                                     UART4                                 */
   NULL_PTR, /*                                     UART5                                 */
   NULL_PTR, /*                                     TIM6 and DAC1&2 under-run errors      */
   NULL_PTR, /*                                     TIM7                                  */
   NULL_PTR, /*                                     DMA2 Stream 0                         */
   NULL_PTR, /*                                     DMA2 Stream 1                         */
   NULL_PTR, /*                                     DMA2 Stream 2                         */
   NULL_PTR, /*                                     DMA2 Stream 3                         */
   NULL_PTR, /*                                     DMA2 Stream 4                         */
   NULL_PTR, /*                                     Ethernet                              */
   NULL_PTR, /*                                     Ethernet wake-up through EXTI line    */
   NULL_PTR, /*                                     CAN2 TX                               */
   NULL_PTR, /*                                     CAN2 RX0                              */
   NULL_PTR, /*                                     CAN2 RX1                              */
   NULL_PTR, /*                                     CAN2 SCE                              */
   NULL_PTR, /*                                     USB OTG FS                            */
   NULL_PTR, /*                                     DMA2 Stream 5                         */
   NULL_PTR, /*                                     DMA2 Stream 6                         */
   NULL_PTR, /*                                     DMA2 Stream 7                         */
   NULL_PTR, /*                                     USART6                                */
   NULL_PTR, /*                                     I2C3 event                            */
   NULL_PTR, /*                                     I2C3 error                            */
   NULL_PTR, /*                                     USB OTG HS End Point 1 Out            */
   NULL_PTR, /*                                     USB OTG HS End Point 1 In             */
   NULL_PTR, /*                                     USB OTG HS wake-up through EXTI       */
   NULL_PTR, /*                                     USB OTG HS                            */
   NULL_PTR, /*                                     DCMI                                  */
   NULL_PTR, /*                                     Reserved                              */
   NULL_PTR, /*                                     Hash and Rng                          */
   NULL_PTR, /*                                     FPU                                   */
};

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
 * \brief      Called when an unexpected interrupt occurs or a specific handler is not present in the application code.
 * \param      -
 * \return     -
 */
void __attribute__ ((section(".after_vectors"))) Os_gv_ExceptionHandler(void)
{
   /* Enter infinite loop and wait for a watchdog reset (if available). */
   while (TRUE)
   {
   }
}
/**   \brief   Init the registers for interrupt channel enable and NVIC registers
 *    \param   Pointer to IRQ configuration register
 *    \return  -
 */
void Os_gv_InitIRQ(const Os_IRQType* Os_gkt_IrqConfig)
{
   RegInit_gv_Masked32Bits(Os_gkt_IrqConfig);
}

/**   \brief   Test function for IRQ
 *    \param   -
 *    \return  -
 */

void Os_Tim2_Handler()
{
   ConfigPtr = &MotorControl_gkt_RampUpCfg;

   if (uc_IndexIrq > MOTORCONTROL_RAMPUP_STEPS - 1)
   {
      uc_StartupRampFlag = 1;
      if (uc_InterruptNumber < 200)
         uc_InterruptNumber++;
      MotorControl_gv_Move(uc_StepIrq, ConfigPtr->pt_ConfigGroup[uc_IndexIrq - 2].t_Value);
      MotorControl_gv_SetRampUpTime(&MotorControl_gkt_RampUpCfg, (uc_IndexIrq - 2));
   }
   else
   {
      MotorControl_gv_Move(uc_StepIrq, ConfigPtr->pt_ConfigGroup[uc_IndexIrq].t_Value);
      MotorControl_gv_SetRampUpTime(&MotorControl_gkt_RampUpCfg, uc_IndexIrq);
      uc_IndexIrq++;
   }
   if (MotorController_StartFlag == 0)
      uc_IndexIrq = 0;
   if (MotorController_Direction == RTE_FORWARD)
   {
      uc_StepIrq = (uc_StepIrq + 1) % 6;
   }
   else if (MotorController_Direction == RTE_BACKWARD)
   {
      if (uc_StepIrq != 0)
      {
         uc_StepIrq = uc_StepIrq - 1;
      }
      else
      {
         uc_StepIrq = MOTORCONTROLLER_BACKWARD_START;
      }
   }
   else
   {

   }
   TIM2->SR &= ~TIM_SR_UIF;

}

void Os_Tim5_Handler()
{

   // MotorControl_gv_AlignRoutine(&MotorControl_gkt_AlignmentCfg, uc_Step);
   if (uc_StepIrq == MotorControl_gkt_AlignmentCfg.ul_NumberOfSteps)
   {

      TIM5->DIER &= ~TIM_DIER_UIE;
      uc_StartupRampFlag = 1;
      uc_StepIrq = 0;
      uc_IndexIrq = 0;

      TIM2->CNT = 0x00;
      TIM2->CNT |= MOTORCONTROL_TIMER_VALUE;
      TIM2->ARR |= MOTORCONTROL_TIMER_VALUE;
      TIM2->DIER |= TIM_DIER_UIE;
      TIM2->CR1 |= TIM_CR1_CEN;

   }
   else
   {
      uc_StepIrq++;
   }
   TIM5->SR &= ~TIM_SR_UIF;
}
void Os_Exti2_Handler()
{
   *(&NVIC->ICER[OS_IRQ_POSITION(OS_IRQ_PA2)]) = (uint32) (OS_IRQ_DISABLE(OS_IRQ_PA2));
   uc_BemfA++;
   uc_BemfA = uc_BemfA % 2;
   if (((uc_InterruptNumber > 100) && (uc_StartupRampFlag == 1)) && (uc_BemfA == 1))
   {

      Dio_WriteChannel(DIO_D_15, STD_HIGH);
      Delay_gv_Us(100);
      Dio_WriteChannel(DIO_D_15, STD_LOW);
   }
   else
   {

   }

   EXTI->PR |= EXTI_PR_PR2;

}
void Os_Exti3_Handler()
{
   *(&NVIC->ICER[OS_IRQ_POSITION(OS_IRQ_PA3)]) = (uint32) (OS_IRQ_DISABLE(OS_IRQ_PA3));
   if ((uc_InterruptNumber > 100) && (uc_StartupRampFlag == 1))
   {
      Dio_WriteChannel(DIO_D_15, STD_HIGH);
      Delay_gv_Us(100);
      Dio_WriteChannel(DIO_D_15, STD_LOW);
   }
   else
   {

   }
   EXTI->PR |= EXTI_PR_PR3;

}
void Os_Exti4_Handler()
{
   *(&NVIC->ICER[OS_IRQ_POSITION(OS_IRQ_PA4)]) = (uint32) (OS_IRQ_DISABLE(OS_IRQ_PA4));
   if ((uc_InterruptNumber > 100) && (uc_StartupRampFlag == 1))
   {
      Dio_WriteChannel(DIO_D_15, STD_HIGH);
      Delay_gv_Us(100);
      Dio_WriteChannel(DIO_D_15, STD_LOW);
   }
   else
   {

   }
   EXTI->PR |= EXTI_PR_PR4;
}
