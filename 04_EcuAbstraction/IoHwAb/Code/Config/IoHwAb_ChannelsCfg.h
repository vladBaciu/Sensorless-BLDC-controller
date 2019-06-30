/*-------------------------------------------------------------------------------------------------------------------*/
/**
 *    \file       IoHwAb_ChannelsCfg.h
 *    \author     Nicolae-Bogdan Bacrau
 *    \brief      Defines the sensor and actuator channels on the ECU abstraction level for accessing all the ECU
 *                signals.
 *
 *    From the MCAL drivers' perspective the channels do not contain the information about the context they're used in.
 *    In this layer the MCAL channels are mapped to ECU signal names that describe the signals origin or destination
 *    that are correlated with a sensor or an actuator.
 */
/*-------------------------------------------------------------------------------------------------------------------*/

#ifndef IOHWAB_CHANNELSCFG_H
#define IOHWAB_CHANNELSCFG_H

/*-------------------------------------------------------------------------------------------------------------------*/
/*                                                     Inclusions                                                    */
/*-------------------------------------------------------------------------------------------------------------------*/

#include "IoHwAb_ApiCfg.h"

#if (STD_ON == IOHWAB_API)

/*-------------------------------------------------------------------------------------------------------------------*/
/*                                            Definition Of Global Macros                                            */
/*-------------------------------------------------------------------------------------------------------------------*/

/* Redefine all the MCAL driver channels by providing the information about the used peripherals. */

/* -------------------------- Analog ---------------------------*/

#if (STD_ON == IOHWAB_ANALOG_API)

#define IOHWAB_ANALOG_POTENTIOMETER_X_AXIS                (ADC_C_0)
#define IOHWAB_ANALOG_POTENTIOMETER_Y_AXIS                (ADC_C_2)
#define IOHWAB_ANALOG_BATTERY_SENSOR                      (ADC_C_4)
#define IOHWAB_ANALOG_CURRENT_SENSOR                      (ADC_A_6)

#endif /* (STD_ON == IOHWAB_ANALOG_API) */

/* -------------------------- Digital --------------------------*/

#if (STD_ON == IOHWAB_DIGITAL_API)

#define IOHWAB_DIGITAL_BTN_JOYSTICK                (DIO_A_0)
#define IOHWAB_DIGITAL_LED_LEFT                    (DIO_D_11)
#define IOHWAB_DIGITAL_LED_CENTER                  (DIO_D_13)
#define IOHWAB_DIGITAL_LED_RIGHT                   (DIO_D_15)
#define IOHWAB_DIGITAL_READ_BATTERY_COMMAND        (DIO_B_0)
#endif /* (STD_ON == IOHWAB_DIGITAL_API) */

/* ---------------------------- PWM ----------------------------*/

#if (STD_ON == IOHWAB_PWM_API)




#endif /* (STD_ON == IOHWAB_PWM_API) */

/* ---------------------------- LCD ----------------------------*/
#if (STD_ON == IOHWAB_LCD_API)

/* ---------------------------- UART ----------------------------*/

#endif /* (STD_ON == IOHWAB_LCD_API) */


#if (STD_ON == IOHWAB_UART_API)

#define IOHWAB_UART_RX_PIN                     (UART_RX_C_11)
#define IOHWAB_UART_TX_PIN                     (UART_TX_C_10)

#endif /* (STD_ON == IOHWAB_UART_API) */
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
#endif /* IOHWAB_CHANNELSCFG_H */
