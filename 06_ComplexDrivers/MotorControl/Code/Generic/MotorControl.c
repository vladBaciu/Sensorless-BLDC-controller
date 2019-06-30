/*-------------------------------------------------------------------------------------------------------------------*/
/**
 *    \file       MotorControl.c
 *    \author     Baciu Vlad-Eusebiu
 *    \brief      Empty template to be used for all .c files. This file provides an example for the case in which a
 *                detailed description is not needed.
 */
/*-------------------------------------------------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------------------------------------------------*/
/*                                                     Inclusions                                                    */
/*-------------------------------------------------------------------------------------------------------------------*/
#include "MotorControl.h"
#include "Pwm.h"
#include "Dio.h"
#include "Os_Interrupts_Cfg.h"
/*-------------------------------------------------------------------------------------------------------------------*/
/*                                             Definition Of Local Macros                                            */
/*-------------------------------------------------------------------------------------------------------------------*/

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
 *    \brief
 *    \param  -
 *    \return -
 */
void MotrolControl_v_TurnOffPwm()
{
   Pwm_SetDutyCycle(MOTORCONTROL_PHASE_AH, STD_LOW);
   Dio_WriteChannel(MOTORCONTROL_PHASE_AL, STD_LOW);

   Pwm_SetDutyCycle(MOTORCONTROL_PHASE_BH, STD_LOW);
   Dio_WriteChannel(MOTORCONTROL_PHASE_BL, STD_LOW);

   Pwm_SetDutyCycle(MOTORCONTROL_PHASE_CH, STD_LOW);
   Dio_WriteChannel(MOTORCONTROL_PHASE_CL, STD_LOW);

   *(&NVIC->ISER[OS_IRQ_POSITION(OS_IRQ_PA2)]) = (uint32) (OS_IRQ_DISABLE(OS_IRQ_PA2));
   *(&NVIC->ISER[OS_IRQ_POSITION(OS_IRQ_PA3)]) = (uint32) (OS_IRQ_DISABLE(OS_IRQ_PA3));
   *(&NVIC->ISER[OS_IRQ_POSITION(OS_IRQ_PA4)]) = (uint32) (OS_IRQ_DISABLE(OS_IRQ_PA4));
}

/**
 *    \brief
 *    \param  -
 *    \return -
 */
void MotorControl_gv_Init()
{
   MotrolControl_v_TurnOffPwm();
}

