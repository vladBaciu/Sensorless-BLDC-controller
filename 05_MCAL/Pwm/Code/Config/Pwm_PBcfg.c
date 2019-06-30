/*-------------------------------------------------------------------------------------------------------------------*/
/**
 *    \file       Pwm_PBcfg.c
 *    \author     Baciu Vlad-Eusebiu
 *    \brief      Implements the register configuration array  and post build configuration.
 */
/*-------------------------------------------------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------------------------------------------------*/
/*                                                     Inclusions                                                    */
/*-------------------------------------------------------------------------------------------------------------------*/
#include "Pwm.h"
#include "Pwm_Cfg.h"
#include "MotorControl.h"
/*-------------------------------------------------------------------------------------------------------------------*/
/*                                             Definition Of Local Macros                                            */
/*-------------------------------------------------------------------------------------------------------------------*/
/** \brief Number of PWM registers from configuration array*/
#define PWM_NUMBER_OF_REGISTERS        (30U)

/** \brief Preload value for ARR register*/
#define PWM_TIM_ARR_PRELOAD                (0xFFFFFFFFU)

/** \brief Value that sets the frequency of the PWM signal
 *   Formula: ARR_Value = desired period/ clock period
 *   Notes:   clock period: 1/clock frequency.Where clock frequency is 80 MHz.
 *            desired period: 1/pwm frequency
 *   For example:
 *            The desired frequency is 20 kHz. That means that the period is 1/20 kHz =  50 uS
 *            Clock frequency equals 80 MHz.   That means that the perios is 1/80 MHz =  12.5 nS
 *            ARR_Value = 50 uS/12.5 nS or 50uS/0.0125 us = 4000 (decimal) or 0xFA0U (hexadecimal)
 *
 *
 */

/*                                           TIM4 MACROS                                                             */

/** \brief  TIM8 direction of counting */
#define PWM_TIM4_DIRECTION        (0U << 4)

/** \brief  Clock prescaler for TIM8 */
#define PWM_TIM4_PRESCALER        (2U)

/** \brief  Prescaler value to be written in PSC register */
#define PWM_TIM4_PRESCALER_REGISTER_VALUE (PWM_TIM4_PRESCALER - 1)

/** \brief ARR register value */
#define PWM_TIM4_ARR_FREQUENCY       (2000U)

/** \brief  TIMER 1 duty cycle start value */
#define PWM_TIM4_CCR_START_VALUE     (0x00U)

/*                                           TIM3 MACROS                                                             */

/** \brief  TIMER 3 direction of counting */
#define PWM_TIM3_DIRECTION        (0U << 4)

/** \brief  TIMER 3 prescaler value */
#define PWM_TIM3_PRESCALER        (2U)

/** \brief  Prescaler value to be written in PSC register */
#define PWM_TIM3_PRESCALER_REGISTER_VALUE  (PWM_TIM3_PRESCALER - 1)

/** \brief ARR register value */
#define PWM_TIM3_ARR_FREQUENCY    (2000U)

/** \brief  TIMER 3 duty cycle start value */
#define PWM_TIM3_CCR_START_VALUE  (0U)

/*                                           TIM2 MACROS                                                             */

/** \brief  TIMER 2 direction of counting */
#define PWM_TIM2_DIRECTION        (0U << 4)

/** \brief  TIMER 2 prescaler value */
#define PWM_TIM2_PRESCALER        (8U)

/** \brief  Prescaler value to be written in PSC register */
#define PWM_TIM2_PRESCALER_REGISTER_VALUE   (PWM_TIM2_PRESCALER - 1)

/** \brief ARR register value */
#define PWM_TIM2_ARR_FREQUENCY       (MOTORCONTROL_TIMER_VALUE)

/*                                           TIM5 MACROS                                                             */

/** \brief  TIMER 2 direction of counting */
#define PWM_TIM5_DIRECTION        (0U << 4)

/** \brief  TIMER 2 prescaler value */
#define PWM_TIM5_PRESCALER        (8U)

/** \brief  Prescaler value to be written in PSC register */
#define PWM_TIM5_PRESCALER_REGISTER_VALUE   (PWM_TIM5_PRESCALER - 1)

