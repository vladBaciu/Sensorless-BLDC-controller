/*-------------------------------------------------------------------------------------------------------------------*/
/**
 *    \file       IoHwAb.h
 *    \author     Nicolae-Bogdan Bacrau
 *    \brief      Declares the implementation-specific (non-standardized by AUTOSAR) I/O hardware abstraction
 *                interfaces for accessing and controlling all the sensor and actuator ECU signals. This implementation
 *                targets only the microcontroller (internal) signals.
 */
/*-------------------------------------------------------------------------------------------------------------------*/

#ifndef IOHWAB_H
#define IOHWAB_H

/*-------------------------------------------------------------------------------------------------------------------*/
/*                                                     Inclusions                                                    */
/*-------------------------------------------------------------------------------------------------------------------*/

#include "IoHwAb_ApiCfg.h"

#if (STD_ON == IOHWAB_API)

#if (STD_ON == IOHWAB_ANALOG_API)
#include "Adc.h"
#endif

#if (STD_ON == IOHWAB_DIGITAL_API)
#include "Dio.h"
#endif

#if (STD_ON == IOHWAB_PWM_API)
#include "Pwm.h"
#endif

#if (STD_ON == IOHWAB_LCD_API)
#include "Lcd.h"
#endif

#if (STD_ON == IOHWAB_UART_API)
#include "Uart.h"
#endif

#if (STD_ON == IOHWAB_MOTOR_API)
#include "MotorControl.h"
#endif

#include "IoHwAb_ChannelsCfg.h"

/*-------------------------------------------------------------------------------------------------------------------*/
/*                                            Definition Of Global Macros                                            */
/*-------------------------------------------------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------------------------------------------------*/
/*                                          Definition Of Global Data Types                                          */
/*-------------------------------------------------------------------------------------------------------------------*/

/*------------------------------------------------ Analog Interfaces ------------------------------------------------*/

#if (STD_ON == IOHWAB_ANALOG_API)

/** \brief  Defines the ECU level type for storing ADC readings. Only the MCAL ADC driver is used in this version. */
typedef Adc_ValueGroupType IoHwAb_AnalogLevelType;

/** \brief  Defines the ECU level type for defining ADC channels. Only the MCAL ADC driver is used in this version. */
typedef Adc_GroupType IoHwAb_AnalogChannelType;

#endif

/*------------------------------------------------ Digital Interfaces -----------------------------------------------*/

#if (STD_ON == IOHWAB_DIGITAL_API)

/** \brief  Defines the ECU level type for storing digital values. Only the MCAL DIO driver is used in this version. */
typedef Dio_LevelType IoHwAb_DigitalLevelType;

/** \brief  Defines the ECU level type for defining DIO channels. Only the MCAL DIO driver is used in this version. */
typedef Dio_ChannelType IoHwAb_DigitalChannelType;

/** \brief  Defines the ECU level type for storing port values. Only the MCAL DIO driver is used in this version. */
typedef Dio_PortLevelType IoHwAb_DigitalPortLevelType;

/** \brief  Defines the ECU level type for defining DIO port channels. Only the MCAL DIO driver is used in this
 *          version. */
typedef Dio_PortType IoHwAb_DigitalPortChannelType;

#endif /* (STD_ON == IOHWAB_DIGITAL_API) */

/*-------------------------------------------------- PWM Interfaces -------------------------------------------------*/

#if (STD_ON == IOHWAB_PWM_API)

/** \brief  Defines the ECU level type for defining PWM duty cycle values. Only the MCAL PWM driver is used in this
 *          version. */
typedef uint16 IoHwAb_PwmDutyType;

/** \brief  Defines the ECU level type for defining PWM channels. Only the MCAL PWM driver is used in this version. */
typedef Pwm_ChannelType IoHwAb_PwmChannelType;

#endif /* (STD_ON == IOHWAB_PWM_API) */

/*-------------------------------------------------- LCD Interfaces -------------------------------------------------*/

#if (STD_ON == IOHWAB_LCD_API)

#endif /* (STD_ON == IOHWAB_LCD_API) */

/*-------------------------------------------------- UART Interfaces -------------------------------------------------*/

#if (STD_ON == IOHWAB_UART_API)