void MotorControl_gv_Step1(uint16 DutyCylce)
{
   Pwm_SetDutyCycle(MOTORCONTROL_PHASE_AH, STD_LOW);
   Dio_WriteChannel(MOTORCONTROL_PHASE_AL, STD_LOW);
   Pwm_SetDutyCycle(MOTORCONTROL_PHASE_BH, STD_LOW);
   Dio_WriteChannel(MOTORCONTROL_PHASE_CL, STD_LOW);
   Dio_WriteChannel(MOTORCONTROL_PHASE_BL, STD_HIGH);
   Pwm_SetDutyCycle(MOTORCONTROL_PHASE_CH, DutyCylce);

}
void MotorControl_gv_Step2(uint16 DutyCylce)
{
   Dio_WriteChannel(MOTORCONTROL_PHASE_AL, STD_LOW);
   Pwm_SetDutyCycle(MOTORCONTROL_PHASE_BH, STD_LOW);
   Pwm_SetDutyCycle(MOTORCONTROL_PHASE_CH, STD_LOW);
   Dio_WriteChannel(MOTORCONTROL_PHASE_CL, STD_LOW);
   Pwm_SetDutyCycle(MOTORCONTROL_PHASE_AH, DutyCylce);
   Dio_WriteChannel(MOTORCONTROL_PHASE_BL, STD_HIGH);
}
void MotorControl_gv_Step3(uint16 DutyCylce)
{
   Dio_WriteChannel(MOTORCONTROL_PHASE_AL, STD_LOW);
   Pwm_SetDutyCycle(MOTORCONTROL_PHASE_BH, STD_LOW);
   Dio_WriteChannel(MOTORCONTROL_PHASE_BL, STD_LOW);
   Pwm_SetDutyCycle(MOTORCONTROL_PHASE_CH, STD_LOW);
   Dio_WriteChannel(MOTORCONTROL_PHASE_CL, STD_HIGH);
   Pwm_SetDutyCycle(MOTORCONTROL_PHASE_AH, DutyCylce);
}
void MotorControl_gv_Step4(uint16 DutyCylce)
{
   Pwm_SetDutyCycle(MOTORCONTROL_PHASE_AH, STD_LOW);
   Dio_WriteChannel(MOTORCONTROL_PHASE_AL, STD_LOW);
   Dio_WriteChannel(MOTORCONTROL_PHASE_BL, STD_LOW);
   Pwm_SetDutyCycle(MOTORCONTROL_PHASE_CH, STD_LOW);
   Pwm_SetDutyCycle(MOTORCONTROL_PHASE_BH, DutyCylce);
   Dio_WriteChannel(MOTORCONTROL_PHASE_CL, STD_HIGH);

}
void MotorControl_gv_Step5(uint16 DutyCylce)
{
   Pwm_SetDutyCycle(MOTORCONTROL_PHASE_AH, STD_LOW);
   Dio_WriteChannel(MOTORCONTROL_PHASE_BL, STD_LOW);
   Pwm_SetDutyCycle(MOTORCONTROL_PHASE_CH, STD_LOW);
   Dio_WriteChannel(MOTORCONTROL_PHASE_CL, STD_LOW);
   Dio_WriteChannel(MOTORCONTROL_PHASE_AL, STD_HIGH);
   Pwm_SetDutyCycle(MOTORCONTROL_PHASE_BH, DutyCylce);
}
void MotorControl_gv_Step6(uint16 DutyCylce)
{
   Pwm_SetDutyCycle(MOTORCONTROL_PHASE_AH, STD_LOW);
   Pwm_SetDutyCycle(MOTORCONTROL_PHASE_BH, STD_LOW);
   Dio_WriteChannel(MOTORCONTROL_PHASE_BL, STD_LOW);
   Dio_WriteChannel(MOTORCONTROL_PHASE_CL, STD_LOW);
   Pwm_SetDutyCycle(MOTORCONTROL_PHASE_CH, DutyCylce);
   Dio_WriteChannel(MOTORCONTROL_PHASE_AL, STD_HIGH);
}
void MotorControl_gv_BemfAFalling()
{
   *(&NVIC->ISER[OS_IRQ_POSITION(OS_IRQ_PA2)]) = (uint32) (OS_IRQ_ENABLE(OS_IRQ_PA2));

   *(&NVIC->ISER[OS_IRQ_POSITION(OS_IRQ_PA3)]) = (uint32) (OS_IRQ_DISABLE(OS_IRQ_PA3));
   *(&NVIC->ISER[OS_IRQ_POSITION(OS_IRQ_PA4)]) = (uint32) (OS_IRQ_DISABLE(OS_IRQ_PA4));

   *(&EXTI->RTSR) = (uint32) ~(EXTI_RTSR_TR2);
   *(&EXTI->FTSR) = (uint32) (EXTI_RTSR_TR2);
}
void MotorControl_gv_BemfARising()
{
   *(&NVIC->ISER[OS_IRQ_POSITION(OS_IRQ_PA2)]) = (uint32) (OS_IRQ_ENABLE(OS_IRQ_PA2));

   *(&NVIC->ISER[OS_IRQ_POSITION(OS_IRQ_PA3)]) = (uint32) (OS_IRQ_DISABLE(OS_IRQ_PA3));
   *(&NVIC->ISER[OS_IRQ_POSITION(OS_IRQ_PA4)]) = (uint32) (OS_IRQ_DISABLE(OS_IRQ_PA4));

   *(&EXTI->RTSR) = (uint32) (EXTI_RTSR_TR2);
   *(&EXTI->FTSR) = (uint32) ~(EXTI_RTSR_TR2);
}
void MotorControl_gv_BemfBFalling()
{
   *(&NVIC->ISER[OS_IRQ_POSITION(OS_IRQ_PA3)]) = (uint32) (OS_IRQ_ENABLE(OS_IRQ_PA3));

   *(&NVIC->ISER[OS_IRQ_POSITION(OS_IRQ_PA2)]) = (uint32) (OS_IRQ_DISABLE(OS_IRQ_PA2));
   *(&NVIC->ISER[OS_IRQ_POSITION(OS_IRQ_PA4)]) = (uint32) (OS_IRQ_DISABLE(OS_IRQ_PA4));

   *(&EXTI->RTSR) = (uint32) ~(EXTI_RTSR_TR3);
   *(&EXTI->FTSR) = (uint32) (EXTI_RTSR_TR3);
}
void MotorControl_gv_BemfBRising()
{
   *(&NVIC->ISER[OS_IRQ_POSITION(OS_IRQ_PA3)]) = (uint32) (OS_IRQ_ENABLE(OS_IRQ_PA3));

   *(&NVIC->ISER[OS_IRQ_POSITION(OS_IRQ_PA2)]) = (uint32) (OS_IRQ_DISABLE(OS_IRQ_PA2));
   *(&NVIC->ISER[OS_IRQ_POSITION(OS_IRQ_PA4)]) = (uint32) (OS_IRQ_DISABLE(OS_IRQ_PA4));

   *(&EXTI->RTSR) = (uint32) (EXTI_RTSR_TR3);
   *(&EXTI->FTSR) = (uint32) ~(EXTI_RTSR_TR3);
}
void MotorControl_gv_BemfCFalling()
{
   *(&NVIC->ISER[OS_IRQ_POSITION(OS_IRQ_PA4)]) = (uint32) (OS_IRQ_ENABLE(OS_IRQ_PA4));

   *(&NVIC->ISER[OS_IRQ_POSITION(OS_IRQ_PA2)]) = (uint32) (OS_IRQ_DISABLE(OS_IRQ_PA2));
   *(&NVIC->ISER[OS_IRQ_POSITION(OS_IRQ_PA3)]) = (uint32) (OS_IRQ_DISABLE(OS_IRQ_PA3));

   *(&EXTI->RTSR) = (uint32) ~(EXTI_RTSR_TR4);
   *(&EXTI->FTSR) = (uint32) (EXTI_RTSR_TR4);
}
void MotorControl_gv_BemfCRising()
{
   *(&NVIC->ISER[OS_IRQ_POSITION(OS_IRQ_PA4)]) = (uint32) (OS_IRQ_ENABLE(OS_IRQ_PA4));

   *(&NVIC->ISER[OS_IRQ_POSITION(OS_IRQ_PA2)]) = (uint32) (OS_IRQ_DISABLE(OS_IRQ_PA2));
   *(&NVIC->ISER[OS_IRQ_POSITION(OS_IRQ_PA3)]) = (uint32) (OS_IRQ_DISABLE(OS_IRQ_PA3));

   *(&EXTI->RTSR) = (uint32) (EXTI_RTSR_TR4);
   *(&EXTI->FTSR) = (uint32) ~(EXTI_RTSR_TR4);
}

