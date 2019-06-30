/*-------------------------------------------------------------------------------------------------------------------*/
/**
 *    \file       RegInit.h
 *    \author     Nicolae-Bogdan Bacrau
 *    \brief      Exports the global functions and data types of the generic API for writing sets of 8, 16 or 32 bit
 *                registers.
 */
/*-------------------------------------------------------------------------------------------------------------------*/

#ifndef REGINIT_H
#define REGINIT_H

/*-------------------------------------------------------------------------------------------------------------------*/
/*                                                     Inclusions                                                    */
/*-------------------------------------------------------------------------------------------------------------------*/

#include "Std_Types.h"

/*-------------------------------------------------------------------------------------------------------------------*/
/*                                            Definition Of Global Macros                                            */
/*-------------------------------------------------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------------------------------------------------*/
/*                                          Definition Of Global Data Types                                          */
/*-------------------------------------------------------------------------------------------------------------------*/

/** \brief  Defines a configuration for a single 8-bits register. */
typedef struct
{
   /** \brief  Address of the 8-bits register. */
   volatile uint8* kpuc_Register;

   /** \brief  Value to be loaded into the destination 8-bits register. */
   uint8 uc_RegisterValue;

} RegInit_Full8BitsSingleType;

/** \brief  Defines a configuration for multiple single 8-bits register configurations. */
typedef struct
{
   /** \brief  Pointer to an array of single 8-bits register configurations. */
   const RegInit_Full8BitsSingleType* pt_Registers;

   /** \brief  The number of elements of the array of single 8-bits register configurations. */
   uint16 us_NumberOfRegisters;

} RegInit_Full8BitsConfigType;

/*-------------------------------------------------------------------------------------------------------------------*/

/** \brief  Defines a configuration for a single 16-bits register. */
typedef struct
{
   /** \brief  Address of the 16-bits register. */
   volatile uint16* kpus_Register;

   /** \brief  Value to be loaded into the destination 16-bits register. */
   uint16 us_RegisterValue;

} RegInit_Full16BitsSingleType;

/** \brief  Defines a configuration for multiple 16-bits register configurations. */
typedef struct
{
   /** \brief  Pointer to an array of single 16-bits register configurations. */
   const RegInit_Full16BitsSingleType* pt_Registers;

   /** \brief  The number of elements of the array of single 16-bits register configurations. */
   uint16 us_NumberOfRegisters;

} RegInit_Full16BitsConfigType;

/*-------------------------------------------------------------------------------------------------------------------*/

/** \brief  Defines a configuration for a single 32-bits register. */
typedef struct
{
   /** \brief  Address of the 32-bits register. */
   volatile uint32* kpul_Register;

   /** \brief  Value to be loaded into the destination 32-bits register. */
   uint32 ul_RegisterValue;

} RegInit_Full32BitsSingleType;

/** \brief  Defines a configuration for multiple 16-bits register configurations. */
typedef struct
{
   /** \brief  Pointer to an array of single 32-bits register configurations. */
   const RegInit_Full32BitsSingleType* pt_Registers;

   /** \brief  The number of elements of the array of single 32-bits register configurations. */
   uint16 us_NumberOfRegisters;

} RegInit_Full32BitsConfigType;

/*-------------------------------------------------------------------------------------------------------------------*/
/*-------------------------------------------------------------------------------------------------------------------*/
/*-------------------------------------------------------------------------------------------------------------------*/

/** \brief  Defines a configuration for a single 8-bits register with masks. */
typedef struct
{
   /** \brief  Address of the 8-bits register. */
   volatile uint8* kpuc_Register;

   /** \brief  AND mask to be applied on the destination 8-bits register. */
   uint8 uc_MaskAnd;

   /** \brief  OR mask to be applied on the destination 8-bits register. */
   uint8 uc_MaskOr;

} RegInit_Masked8BitsSingleType;

/** \brief  Defines a configuration for multiple 8-bits register with mask configurations. */
typedef struct
{
   /** \brief  Pointer to an array of single 8-bits register configurations. */
   const RegInit_Masked8BitsSingleType* pt_Registers;

   /** \brief  The number of elements of the array of single 8-bits register configurations. */
   uint16 us_NumberOfRegisters;

} RegInit_Masked8BitsConfigType;

/*-------------------------------------------------------------------------------------------------------------------*/

/** \brief  Defines a configuration for a single 16-bits register with masks. */
typedef struct
{
   /** \brief  Address of the 16-bits register. */
   volatile uint16* kpus_Register;

   /** \brief  AND mask to be applied on the destination 16-bits register. */
   uint16 us_MaskAnd;

   /** \brief  OR mask to be applied on the destination 16-bits register. */
   uint16 us_MaskOr;

} RegInit_Masked16BitsSingleType;

/** \brief  Defines a configuration for multiple 16-bits register with mask configurations. */
typedef struct
{
   /** \brief  Pointer to an array of single 16-bits register configurations. */
   const RegInit_Masked16BitsSingleType* pt_Registers;

   /** \brief  The number of elements of the array of single 16-bits register configurations. */
   uint16 us_NumberOfRegisters;

} RegInit_Masked16BitsConfigType;

/*-------------------------------------------------------------------------------------------------------------------*/

/** \brief  Defines a configuration for a single 32-bits register with masks. */
typedef struct
{
   /** \brief  Address of the 32-bits register. */
   volatile uint32* kpul_Register;

   /** \brief  AND mask to be applied on the destination 32-bits register. */
   uint32 ul_MaskAnd;

   /** \brief  OR mask to be applied on the destination 32-bits register. */
   uint32 ul_MaskOr;

} RegInit_Masked32BitsSingleType;

/** \brief  Defines a configuration for multiple 32-bits register with mask configurations. */
typedef struct
{
   /** \brief  Pointer to an array of single 32-bits register configurations. */
   const RegInit_Masked32BitsSingleType* pt_Registers;

   /** \brief  The number of elements of the array of single 32-bits register configurations. */
   uint16 us_NumberOfRegisters;

} RegInit_Masked32BitsConfigType;

/*-------------------------------------------------------------------------------------------------------------------*/
/*                                             Export Of Global Variables                                            */
/*-------------------------------------------------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------------------------------------------------*/
/*                                             Export Of Global Constants                                            */
/*-------------------------------------------------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------------------------------------------------*/
/*                                             Export Of Global Functions                                            */
/*-------------------------------------------------------------------------------------------------------------------*/

extern void RegInit_gv_Full8Bits(const RegInit_Full8BitsConfigType* pt_Full8BitsConfig);
extern void RegInit_gv_Full16Bits(const RegInit_Full16BitsConfigType* pt_Full16BitsConfig);
extern void RegInit_gv_Full32Bits(const RegInit_Full32BitsConfigType* pt_Full32BitsConfig);
extern void RegInit_gv_Masked8Bits(const RegInit_Masked8BitsConfigType* pt_Masked8BitsConfig);
extern void RegInit_gv_Masked16Bits(const RegInit_Masked16BitsConfigType* pt_Masked16BitsConfig);
extern void RegInit_gv_Masked32Bits(const RegInit_Masked32BitsConfigType* pt_Masked32BitsConfig);

/*-------------------------------------------------------------------------------------------------------------------*/
#endif /* REGINIT_H */
