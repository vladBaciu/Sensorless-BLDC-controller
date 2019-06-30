/*-------------------------------------------------------------------------------------------------------------------*/
/**
 *    \file       Std_Types.h
 *    \author     Nicolae-Bogdan Bacrau
 *    \brief      Defines the AUTOSAR standard types.
 */
/*-------------------------------------------------------------------------------------------------------------------*/

#ifndef STD_TYPES_H
#define STD_TYPES_H

/*-------------------------------------------------------------------------------------------------------------------*/
/*                                                     Inclusions                                                    */
/*-------------------------------------------------------------------------------------------------------------------*/

#include "Platform_Types.h"
#include "Compiler.h"

/*-------------------------------------------------------------------------------------------------------------------*/
/*                                            Definition Of Global Macros                                            */
/*-------------------------------------------------------------------------------------------------------------------*/

#ifndef STATUSTYPEDEFINED
#define STATUSTYPEDEFINED

/** \brief  Defines the standard return value that is returned when a given command is accepted. */
#define E_OK            ((Std_ReturnType) 0x00U)

/** \brief  Defines the standard return value that is returned when a given command is rejected. */
#define E_NOT_OK        ((Std_ReturnType) 0x01U)

/** \brief  Defines the status type used by OSEK. Added for OSEK compliance. */
typedef unsigned char   StatusType;

#endif

/** \brief  Defines an electrical signal state of low voltage (usually 0V). */
#define STD_LOW         (0x00U)

/** \brief  Defines an electrical signal state of high voltage (usually 3.3V or 5V). */
#define STD_HIGH        (0x01U)

/** \brief  Defines if a statically configurable functionality is deactivated. */
#define STD_OFF         (0x00U)

/** \brief  Defines if a statically configurable functionality is activated. */
#define STD_ON          (0x01U)

/*-------------------------------------------------------------------------------------------------------------------*/
/*                                          Definition Of Global Data Types                                          */
/*-------------------------------------------------------------------------------------------------------------------*/

/** \brief  Defines the AUTOSAR standard return type that can be used as standard API return type. It is shared between
 *          the RTE and the BSW modules and consists of standard values, E_OK and E_NOT_OK, and user specific error
 *          values, between 0x02 and 0x3F. */
typedef uint8 Std_ReturnType;

/*-------------------------------------------------------------------------------------------------------------------*/
/*                                             Export Of Global Variables                                            */
/*-------------------------------------------------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------------------------------------------------*/
/*                                             Export Of Global Constants                                            */
/*-------------------------------------------------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------------------------------------------------*/
/*                                             Export Of Global Functions                                            */
/*-------------------------------------------------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------------------------------------------------*/
#endif /* STD_TYPES_H */