void MotorControl_gv_Move(uint8 Step, uint16 DutyCylce)
{
   switch (Step)
   {
      case 0:
      /* CH-BL */

      MotorControl_gv_Step1(DutyCylce);
      MotorControl_gv_BemfARising();
         break;
      case 1:
      /* AH-BL */

      MotorControl_gv_Step2(DutyCylce);
      MotorControl_gv_BemfCFalling();
         break;
      case 2:
      /* AH-CL */

      MotorControl_gv_Step3(DutyCylce);
      MotorControl_gv_BemfBRising();
         break;
      case 3:
      /* BH-CL */

      MotorControl_gv_Step4(DutyCylce);
      MotorControl_gv_BemfAFalling();
         break;
      case 4:
      /* BH-AL */

      MotorControl_gv_Step5(DutyCylce);
      MotorControl_gv_BemfCRising();
         break;
      case 5:
      /* CH-AL */

      MotorControl_gv_Step6(DutyCylce);
      MotorControl_gv_BemfBFalling();
         break;
      default:
      MotrolControl_v_TurnOffPwm();
         break;

   }
}

/*    /brief
 *    /param
 *    /return
 */
void MotorControl_gv_AlignRoutine(const MotorControl_ConfigType *ConfigPtr, uint8 Step)
{
   Pwm_SetDutyCycle(MOTORCONTROL_PHASE_AH, 0x00);
   Pwm_SetDutyCycle(MOTORCONTROL_PHASE_BH, 0x00);
   Dio_WriteChannel(MOTORCONTROL_PHASE_CL, 0x00);

   Pwm_SetDutyCycle(MOTORCONTROL_PHASE_CH, (uint16) ConfigPtr->pt_ConfigGroup[Step].t_Value);
   Dio_WriteChannel(MOTORCONTROL_PHASE_BL, STD_HIGH);
   Dio_WriteChannel(MOTORCONTROL_PHASE_AL, STD_HIGH);
}

/*
 *  /brief
 *  /param
 *  /return
 */
void MotorControl_gv_SetRampUpTime(const MotorControl_ConfigType *ConfigPtr, uint8 Step)
{
   TIM2->CNT = 0x00;
   TIM2->ARR = ConfigPtr->pt_ConfigGroup[Step].t_Time;
}

void MotorControl_gv_EnableStartSequence()
{
   TIM2->CNT = 0x00;
   TIM2->CNT |= MOTORCONTROL_TIMER_VALUE;
   TIM2->ARR |= MOTORCONTROL_TIMER_VALUE;
   TIM2->DIER |= TIM_DIER_UIE;
   TIM2->CR1 |= TIM_CR1_CEN;
}
void MotorControl_gv_DisableStartSequence()
{
   TIM2->DIER &= ~TIM_DIER_UIE;
   TIM2->SR &= ~TIM_SR_UIF;
}

void MotorControl_gv_EnableAlignSequence()
{
   TIM5->DIER |= TIM_DIER_UIE;
}

void MotorControl_gv_DisableAlignSequence()
{
   TIM5->DIER &= ~TIM_DIER_UIE;
   TIM5->SR &= ~TIM_SR_UIF;
}