typedef Uart_ChannelType IoHwAb_UartChannelType;

typedef Uart_TxStatusType IoHwAb_UartTxStatusType;

typedef Uart_RxStatusType IoHwAb_UartRxStatusType;

#endif /* (STD_ON == IOHWAB_UART_API) */
/*-------------------------------------------------------------------------------------------------------------------*/
/*                                             Export Of Global Variables                                            */
/*-------------------------------------------------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------------------------------------------------*/
/*                                             Export Of Global Constants                                            */
/*-------------------------------------------------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------------------------------------------------*/
/*                                             Export Of Global Functions                                            */
/*-------------------------------------------------------------------------------------------------------------------*/

/*------------------------------------------------ Analog Interfaces ------------------------------------------------*/

#if (STD_ON == IOHWAB_ANALOG_API)

extern IoHwAb_AnalogLevelType IoHwAb_AnalogGetChannel(IoHwAb_AnalogChannelType ChannelId);

#endif

/*------------------------------------------------ Digital Interfaces -----------------------------------------------*/

#if (STD_ON == IOHWAB_DIGITAL_API)

extern IoHwAb_DigitalLevelType IoHwAb_DigitalGetChannel(IoHwAb_DigitalChannelType ChannelId);
extern void IoHwAb_DigitalSetChannel(IoHwAb_DigitalChannelType Channeld, IoHwAb_DigitalLevelType Level);
extern IoHwAb_DigitalPortLevelType IoHwAb_DigitalGetPort(IoHwAb_DigitalPortChannelType PortId);
extern void IoHwAb_DigitalSetPort(IoHwAb_DigitalPortChannelType PortId, IoHwAb_DigitalPortLevelType Level);

#endif /* #if (STD_ON == IOHWAB_DIGITAL_API) */

/*-------------------------------------------------- PWM Interfaces -------------------------------------------------*/

#if (STD_ON == IOHWAB_PWM_API)

extern void IoHwAb_PwmSetChannel(IoHwAb_PwmChannelType ChannelId, IoHwAb_PwmDutyType Duty);

#endif

#endif /* (STD_ON == IOHWAB_API) */

/*-------------------------------------------------- LCD Interfaces -------------------------------------------------*/
#if (STD_ON == IOHWAB_LCD_API)

extern void IoHwAb_LcdInit(void);
extern void IoHwAb_LcdSendString(uint8 * String);
extern void IoHwAb_LcdSendStringXY(uint8 Row, uint8 Position, uint8 *String);
extern void IoHwAb_LcdPutCustomCharacter(uint8 Row, uint8 Position, uint8 uc_Index);
extern void IoHwAb_LcdClear(void);
extern void IoHwAb_LcdCursor(void);
extern void IoHwAb_LcdDisableCursor(void);
extern void IoHwAb_LcdCustomCharacter(void);

#endif /* #if (STD_ON == IOHWAB_LCD_API) */

/*-------------------------------------------------- UART Interfaces -------------------------------------------------*/
#if (STD_ON == IOHWAB_UART_API)

extern void IoHwAbUartTransmitData(IoHwAb_UartChannelType t_ChannelId, uint8 * puc_TransmitAddr);
extern void IoHwAbUartReceiveData(IoHwAb_UartChannelType t_ChannelId, uint8 * puc_ReceiveAddr);
extern IoHwAb_UartTxStatusType IoHwAb_UartGetTransmitStatus(IoHwAb_UartChannelType t_ChannelId);
extern IoHwAb_UartRxStatusType IoHwAb_UartGetReceiveStatus(IoHwAb_UartChannelType t_ChannelId);
#endif /* #if (STD_ON == IOHWAB_UART_API) */

/*-------------------------------------------------- MOTOR Interfaces -------------------------------------------------*/
#if (STD_ON == IOHWAB_MOTOR_API)

extern void IoHwAb_EnableStartSequence();
extern void IoHwAb_EnableAlignSequence();
extern void IoHwAb_DisableStartSequence();
extern void IoHwAb_DisableAlignSequence();

#endif /* #if (STD_ON == IOHWAB_MOTOR_API) */
/*-------------------------------------------------------------------------------------------------------------------*/
#endif /* IOHWAB_H */
