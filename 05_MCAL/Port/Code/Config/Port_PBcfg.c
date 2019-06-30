/*-------------------------------------------------------------------------------------------------------------------*/
/**
 *    \file       Port_PBcfg.c
 *    \author     Baciu Vlad-Eusebiu
 *    \brief      Implements the configuration set for the GPIO registers and the configuration structure of the
 *                port module.
 */
/*-------------------------------------------------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------------------------------------------------*/
/*                                                     Inclusions                                                    */
/*-------------------------------------------------------------------------------------------------------------------*/
#include "stm32f407xx.h"
#include "RegInit.h"
#include "Port.h"
/*-------------------------------------------------------------------------------------------------------------------*/
/*                                             Definition Of Local Macros                                            */
/*-------------------------------------------------------------------------------------------------------------------*/
/** \brief Number of used PORT registers */
#define PORT_NUMBER_OF_REGISTERS                        (13U)
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
/** \brief Stores the configuration of all the registers to be set in the PORT initialization function. */
static const RegInit_Masked32BitsSingleType Port_gkt_Registers[PORT_NUMBER_OF_REGISTERS] =
{
   /*                                   GPIOA PORT CONFIGURATION                                                     */
   /**
    * REMINDER:
    * 00: input
    * 01: general purpose output mode
    * 10: alternate function:
    * 11: analog mode
    *
    * GPIOA PORT CONFIGURATION
    * Set:
    *
    *  PA0 as input   (Joystick button)
    *  PA2 as input   (EXTI)
    *  PA3 as input   (EXTI)
    *  PA4 as input   (EXTI)
    *  PA6 as analog  (Current sensor).
    *  */
   {
      &GPIOA->MODER,
      (uint32) ~(
      GPIO_MODER_MODER0 |
      GPIO_MODER_MODER2 |
      GPIO_MODER_MODER3 |
      GPIO_MODER_MODER4 |
      GPIO_MODER_MODER6),

      (uint32) (GPIO_MODER_MODER6)
   },
   /*                                 GPIOA PIN SPEED CONFIGURATION                                                  */
   /**
    * Set:
    *
    *    PA0 to very high speed.
    *    PA2 to very high speed.
    *    PA3 to very high speed.
    *    PA4 to very high speed.
    *  */
   {
      &GPIOA->OSPEEDR,
      (uint32) ~(
      GPIO_OSPEEDER_OSPEEDR0 |
      GPIO_OSPEEDER_OSPEEDR2 |
      GPIO_OSPEEDER_OSPEEDR3 |
      GPIO_OSPEEDER_OSPEEDR4 |
      GPIO_OSPEEDER_OSPEEDR6
      ),

      (uint32) (
      GPIO_OSPEEDER_OSPEEDR0 |
      GPIO_OSPEEDER_OSPEEDR2 |
      GPIO_OSPEEDER_OSPEEDR3 |
      GPIO_OSPEEDER_OSPEEDR4 |
      GPIO_OSPEEDER_OSPEEDR6),
   },
   /*                                      GPIOB PORT CONFIGURATION                                                   */

   /**
    * GPIOB MODER CONFIGURATION
    * Set:
    *    PB0 as output      (Read battery command)
    *    PB5 as PWM output  (AH motor control)
    *    PB7 as PWM output  (BH motor control)
    *    PB9 as PWM output  (CH motor control)
    *    PB11 as output     (for LCD)
    * */
   {
      &GPIOB->MODER,
      (uint32) ~(
      GPIO_MODER_MODER0 |
      GPIO_MODER_MODER5 |
      GPIO_MODER_MODER7 |
      GPIO_MODER_MODER9 |
      GPIO_MODER_MODER11),

      (uint32) (
      GPIO_MODER_MODER0_0 |
      GPIO_MODER_MODER5_1 |
      GPIO_MODER_MODER7_1 |
      GPIO_MODER_MODER9_1 |
      GPIO_MODER_MODER11_0)
   },

   /**
    * GPIOB PIN SPEED CONFIGURATION
    * Set:
    *
    *    PB5 to very high.
    *    PB7 to very high.
    *    PB9 to very high.
    *    PB11 to very high.
    *  */
   {
      &GPIOB->OSPEEDR,
      (uint32) ~(
      GPIO_OSPEEDER_OSPEEDR0 |
      GPIO_OSPEEDER_OSPEEDR5 |
      GPIO_OSPEEDER_OSPEEDR7 |
      GPIO_OSPEEDER_OSPEEDR9 |
      GPIO_OSPEEDER_OSPEEDR11),

      (uint32) (
      GPIO_OSPEEDER_OSPEEDR0 |
      GPIO_OSPEEDER_OSPEEDR5 |
      GPIO_OSPEEDER_OSPEEDR7 |
      GPIO_OSPEEDER_OSPEEDR9 |
      GPIO_OSPEEDER_OSPEEDR11)
   },

   /**
    *                               GPIOB PIN ALTERNATE FUNCTION CONFIGURATION
    * Set:
    *
    *    PB5 - AF2 (TIM3_CH2)
    *    PB7 - AF2 (TIM4_CH2)
    *    PB9 - AF2 (TIM4_CH4)
    *  */

   {
      &GPIOB->AFRL,
      (uint32) ~(
      GPIO_AFRL_AFRL5 |
      GPIO_AFRL_AFRL7),

      (uint32) (
      GPIO_AFRL_AFRL5_1 |
      GPIO_AFRL_AFRL7_1)

   },

   {
      &GPIOB->AFRH,
      (uint32) ~(
      GPIO_AFRH_AFRH9),

      (uint32) (
      GPIO_AFRH_AFRH9_1)

   },

   /*                                          GPIOC PORT CONFIGURATION                                               */
   /**
    *
    * Set:
    *
    *    PC0 as analog  (Joystick ADC)
    *    PC2 as analog  (Joystick ADC)
    *    PC4 as analog  (Battery ADC)
    *    PC10 as alternate function (UART)
    *    PC11 as alternate function (UART)
    * */
   {
      &GPIOC->MODER,
      (uint32) ~(
      GPIO_MODER_MODER0 |
      GPIO_MODER_MODER2 |
      GPIO_MODER_MODER4) |
      GPIO_MODER_MODER10 |
      GPIO_MODER_MODER11,
      (uint32) (
      GPIO_MODER_MODER0 |
      GPIO_MODER_MODER2 |
      GPIO_MODER_MODER4 |
      GPIO_MODER_MODER10_1 |
      GPIO_MODER_MODER11_1)
   },
   /*                                     GPIOC PIN SPEED CONFIGURATION                                              */
   /**
    * Set:
    *
    *     PC0 to very high speed.
    *     PC2 to very high speed.
    *     PC4 to very high speed.
    *     PC10 to very medium speed.
    *     PC11 to very medium speed.
    *  */
   {
      &GPIOC->OSPEEDR,
      (uint32) ~(
      GPIO_OSPEEDER_OSPEEDR0 |
      GPIO_OSPEEDER_OSPEEDR2 |
      GPIO_OSPEEDER_OSPEEDR4 |
      GPIO_OSPEEDER_OSPEEDR10 |
      GPIO_OSPEEDER_OSPEEDR11),
      (uint32) (
      GPIO_OSPEEDER_OSPEEDR0 |
      GPIO_OSPEEDER_OSPEEDR2 |
      GPIO_OSPEEDER_OSPEEDR4 |
      GPIO_OSPEEDER_OSPEEDR10_1 |
      GPIO_OSPEEDER_OSPEEDR11_1)
   },
   /*                               GPIOB PIN ALTERNATE FUNCTION CONFIGURATION                                        */
   {
   &GPIOC->AFRH,
   (uint32) ~(
   GPIO_AFRH_AFRH10 |
   GPIO_AFRH_AFRH11),
   (uint32) (
   GPIO_AFRH_AFRH10_3|
   GPIO_AFRH_AFRH11_3)
   },
   /*                                     GPIOD PORT CONFIGURATION                                                    */
   /**
    *
    * Set:
    *
    *    PD0 as output   (AL motor control)
    *    PD2 as output   (BL motor control)
    *    PD4 as output   (CL motor control)
    *    PD11 as output  (Led indicator)
    *    PD13 as output  (Led indicator)
    *    PD15 as output  (Led indicator)
    * */
   {
      &GPIOD->MODER,
      (uint32) ~(
      GPIO_MODER_MODER0 |
      GPIO_MODER_MODER2 |
      GPIO_MODER_MODER4 |
      GPIO_MODER_MODER11 |
      GPIO_MODER_MODER13 |
      GPIO_MODER_MODER15),
      (uint32) (
      GPIO_MODER_MODER0_0 |
      GPIO_MODER_MODER2_0 |
      GPIO_MODER_MODER4_0 |
      GPIO_MODER_MODER11_0 |
      GPIO_MODER_MODER13_0 |
      GPIO_MODER_MODER15_0)
   },

   /*                                     GPIOD PIN SPEED CONFIGURATION                                              */
   /**
    * Set:
    *
    *    PD0 to very high speed.
    *    PD2 to very high speed.
    *    PD4 to very high speed.
    *  */
   {
      &GPIOD->OSPEEDR,
      (uint32) ~(
      GPIO_OSPEEDER_OSPEEDR0 |
      GPIO_OSPEEDER_OSPEEDR2 |
      GPIO_OSPEEDER_OSPEEDR4 |
      GPIO_OSPEEDER_OSPEEDR11 |
      GPIO_OSPEEDER_OSPEEDR13 |
      GPIO_OSPEEDER_OSPEEDR15),
      (uint32) (
      GPIO_OSPEEDER_OSPEEDR0 |
      GPIO_OSPEEDER_OSPEEDR2 |
      GPIO_OSPEEDER_OSPEEDR4 |
      GPIO_OSPEEDER_OSPEEDR11 |
      GPIO_OSPEEDER_OSPEEDR13 |
      GPIO_OSPEEDER_OSPEEDR15)
   },

   /*                                     GPIOE PORT CONFIGURATION                                                    */
   /**
    * Set:
    *
    *    PE7 as output (LCD)
    *    PE9 as output (LCD)
    *    PE11 as output (LCD)
    *    PE13 as output (LCD)
    *    PE15 as output (LCD)
    **/

   {
      &GPIOE->MODER,
      (uint32) ~(
      GPIO_MODER_MODER7 |
      GPIO_MODER_MODER9 |
      GPIO_MODER_MODER11 |
      GPIO_MODER_MODER13 |
      GPIO_MODER_MODER15),

      (uint32) (
      GPIO_MODER_MODER7_0 |
      GPIO_MODER_MODER9_0 |
      GPIO_MODER_MODER11_0 |
      GPIO_MODER_MODER13_0 |
      GPIO_MODER_MODER15_0)
   },

   {
      &GPIOD->OSPEEDR,
      (uint32) ~(
      GPIO_OSPEEDER_OSPEEDR7 |
      GPIO_OSPEEDER_OSPEEDR9 |
      GPIO_OSPEEDER_OSPEEDR11 |
      GPIO_OSPEEDER_OSPEEDR13 |
      GPIO_OSPEEDER_OSPEEDR15),

      (uint32) (
      GPIO_OSPEEDER_OSPEEDR7 |
      GPIO_OSPEEDER_OSPEEDR9 |
      GPIO_OSPEEDER_OSPEEDR11 |
      GPIO_OSPEEDER_OSPEEDR13 |
      GPIO_OSPEEDER_OSPEEDR15)
   },

};

/** \brief  References the configuration of all the registers to be set in the PORT initialization function and the
 *          number of registers to be initialized. */
const Port_ConfigType Port_gkt_Config =
{
   Port_gkt_Registers,
   PORT_NUMBER_OF_REGISTERS
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
