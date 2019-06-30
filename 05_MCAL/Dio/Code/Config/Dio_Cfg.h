/*-------------------------------------------------------------------------------------------------------------------*/
/**
 *    \file       Dio_Cfg.h
 *    \author     Baciu Vlad-Eusebiu
 *    \brief      Defines and exports the channels and ports IDs.
 */
/*-------------------------------------------------------------------------------------------------------------------*/

#ifndef DIO_CFG_H
#define DIO_CFG_H

/*-------------------------------------------------------------------------------------------------------------------*/
/*                                                     Inclusions                                                    */
/*-------------------------------------------------------------------------------------------------------------------*/
#include "Dio.h"
/*-------------------------------------------------------------------------------------------------------------------*/
/*                                            Definition Of Global Macros                                            */
/*-------------------------------------------------------------------------------------------------------------------*/
/** \brief  Numbers of channels from channel configuration array */
#define DIO_NUMBER_OF_CHANNELS (14U)
/** \brief  Numbers of ports from port configuration array */
#define DIO_NUMBER_OF_PORTS    (5U)

/** \brief  GPIOA index in port configuration */
#define DIO_PORTA (0U)

/** \brief  GPIOB index in port configuration */
#define DIO_PORTB (1U)

/** \brief  GPIOC index in port configuration */
#define DIO_PORTC (2U)

/** \brief  GPIOE index in port configuration */
#define DIO_PORTE (3U)

/** \brief  GPIOD index in port configuration */
#define DIO_PORTD (4U)

/** \brief  GPIOA PIN 0 index in channel configuration */
#define DIO_A_0        (0)

/** \brief  GPIOE PIN 7 index in channel configuration */
#define DIO_E_7        (1)

/** \brief  GPIOE PIN 9 index in channel configuration */
#define DIO_E_9        (2)

/** \brief  GPIOE PIN 11 index in channel configuration */
#define DIO_E_11       (3)

/** \brief  GPIOE PIN 13 index in channel configuration */
#define DIO_E_13       (4)

/** \brief  GPIOE PIN 15 index in channel configuration */
#define DIO_E_15       (5)

/** \brief  GPIOB PIN 11 index in channel configuration */
#define DIO_B_11       (6)

/** \brief  GPIOD PIN 0 index in channel configuration */
#define DIO_D_0        (7)

/** \brief  GPIOD PIN 2 index in channel configuration */
#define DIO_D_2        (8)

/** \brief  GPIOD PIN 2 index in channel configuration */
#define DIO_D_4        (9)

/** \brief  GPIOD PIN 11 index in channel configuration */
#define DIO_D_11        (10)

/** \brief  GPIOD PIN 13 index in channel configuration */
#define DIO_D_13        (11)

/** \brief  GPIOD PIN 15 index in channel configuration */
#define DIO_D_15        (12)

/** \brief  GPIOA PIN 0 index in channel configuration */
#define DIO_B_0        (13)

/*-------------------------------------------------------------------------------------------------------------------*/
/*                                          Definition Of Global Data Types                                          */
/*-------------------------------------------------------------------------------------------------------------------*/

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
#endif /* DIO_CFG_H */
