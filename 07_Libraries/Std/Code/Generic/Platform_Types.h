/*-------------------------------------------------------------------------------------------------------------------*/
/**
 *    \file       Platform_Types.h
 *    \author     Nicolae-Bogdan Bacrau
 *    \brief      Defines the AUTOSAR platform dependent types and symbols.
 */
/*-------------------------------------------------------------------------------------------------------------------*/

#ifndef PLATFORM_TYPES_H
#define PLATFORM_TYPES_H

/*-------------------------------------------------------------------------------------------------------------------*/
/*                                                     Inclusions                                                    */
/*-------------------------------------------------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------------------------------------------------*/
/*                                            Definition Of Global Macros                                            */
/*-------------------------------------------------------------------------------------------------------------------*/

/** \brief  Symbol defining a CPU register width of 8 bits. */
#define CPU_TYPE_8               (8U)

/** \brief  Symbol defining a CPU register width of 16 bits. */
#define CPU_TYPE_16              (16U)

/** \brief  Symbol defining a CPU register width of 32 bits. */
#define CPU_TYPE_32              (32U)

/** \brief  Symbol defining the bit order "most significant bit first" in a byte. */
#define MSB_FIRST                (0U)

/** \brief  Symbol defining the bit order "least significant bit first" in a byte. */
#define LSB_FIRST                (1U)

/** \brief  Symbol defining the byte order "high byte first" in a word. */
#define HIGH_BYTE_FIRST          (0U)

/** \brief  Symbol defining the byte order "low byte first" in a word. */
#define LOW_BYTE_FIRST           (1U)

/** \brief  Symbol defining the width of the used CPU. */
#define CPU_TYPE                 (CPU_TYPE_16)

/** \brief  Symbol defining the bit order of the used CPU. */
#define CPU_BIT_ORDER            (MSB_FIRST)

/** \brief  Symbol defining the byte order of the used CPU. */
#define CPU_BYTE_ORDER           (LOW_BYTE_FIRST)

#ifndef FALSE
/** \brief  Symbol defining the boolean value "false". */
#define FALSE                    (0U)
#endif

#ifndef TRUE
/** \brief  Symbol defining the boolean value "true". */
#define TRUE                     (1U)
#endif

/*-------------------------------------------------------------------------------------------------------------------*/
/*                                          Definition Of Global Data Types                                          */
/*-------------------------------------------------------------------------------------------------------------------*/


/** \brief  Type defining an 8 bit signed integer. The possible values interval is [-128, +127]. */
typedef signed    char           sint8;

/** \brief  Type defining an 8 bit unsigned integer. The possible values interval is [0, +255]. */
typedef unsigned  char           uint8;

/** \brief  Type defining a 16 bit signed integer. The possible values interval is [-32,768, +32,767]. */
typedef signed    short          sint16;

/** \brief  Type defining a 16 bit unsigned integer. The possible values interval is [0, +65,535]. */
typedef unsigned  short          uint16;

/** \brief  Type defining a 32 bit signed integer. The possible values interval is [-2,147,483,648, +2,147,483,647]. */
typedef signed    long           sint32;

/** \brief  Type defining a 32 bit unsigned integer. The possible values interval is [0, +4,294,967,295]. */
typedef unsigned  long           uint32;

/** \brief  Type defining the boolean logic. The possible values are {FALSE, TRUE}. */
typedef unsigned  char           boolean;

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
#endif /* PLATFORM_TYPES_H */
