/*-------------------------------------------------------------------------------------------------------------------*/
/**
 *    \file       RegInit.c
 *    \author     Nicolae-Bogdan Bacrau
 *    \brief      Implements a generic API for writing sets of 8, 16 or 32 bit registers.
 *
 *                The API offers two possibilities for loading the registers:
 *                -Direct: the registers are (fully) written with predefined values;
 *                -Masked: only subsets of each referenced register can be written by making use of (AND, OR) masks.
 */
/*-------------------------------------------------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------------------------------------------------*/
/*                                                     Inclusions                                                    */
/*-------------------------------------------------------------------------------------------------------------------*/

#include "RegInit.h"

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
 * \brief      Initializes the referenced set of MCU 8 bit registers by loading predefined values.
 * \param      pt_Full8BitsConfig : Configuration structure to be loaded for 8 bit registers.
 * \return     -
 */
void RegInit_gv_Full8Bits(const RegInit_Full8BitsConfigType* pt_Full8BitsConfig)
{
   uint16 us_I;
   for (us_I = 0U; us_I < pt_Full8BitsConfig->us_NumberOfRegisters; us_I++)
   {
      (*pt_Full8BitsConfig->pt_Registers[us_I].kpuc_Register) = pt_Full8BitsConfig->pt_Registers[us_I].uc_RegisterValue;
   }
}

/**
 * \brief      Initializes the referenced set of MCU 16 bit registers by loading predefined values.
 * \param      pt_Full16BitsConfig : Configuration structure to be loaded for 16 bit registers.
 * \return     -
 */
void RegInit_gv_Full16Bits(const RegInit_Full16BitsConfigType* pt_Full16BitsConfig)
{
   uint16 us_I;
   for (us_I = 0U; us_I < pt_Full16BitsConfig->us_NumberOfRegisters; us_I++)
   {
      (*pt_Full16BitsConfig->pt_Registers[us_I].kpus_Register) = pt_Full16BitsConfig->pt_Registers[us_I]
         .us_RegisterValue;
   }
}

/**
 * \brief      Initializes the referenced set of MCU 32 bit registers by loading predefined values.
 * \param      pt_Full32BitsConfig : Configuration structure to be loaded for 32 bit registers.
 * \return     -
 */
void RegInit_gv_Full32Bits(const RegInit_Full32BitsConfigType* pt_Full32BitsConfig)
{
   uint16 us_I;
   for (us_I = 0U; us_I < pt_Full32BitsConfig->us_NumberOfRegisters; us_I++)
   {
      (*pt_Full32BitsConfig->pt_Registers[us_I].kpul_Register) = pt_Full32BitsConfig->pt_Registers[us_I]
         .ul_RegisterValue;
   }
}

/**
 * \brief      Initializes the referenced set of MCU 8 bit registers by applying AND and OR masks.
 * \param      pt_Masked8BitsConfig : Configuration structure to be loaded for 8 bit registers.
 * \return     -
 */
void RegInit_gv_Masked8Bits(const RegInit_Masked8BitsConfigType* pt_Masked8BitsConfig)
{
   uint16 us_I;
   volatile uint8 uc_RegVal;
   for (us_I = 0U; us_I < pt_Masked8BitsConfig->us_NumberOfRegisters; us_I++)
   {
      /* Apply the masks on a local variable to avoid writing the register twice; mandatory for registers which can
       * only be written once after reset. */
      uc_RegVal = *pt_Masked8BitsConfig->pt_Registers[us_I].kpuc_Register;

      /* Applying the AND mask. */
      uc_RegVal &= pt_Masked8BitsConfig->pt_Registers[us_I].uc_MaskAnd;

      /* Applying the OR mask. */
      uc_RegVal |= pt_Masked8BitsConfig->pt_Registers[us_I].uc_MaskOr;

      /* Write back the local variable to the register. */
      *pt_Masked8BitsConfig->pt_Registers[us_I].kpuc_Register = uc_RegVal;
   }
}

/**
 * \brief      Initializes the referenced set of MCU 16 bit registers by applying AND and OR masks.
 * \param      pt_Masked16BitsConfig : Configuration structure to be loaded for 16 bit registers.
 * \return     -
 */
void RegInit_gv_Masked16Bits(const RegInit_Masked16BitsConfigType* pt_Masked16BitsConfig)
{
   uint16 us_I;
   volatile uint16 us_RegVal;
   for (us_I = 0U; us_I < pt_Masked16BitsConfig->us_NumberOfRegisters; us_I++)
   {
      /* Apply the masks on a local variable to avoid writing the register twice; mandatory for registers which can
       * only be written once after reset. */
      us_RegVal = *pt_Masked16BitsConfig->pt_Registers[us_I].kpus_Register;

      /* Applying the AND mask. */
      us_RegVal &= pt_Masked16BitsConfig->pt_Registers[us_I].us_MaskAnd;

      /* Applying the OR mask. */
      us_RegVal |= pt_Masked16BitsConfig->pt_Registers[us_I].us_MaskOr;

      /* Write back the local variable to the register. */
      *pt_Masked16BitsConfig->pt_Registers[us_I].kpus_Register = us_RegVal;
   }
}

/**
 * \brief      Initializes the referenced set of MCU 32 bit registers by applying AND and OR masks.
 * \param      pt_Masked32BitsConfig : Configuration structure to be loaded for 32 bit registers.
 * \return     -
 */
void RegInit_gv_Masked32Bits(const RegInit_Masked32BitsConfigType* pt_Masked32BitsConfig)
{
   uint16 us_I;
   volatile uint32 ul_RegVal;
   for (us_I = 0U; us_I < pt_Masked32BitsConfig->us_NumberOfRegisters; us_I++)
   {
      /* Apply the masks on a local variable to avoid writing the register twice; mandatory for registers which can
       * only be written once after reset. */
      ul_RegVal = *pt_Masked32BitsConfig->pt_Registers[us_I].kpul_Register;

      /* Applying the AND mask. */
      ul_RegVal &= pt_Masked32BitsConfig->pt_Registers[us_I].ul_MaskAnd;

      /* Applying the OR mask. */
      ul_RegVal |= pt_Masked32BitsConfig->pt_Registers[us_I].ul_MaskOr;

      /* Write back the local variable to the register. */
      *pt_Masked32BitsConfig->pt_Registers[us_I].kpul_Register = ul_RegVal;
   }
}
