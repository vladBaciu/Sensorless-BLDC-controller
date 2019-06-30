/*-------------------------------------------------------------------------------------------------------------------*/
/**
 *    \file       Adc_PBcfg.c
 *    \author     Baciu Vlad-Eusebiu
 *    \brief      Implements the configuration set for the ADC registers and the configuration structure of the
 *                ADC module.
 */
/*-------------------------------------------------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------------------------------------------------*/
/*                                                     Inclusions                                                    */
/*-------------------------------------------------------------------------------------------------------------------*/
#include "Adc.h"
#include "Adc_Cfg.h"
/*-------------------------------------------------------------------------------------------------------------------*/
/*                                             Definition Of Local Macros                                            */
/*-------------------------------------------------------------------------------------------------------------------*/
/** \brief Number of registers to be configured */
#define ADC_NUMBER_OF_REGISTERS           (9U)

/** \brief Channel 10 index in ADC2 module */
#define ADC_ADC2_CH10                      (10U)

/** \brief Channel 12 index in ADC1 module */
#define ADC_ADC2_CH12                      (12U)

/** \brief Channel 6 index in ADC1 module */
#define ADC_ADC2_CH6                       (6U)

/** \brief Channel 14 index in ADC1 module */
#define ADC_ADC2_CH14                       (14U)

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

/** \brief Group configuration array */
static const Adc_GroupCfgType Adc_kat_AdcGroups[ADC_NUMBER_OF_GROUPS] =
{
   /* ADC group 0 : ADC2_CH10 - PC0 pin */
   { ADC_ADC2_CH10, ADC2 },
   /* ADC group 2 : ADC2_CH12 - PC2 pin */
   { ADC_ADC2_CH12, ADC2 },
   /* ADC group 2 : ADC2_CH6  - PA6 pin */
   { ADC_ADC2_CH6, ADC2 },
   /* ADC group 2 : ADC2_CH14  - PC4 pin */
   { ADC_ADC2_CH14, ADC2 }
};

/** \brief Register configuration array */
static const RegInit_Masked32BitsSingleType Adc_kat_Registers[ADC_NUMBER_OF_REGISTERS] =
{
   /**
    *    Configuration of ADC1_SQR1 register
    *    - Set the regular channel sequence length.
    *
    */

   {
      (volatile uint32*) &ADC1->SQR1,

      (uint32) ~(ADC_SQR1_L),

      (uint32) (0x00)
   },
   /**
    *    Configuration of ADC1_CR1 register
    *    - Set ADC1 in discontinuous mode
    *    - Set the resolution of the conversion to 12 bits.
    */
   {
      (volatile uint32*) &ADC1->CR1,

      (uint32) ~(
      ADC_CR1_DISCEN |
      ADC_CR1_RES),

      (uint32) (ADC_CR1_DISCEN)

   },

   /**
    *    Configuration of ADC1_SMPR2 register
    *    - Set the sampling time of the channel 1 to 144 cycles
    *    -
    */
   {
      (volatile uint32*) &ADC1->SMPR2,

      (uint32) ~(
      ADC_SMPR2_SMP0_1 |
      ADC_SMPR2_SMP0_2),

      (uint32) (
      ADC_SMPR2_SMP0_1 |
      ADC_SMPR2_SMP0_2)

   },

   /**
    *    Configuration of ADC1_CR2 register
    *    - Set ADON register to enable ADC1
    *    - Set the alignment of the conversion to right.
    */
   {
      (volatile uint32*) &ADC1->CR2,

      (uint32) ~(
      ADC_CR2_ADON |
      ADC_CR2_ALIGN),

      (uint32) (ADC_CR2_ADON)
   },

   /**
    *    Configuration of ADC2_SQR1 register
    *    - Set the regular channel sequence length.
    *
    */

   {
      (volatile uint32*) &ADC2->SQR1,

      (uint32) ~(ADC_SQR1_L),

      (uint32) (0x00)
   },
   /**
    *    Configuration of ADC2_CR1 register
    *    - Set ADC2 in discontinuous mode
    *    - Set the resolution of the conversion to 12 bits.
    */
   {
      (volatile uint32*) &ADC2->CR1,

      (uint32) ~(
      ADC_CR1_DISCEN |
      ADC_CR1_RES),

      (uint32) (ADC_CR1_DISCEN)

   },

   /**
    *    Configuration of ADC2_SMPR2 register
    *    - Set the sampling time of the channel 1 to 144 cycles
    *    -
    */
   {
      (volatile uint32*) &ADC2->SMPR2,

      (uint32) ~(
      ADC_SMPR2_SMP6_1 |
      ADC_SMPR2_SMP6_2),

      (uint32) (
      ADC_SMPR2_SMP6_1 |
      ADC_SMPR2_SMP6_2)

   },
   {
      (volatile uint32*) &ADC2->SMPR1,

      (uint32) ~(
      ADC_SMPR1_SMP10_1 |
      ADC_SMPR1_SMP10_2 |
      ADC_SMPR1_SMP12_1 |
      ADC_SMPR1_SMP12_2 |
      ADC_SMPR1_SMP14_1 |
      ADC_SMPR1_SMP14_2
      ),

      (uint32) (
      ADC_SMPR1_SMP10_1 |
      ADC_SMPR1_SMP10_2 |
      ADC_SMPR1_SMP12_1 |
      ADC_SMPR1_SMP12_2 |
      ADC_SMPR1_SMP14_1 |
      ADC_SMPR1_SMP14_2
      )

   },
   /**
    *    Configuration of ADC2_CR2 register
    *    - Set ADON register to enable ADC2
    *    - Set the alignment of the conversion to right.
    */
   {
      (volatile uint32*) &ADC2->CR2,

      (uint32) ~(
      ADC_CR2_ADON |
      ADC_CR2_ALIGN),

      (uint32) (ADC_CR2_ADON)
   },

};

/** \brief ADC register configuration array */
static const RegInit_Masked32BitsConfigType Adc_kt_Config =
{
   Adc_kat_Registers,
   ADC_NUMBER_OF_REGISTERS,

};

/*-------------------------------------------------------------------------------------------------------------------*/
/*                                          Declaration Of Global Constants                                          */
/*-------------------------------------------------------------------------------------------------------------------*/
/** \brief ADC configuration array */
const Adc_ConfigType Adc_gkt_Cfg =
{
   Adc_kat_AdcGroups,
   &Adc_kt_Config

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
