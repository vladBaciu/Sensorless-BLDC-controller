/*-------------------------------------------------------------------------------------------------------------------*/
/**
 *    \file       IoHwAb_ApiCfg.h
 *    \author     Nicolae-Bogdan Bacrau
 *    \brief      Configured the APIs to be used from the I/O hardware abstraction layer.
 */
/*-------------------------------------------------------------------------------------------------------------------*/

#ifndef IOHWAB_APICFG_H
#define IOHWAB_APICFG_H

/*-------------------------------------------------------------------------------------------------------------------*/
/*                                                     Inclusions                                                    */
/*-------------------------------------------------------------------------------------------------------------------*/

#include "Std_Types.h"

/*-------------------------------------------------------------------------------------------------------------------*/
/*                                            Definition Of Global Macros                                            */
/*-------------------------------------------------------------------------------------------------------------------*/

/** \brief  Activates or deactivates the usage of the I/O hardware abstraction layer. Shall be activated only if MCAL
 *          drivers are available. */
#define IOHWAB_API                           (STD_ON)

#if (STD_ON == IOHWAB_API)

/** \brief  Activates or deactivates the usage of the I/O hardware abstraction layer for analog resources. */
#define IOHWAB_ANALOG_API                    (STD_ON)

/** \brief  Activates or deactivates the usage of the I/O hardware abstraction layer for digital resources. */
#define IOHWAB_DIGITAL_API                   (STD_ON)

/** \brief  Activates or deactivates the usage of the I/O hardware abstraction layer for PWM resources. */
#define IOHWAB_PWM_API                       (STD_ON)

/** \brief  Activates or deactivates the usage of the I/O hardware abstraction layer for LCD resources. */
#define IOHWAB_LCD_API                       (STD_ON)

/** \brief  Activates or deactivates the usage of the I/O hardware abstraction layer for UART resources. */
#define IOHWAB_UART_API                       (STD_ON)

/** \brief  Activates or deactivates the usage of the I/O hardware abstraction layer for MOTOR resources. */
#define IOHWAB_MOTOR_API                       (STD_ON)
/*-------------------------------------------------------------------------------------------------------------------*/
/*                                          Definition Of Global Data Types                                          */
/*-------------------------------------------------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------------------------------------------------*/
/*                                             Export Of Global Constants                                            */
/*-------------------------------------------------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------------------------------------------------*/
/*                                             Export Of Global Variables                                            */
/*-------------------------------------------------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------------------------------------------------*/
/*                                             Export Of Global Functions                                            */
/*-------------------------------------------------------------------------------------------------------------------*/

#endif /* (STD_ON == IOHWAB_API) */

/*-------------------------------------------------------------------------------------------------------------------*/
#endif /* IOHWAB_APICFG_H */
