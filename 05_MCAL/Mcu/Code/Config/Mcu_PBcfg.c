/*-------------------------------------------------------------------------------------------------------------------*/
/**
 *    \file       Mcu_PBcfg.c
 *    \author     Nicolae-Bogdan Bacrau
 *    \brief      Sets up the AUTOSAR MCU driver configuration using the RegInit data types for masked 32 bits
 *                registers. Sets up clock frequencies, clock distributions, enables flash acceleration features and
 *                sets voltage regulator settings.
 */
/*-------------------------------------------------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------------------------------------------------*/
/*                                                     Inclusions                                                    */
/*-------------------------------------------------------------------------------------------------------------------*/

#include "Mcu.h"
#include "stm32f407xx.h"

/*-------------------------------------------------------------------------------------------------------------------*/
/*                                             Definition Of Local Macros                                            */
/*-------------------------------------------------------------------------------------------------------------------*/

/** \brief  Defines the total number of registers to be loaded in the initialization function. */
#define MCU_NUMBER_OF_INIT_REGISTERS      (10U)

/** \brief  Defines the division factor for the main PLL register value to be written to 8.
 *             8 = b001000. */
#define MCU_RCC_PLLCFGR_PLLM              (RCC_PLLCFGR_PLLM_3)

/** \brief  Defines the main PLL multiplication factor for VCO register value to be written to 320.
 *             320 = b101000000. */
#define MCU_RCC_PLLCFGR_PLLN              (RCC_PLLCFGR_PLLN_8 | RCC_PLLCFGR_PLLN_6)

/** \brief  Defines the main PLL division factor for main system clock register value to be written to 0, which means
 *          PLLP is set to 2. */
#define MCU_RCC_PLLCFGR_PLLP              (0UL)

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