/** \brief ARR register value */
#define PWM_TIM5_ARR_FREQUENCY       (MOTOR_TIMER_ALIGNMENT_VALUE)

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
/** \brief PWM channels configuration array */
static const Pwm_CfgType Pwm_kat_CfgType[PWM_NUMBER_OF_CHANNELS] =
{

/* PWM CHANNEL PB5, TIMER MODULE 2, COMPARE UNIT 2 */
   { (uint32*) &TIM3->CCR2, TIM3 },
   /* PWM CHANNEL PB7, TIMER MODULE 4, COMPARE UNIT 2 */
   { (uint32*) &TIM4->CCR2, TIM4 },
   /* PWM CHANNEL PB9, TIMER MODULE 4, COMPARE UNIT 4 */
   { (uint32*) &TIM4->CCR4, TIM4 },

};

/** \brief Register configuration array */
static const RegInit_Masked32BitsSingleType Pwm_kat_Registers[PWM_NUMBER_OF_REGISTERS] =
{

/*                                        TIMER 2 CONFIGURATION                                                */

/**
 *    Configuration of TIM2_CR1 register
 *    - Set the counting direction as 'upcounter'
 *          0: Upcounter
 *          1: Downcounter
 *
 */

{
   (volatile uint32*) &TIM2->CR1,

   (uint32) ~(TIM_CR1_DIR),

   (uint32) (PWM_TIM2_DIRECTION)
},

/**
 *    Configuration of TIM2_EGR register
 *    - Set update generation to restart the counter after it has reached its peak value.
 *          0: No action
 *          1: Re-initialize the counter
 *
 *
 */

{
   (volatile uint32*) &TIM2->EGR,

   (uint32) ~(TIM_EGR_UG),

   (uint32) (TIM_EGR_UG)
},

/**
 *    Configuration of TIM2_PSC register
 *    - Set prescaler value to 0.
 *          Range:                   0 to 0xFFFF
 *          Divided clock frequency: fCK_PSC / (PSC[15:0] + 1).
 *
 *
 */

{
   (volatile uint32*) &TIM2->PSC,

   (uint32) ~(TIM_PSC_PSC),

   (uint32) (PWM_TIM2_PRESCALER_REGISTER_VALUE)
},

/**
 *    Configuration of TIM2_ARR register
 *    - Set auto-reload value to 0xFA0.
 *
 *
 */
{
   (volatile uint32*) &TIM2->ARR,

   (uint32) ~(PWM_TIM_ARR_PRELOAD),

   (uint32) (PWM_TIM2_ARR_FREQUENCY)
},

/**
 *    Configuration of TIM2_CR1 register
 *    - Set the counter enable register to 1
 *          0: Counter disabled
 *          1: Counter enabled
 *
 */
{
   (volatile uint32*) &TIM2->CR1,

   (uint32) ~(TIM_CR1_CEN),

   (uint32) (0x00)
},
   /**
    *    Enable interrupts for TIM2 overflow.
    */
   {
      (volatile uint32*) &TIM2->DIER,

      (uint32) ~(TIM_DIER_UIE),

      (uint32) (0x00)
   },

   /*                                        TIMER 3 CONFIGURATION                                                */
   /**
    *    Configuration of TIM2_CR1 register
    *    - Set the counting direction as 'upcounter'
    *          0: Upcounter
    *          1: Downcounter
    *
    */

   {
      (volatile uint32*) &TIM3->CR1,

      (uint32) ~(TIM_CR1_DIR),

      (uint32) (PWM_TIM3_DIRECTION)
   },

   /**
    *    Configuration of TIM3_EGR register
    *    - Set update generation to restart the counter after it has reached its peak value.
    *          0: No action
    *          1: Re-initialize the counter
    *
    *
    */

   {
      (volatile uint32*) &TIM3->EGR,

      (uint32) ~(TIM_EGR_UG),

      (uint32) (TIM_EGR_UG)
   },

   /**
    *    Configuration of TIM3_PSC register
    *    - Set prescaler value to 0.
    *          Range:                   0 to 0xFFFF
    *          Divided clock frequency: fCK_PSC / (PSC[15:0] + 1).
    *
    *
    */

   {
      (volatile uint32*) &TIM3->PSC,

      (uint32) ~(TIM_PSC_PSC),

      (uint32) (PWM_TIM3_PRESCALER_REGISTER_VALUE)
   },

   /**
    *    Configuration of TIM3_ARR register
    *    - Set auto-reload value to 0x3E80.
    *
    *
    */
   {
      (volatile uint32*) &TIM3->ARR,

      (uint32) ~(PWM_TIM_ARR_PRELOAD),

      (uint32) (PWM_TIM3_ARR_FREQUENCY)
   },

   /**
    *    Configuration of TIM3_CR1 register
    *    - Set the counter enable register to 1
    *          0: Counter disabled
    *          1: Counter enabled
    *
    */
   {
      (volatile uint32*) &TIM3->CR1,

      (uint32) ~(TIM_CR1_CEN),

      (uint32) (TIM_CR1_CEN)
   },

   /**
    *    Configuration of TIM3_CCMR1 register
    *    - Set the PWM mode 1
    *          110: PWM mode 1 - In upcounting, channel 1 is active as long as TIMx_CNT<TIMx_CCR1
    *               else inactive. In downcounting, channel 1 is inactive (OC1REF=‘0’) as long as
    *               TIMx_CNT>TIMx_CCR1 else active (OC1REF=’1’).
    *          111: PWM mode 2 - In upcounting, channel 1 is inactive as long as TIMx_CNT<TIMx_CCR1
    *               else active. In downcounting, channel 1 is active as long as TIMx_CNT>TIMx_CCR1 else
    *               inactive.
    *
    */
   {
      (volatile uint32*) &TIM3->CCMR1,

      (uint32) ~(
      TIM_CCMR1_OC2PE |
      TIM_CCMR1_OC2M_2 |
      TIM_CCMR1_OC2M_1),

      (uint32) (
      TIM_CCMR1_OC2PE |
      TIM_CCMR1_OC2M_2 |
      TIM_CCMR1_OC2M_1)
   },

   /**
    *    Configuration of TIM3_CCER register
    *    - Set capture/compare enable register. Enable CC2E: Capture/Compare 2 output enable.
    *
    */
   {
      (volatile uint32*) &TIM3->CCER,

      (uint32) ~(TIM_CCER_CC2E),

      (uint32) (TIM_CCER_CC2E)
   },

   /**
    *    Configuration of TIM3_CCR2 register. While initialization the duty cycle is set to 0.
    *
    */
   {
      (volatile uint32*) &TIM3->CCR2,

      (uint32) ~(TIM_CCR2_CCR2),

      (uint32) (PWM_TIM3_CCR_START_VALUE)
   },

   /*                                        TIMER 4 CONFIGURATION                                                */
   /**
    *    Configuration of TIM4_CR1 register
    *    - Set the counting direction as 'upcounter'
    *          0: Upcounter
    *          1: Downcounter
    *
    */

   {
      (volatile uint32*) &TIM4->CR1,

      (uint32) ~(TIM_CR1_DIR),

      (uint32) (PWM_TIM4_DIRECTION)
   },

   /**
    *    Configuration of TIM4_EGR register
    *    - Set update generation to restart the counter after it has reached its peak value.
    *          0: No action
    *          1: Re-initialize the counter
    *
    *
    */

   {
      (volatile uint32*) &TIM4->EGR,

      (uint32) ~(TIM_EGR_UG),

      (uint32) (TIM_EGR_UG)
   },

   /**
    *    Configuration of TIM4_PSC register
    *    - Set prescaler value to 0.
    *          Range:                   0 to 0xFFFF
    *          Divided clock frequency: fCK_PSC / (PSC[15:0] + 1).
    *
    *
    */

   {
      (volatile uint32*) &TIM4->PSC,

      (uint32) ~(TIM_PSC_PSC),

      (uint32) (PWM_TIM4_PRESCALER_REGISTER_VALUE)
   },

   /**
    *    Configuration of TIM4_ARR register
    *    - Set auto-reload value to 0x3E80.
    *
    *
    */
   {
      (volatile uint32*) &TIM4->ARR,

      (uint32) ~(PWM_TIM_ARR_PRELOAD),

      (uint32) (PWM_TIM4_ARR_FREQUENCY)
   },

   /**
    *    Configuration of TIM4_CR1 register
    *    - Set the counter enable register to 1
    *          0: Counter disabled
    *          1: Counter enabled
    *
    */
   {
      (volatile uint32*) &TIM4->CR1,

      (uint32) ~(TIM_CR1_CEN),

      (uint32) (TIM_CR1_CEN)
   },

   /**
    *    Configuration of TIM4_CCMR1 register
    *    - Set the PWM mode 1
    *          110: PWM mode 1 - In upcounting, channel 1 is active as long as TIMx_CNT<TIMx_CCR1
    *               else inactive. In downcounting, channel 1 is inactive (OC1REF=‘0’) as long as
    *               TIMx_CNT>TIMx_CCR1 else active (OC1REF=’1’).
    *          111: PWM mode 2 - In upcounting, channel 1 is inactive as long as TIMx_CNT<TIMx_CCR1
    *               else active. In downcounting, channel 1 is active as long as TIMx_CNT>TIMx_CCR1 else
    *               inactive.
    *
    */
   {
      (volatile uint32*) &TIM4->CCMR1,

      (uint32) ~(
      TIM_CCMR1_OC2PE |
      TIM_CCMR1_OC2M_2 |
      TIM_CCMR1_OC2M_1),

      (uint32) (
      TIM_CCMR1_OC2PE |
      TIM_CCMR1_OC2M_2 |
      TIM_CCMR1_OC2M_1)
   },

   {
      (volatile uint32*) &TIM4->CCMR2,

      (uint32) ~(
      TIM_CCMR2_OC4PE |
      TIM_CCMR2_OC4M_2 |
      TIM_CCMR2_OC4M_1),

      (uint32) (
      TIM_CCMR2_OC4PE |
      TIM_CCMR2_OC4M_2 |
      TIM_CCMR2_OC4M_1)
   },

   /**
    *    Configuration of TIM4_CCER register
    *    - Set capture/compare enable register. Enable CC2E: Capture/Compare 2 output enable.
    *
    */
   {
      (volatile uint32*) &TIM4->CCER,

      (uint32) ~(
      TIM_CCER_CC2E |
      TIM_CCER_CC4E),

      (uint32) (
      TIM_CCER_CC2E |
      TIM_CCER_CC4E)
   },

   /**
    *    Configuration of TIM4_CCR2 register. While initialization the duty cycle is set to 0.
    *
    */
   {
      (volatile uint32*) &TIM4->CCR2,

      (uint32) ~(TIM_CCR2_CCR2),

      (uint32) (PWM_TIM4_CCR_START_VALUE)
   },

   /**
    *    Configuration of TIM4_CCR4 register. While initialization the duty cycle is set to 0.
    *
    */
   {
      (volatile uint32*) &TIM4->CCR4,

      (uint32) ~(TIM_CCR4_CCR4),

      (uint32) (PWM_TIM4_CCR_START_VALUE)
   },

   /*                                        TIMER 5 CONFIGURATION                                                */

   /**
    *    Configuration of TIM5_CR1 register
    *    - Set the counting direction as 'upcounter'
    *          0: Upcounter
    *          1: Downcounter
    *
    */

   {
      (volatile uint32*) &TIM5->CR1,

      (uint32) ~(TIM_CR1_DIR),

      (uint32) (PWM_TIM5_DIRECTION)
   },

   /**
    *    Configuration of TIM5_EGR register
    *    - Set update generation to restart the counter after it has reached its peak value.
    *          0: No action
    *          1: Re-initialize the counter
    *
    *
    */

   {
      (volatile uint32*) &TIM5->EGR,

      (uint32) ~(TIM_EGR_UG),

      (uint32) (TIM_EGR_UG)
   },

   /**
    *    Configuration of TIM5_PSC register
    *    - Set prescaler value to 0.
    *          Range:                   0 to 0xFFFF
    *          Divided clock frequency: fCK_PSC / (PSC[15:0] + 1).
    *
    *
    */

   {
      (volatile uint32*) &TIM5->PSC,

      (uint32) ~(TIM_PSC_PSC),

      (uint32) (PWM_TIM5_PRESCALER_REGISTER_VALUE)
   },

   /**
    *    Configuration of TIM5_ARR register
    *    - Set auto-reload value to 0xFA0.
    *
    *
    */
   {
      (volatile uint32*) &TIM5->ARR,

      (uint32) ~(PWM_TIM_ARR_PRELOAD),

      (uint32) (PWM_TIM5_ARR_FREQUENCY)
   },

   /**
    *    Configuration of TIM5_CR1 register
    *    - Set the counter enable register to 1
    *          0: Counter disabled
    *          1: Counter enabled
    *
    */
   {
      (volatile uint32*) &TIM5->CR1,

      (uint32) ~(TIM_CR1_CEN),

      (uint32) (TIM_CR1_CEN)
   },
   /**
    *    Enable interrupts for TIM5 overflow.
    */
   {
      (volatile uint32*) &TIM5->DIER,

      (uint32) ~(TIM_DIER_UIE),

      (uint32) (0x00)
   },

};

/** \brief PWM register config array */
static const RegInit_Masked32BitsConfigType Pwm_kt_ConfigRegisters =
{
   Pwm_kat_Registers,
   PWM_NUMBER_OF_REGISTERS
};
/*-------------------------------------------------------------------------------------------------------------------*/
/*                                          Declaration Of Global Constants                                          */
/*-------------------------------------------------------------------------------------------------------------------*/

/** \brief  PWM post-build configuration */
const Pwm_ConfigType Pwm_gkt_Config =
{
   Pwm_kat_CfgType,
   &Pwm_kt_ConfigRegisters,
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
