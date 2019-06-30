/*-------------------------------------------------------------------------------------------------------------------*/
/**
 *    \file       Linker_Symbols.h
 *    \author     Nicolae-Bogdan Bacrau
 *    \brief      Exports all the linker script symbols.
 */
/*-------------------------------------------------------------------------------------------------------------------*/

/*----------- Headerswitch ON (for prevention of nested includes) ------------*/

#ifndef LINKER_SYMBOLS_H
#define LINKER_SYMBOLS_H

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

/*-------------------------------------------------------------------------------------------------------------------*/
/*                                             Export Of Global Variables                                            */
/*-------------------------------------------------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------------------------------------------------*/
/*                                             Export Of Global Constants                                            */
/*-------------------------------------------------------------------------------------------------------------------*/

/** \brief  Linker script symbol defining the flash start address from where to load the initialization data for the
 *          .data section. */
extern const uint32 _Linker_DataLoad_;

/** \brief  Linker script symbol defining the RAM start address where the initialized global variables from the .data
 *          section are placed. */
extern const uint32 _Linker_DataStart_;

/** \brief  Linker script symbol defining the RAM end address where the initialized global variables from the .data
 *          section are placed. */
extern const uint32 _Linker_DataEnd_;

/** \brief  Linker script symbol defining the RAM start address where the uninitialized global variables from the .bss
 *          section are placed. */
extern const uint32 _Linker_BssStart_;

/** \brief  Linker script symbol defining the RAM end address where the uninitialized global variables from the .bss
 *          section are placed. */
extern const uint32 _Linker_BssEnd_;

/** \brief  Linker script symbol defining the CCM RAM address where the stack head (also called stack frame or stack
 *          pointer) is placed. The stack grows descending, so the stack head address is higher than the stack tail */
extern const uint32 _Linker_StackHead_;

/** \brief  Linker script symbol defining the CCM RAM address where the stack tail is placed. The stack grows
 *          descending, so the stack head address is higher than the stack tail */
extern const uint32 _Linker_StackTail_;

/*-------------------------------------------------------------------------------------------------------------------*/
/*                                             Export Of Global Functions                                            */
/*-------------------------------------------------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------------------------------------------------*/
#endif /* LINKER_SYMBOLS_H */