/** \brief  Stores the configuration of all the registers to be set in the MCU initialization function. */
static const RegInit_Masked32BitsSingleType Mcu_kat_Registers[MCU_NUMBER_OF_INIT_REGISTERS] =
{
   /* Setup flash acceleration features:
    *    -Enable the flash instruction cache (set ICEN).
    *    -Enable the flash data cache (set DCEN).
    *    -Enable the flash prefetch buffer (set PRFTEN).
    *    -Set the flash access latency to 5. (LATENCY = 5). */
   {
      (volatile uint32*) (&FLASH->ACR),

      (uint32) ~(
      FLASH_ACR_ICEN |
      FLASH_ACR_DCEN |
      FLASH_ACR_PRFTEN |
      FLASH_ACR_LATENCY),

      (uint32) (
      FLASH_ACR_ICEN |
      FLASH_ACR_DCEN |
      FLASH_ACR_PRFTEN |
      FLASH_ACR_LATENCY_5WS)
   },

   /* Enable the power interface clock.
    * Set clock for
    *       TIM2
    *       TIM3
    *       TIM4
    *       TIM5
    *       UART4
    */
   {
      (volatile uint32*) (&RCC->APB1ENR),

      (uint32) ~(
      RCC_APB1ENR_PWREN |
      RCC_APB1ENR_TIM2EN |
      RCC_APB1ENR_TIM3EN |
      RCC_APB1ENR_TIM4EN |
      RCC_APB1ENR_TIM5EN |
      RCC_APB1ENR_UART4EN),
      (uint32) (
      RCC_APB1ENR_PWREN |
      RCC_APB1ENR_TIM2EN |
      RCC_APB1ENR_TIM3EN |
      RCC_APB1ENR_TIM4EN |
      RCC_APB1ENR_TIM5EN |
      RCC_APB1ENR_UART4EN)
   },
   /* Set the regulator voltage scaling to scale 1. */
   {
      (volatile uint32*) (&PWR->CR),

      (uint32) ~(PWR_CR_VOS),

      (uint32) (PWR_CR_VOS)
   },

   /* Enable the high speed external (HSE) 8 MHz oscillator. */
   {
      (volatile uint32*) (&RCC->CR),

      (uint32) ~(RCC_CR_HSEON),

      (uint32) (RCC_CR_HSEON),
   },

   /* Setup the PLL:
    *    -HSE as PLL clock source (PLLSRC = 1).
    *    -Set division factor for the main PLL register to 8 (PLLM = 8).
    *    -Set main PLL multiplication factor for VCO register to 320 (PLLN = 320).
    *    -Set main PLL division factor for main system clock register to 0 (PLLP = 2).
    *
    * According to the STM32F407xx reference manual the PLL output clock frequency is calculated as follows:
    *    -f(VCO clock) = f(PLL clock input) * (PLLN / PLLM);
    *    -f(PLL general clock output) = f(VCO clock) / PLLP;
    *
    * For this configuration:
    *    -f(PLL clock input) = f(HSE) = 8 MHz;
    *    -f(VCO clock) = 8 MHz * (320 / 8) = 320 MHz;
    *    -f(PLL general clock output) = 320 MHz / 2 = 160 MHz. */
   {
      (volatile uint32*) (&RCC->PLLCFGR),

      (uint32) ~(
      RCC_PLLCFGR_PLLSRC |
      RCC_PLLCFGR_PLLM |
      RCC_PLLCFGR_PLLN |
      RCC_PLLCFGR_PLLP),

      (uint32) (
      RCC_PLLCFGR_PLLSRC_HSE |
      MCU_RCC_PLLCFGR_PLLM |
      MCU_RCC_PLLCFGR_PLLN |
      MCU_RCC_PLLCFGR_PLLP)
   },

   /* Enable the main PLL. */
   {
      (volatile uint32*) (&RCC->CR),

      (uint32) ~(RCC_CR_PLLON),

      (uint32) (RCC_CR_PLLON)
   },

   /* Setup the bus clocks:
    *    -Select system clock (SYSCLK) as PLL output (SW = b10).
    *    -Set AHB clock (HCLK) to 160 MHz (SYSCLK prescaler set to 1; HPRE = b0000).
    *    -Set APB2 clock (PCLK2) to 80 MHz (HCLK prescaler set to 2; PPRE2 = b100).
    *    -Set APB1 clock (PCLK1) to 40 MHz (HCLK prescaler set to 4; PPRE1 = b101). Take note that the APB timer clocks
    *    are in this case 40 MHz * 2 = 80 MHz (since PPRE1 != 1). */
   {
      (volatile uint32*) (&RCC->CFGR),

      (uint32) ~(
      RCC_CFGR_SW |
      RCC_CFGR_HPRE |
      RCC_CFGR_PPRE2 |
      RCC_CFGR_PPRE1),

      (uint32) (
      RCC_CFGR_SW_PLL |
      RCC_CFGR_HPRE_DIV1 |
      RCC_CFGR_PPRE2_DIV2 |
      RCC_CFGR_PPRE1_DIV4)
   },

   /* Stop the HSI oscillator since the HSE oscillator is used (HSION = 0). */
   {
      (volatile uint32*) (&RCC->CR),

      (uint32) ~(RCC_CR_HSION),

      (uint32) 0UL
   },

   /* Provide clock to GPIO port A, B, C, E, D*/
   {
      (volatile uint32*) (&RCC->AHB1ENR),

      (uint32) ~(
      RCC_AHB1ENR_GPIOAEN |
      RCC_AHB1ENR_GPIOBEN |
      RCC_AHB1ENR_GPIOCEN |
      RCC_AHB1ENR_GPIOEEN |
      RCC_AHB1ENR_GPIODEN),

      (uint32) (
      RCC_AHB1ENR_GPIOAEN |
      RCC_AHB1ENR_GPIOBEN |
      RCC_AHB1ENR_GPIOCEN |
      RCC_AHB1ENR_GPIOEEN |
      RCC_AHB1ENR_GPIODEN),
   },

   /* Provide clock to ADC1 and ADC2 module
    * */
   {
      (volatile uint32*) (&RCC->APB2ENR),
      (uint32) ~(
      RCC_APB2ENR_ADC1EN |
      RCC_APB2ENR_ADC2EN),

      (uint32) (
      RCC_APB2ENR_ADC1EN |
      RCC_APB2ENR_ADC2EN )
   }
};

/*-------------------------------------------------------------------------------------------------------------------*/
/*                                          Declaration Of Global Constants                                          */
/*-------------------------------------------------------------------------------------------------------------------*/

/** \brief  References the configuration of all the registers to be set in the MCU initialization function and the
 *          number of registers to be initialized. */
const Mcu_ConfigType Mcu_gkt_Config =
{
   Mcu_kat_Registers,
   MCU_NUMBER_OF_INIT_REGISTERS
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
