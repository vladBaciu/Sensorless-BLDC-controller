/*-------------------------------------------------------------------------------------------------------------------*/
/**
 *    \file       IoHwAb.c
 *    \author     Nicolae-Bogdan Bacrau
 *    \brief      Implements the (non-standardized by AUTOSAR) I/O hardware abstraction interfaces for accessing and
 *                controlling all the sensor and actuator ECU signals through direct access to the MCAL drivers.
 */
/*-------------------------------------------------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------------------------------------------------*/
/*                                                     Inclusions                                                    */
/*-------------------------------------------------------------------------------------------------------------------*/

#include "IoHwAb.h"

#if (STD_ON == IOHWAB_API)

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

/*------------------------------------------------ Analog Interfaces ------------------------------------------------*/

#if (STD_ON == IOHWAB_ANALOG_API)

/**
 * \brief      Performs a synchronous read of the specified MCAL ADC channel.
 * \param      ChannelId: ID of a specific MCAL ADC channel.
 * \return     Result of the internal MCAL ADC conversion for the specified channel.
 */
IoHwAb_AnalogLevelType IoHwAb_AnalogGetChannel(IoHwAb_AnalogChannelType ChannelId)
{
   IoHwAb_AnalogLevelType t_Return;
   Adc_SetupResultBuffer((Adc_GroupType) ChannelId, (Adc_ValueGroupType *) &t_Return);
   Adc_StartGroupConversion((Adc_GroupType) ChannelId);
   while (ADC_BUSY == Adc_GetGroupStatus((Adc_GroupType) ChannelId))
   {
      /* Wait for the conversion to finish. */
   }
   return t_Return;
}

#endif /* (STD_ON == IOHWAB_ANALOG_API) */

/*------------------------------------------------ Digital Interfaces -----------------------------------------------*/

#if (STD_ON == IOHWAB_DIGITAL_API)

/**
 * \brief      Performs a synchronous read of the specified MCAL DIO channel.
 * \param      ChannelId: ID of a specific MCAL DIO channel.
 * \return     Result of the specified MCAL DIO channel reading.
 */
IoHwAb_DigitalLevelType IoHwAb_DigitalGetChannel(IoHwAb_DigitalChannelType ChannelId)
{
   return (IoHwAb_DigitalLevelType) Dio_ReadChannel((Dio_ChannelType) ChannelId);
}

/**
 * \brief      Performs a synchronous write on the specified MCAL DIO channel.
 * \param      ChannelId: ID of a specific MCAL DIO channel.
 * \param      Level: Digital level to be applied on the specified MCAL DIO channel.
 * \return     -
 */
void IoHwAb_DigitalSetChannel(IoHwAb_DigitalChannelType Channeld, IoHwAb_DigitalLevelType Level)
{
   Dio_WriteChannel((Dio_ChannelType) Channeld, (Dio_LevelType) Level);
}

/**
 * \brief      Performs a synchronous read of the specified MCAL DIO port.
 * \param      ChannelId: ID of a specific MCAL DIO port.
 * \return     Result of the specified MCAL DIO port reading.
 */
IoHwAb_DigitalPortLevelType IoHwAb_DigitalGetPort(IoHwAb_DigitalPortChannelType PortId)
{
   return (IoHwAb_DigitalPortLevelType) Dio_ReadPort((Dio_PortType) PortId);
}

/**
 * \brief      Performs a synchronous write on the specified MCAL DIO port.
 * \param      ChannelId: ID of a specific MCAL DIO port.
 * \param      Level: Full port value to be applied on the specified MCAL DIO port.
 * \return     -
 */
void IoHwAb_DigitalSetPort(IoHwAb_DigitalPortChannelType PortId, IoHwAb_DigitalPortLevelType Level)
{
   Dio_WritePort((Dio_PortType) PortId, (Dio_PortLevelType) Level);
}

#endif /* #if (STD_ON == IOHWAB_DIGITAL_API) */

/*-------------------------------------------------- PWM Interfaces -------------------------------------------------*/

#if (STD_ON == IOHWAB_PWM_API)

/**
 * \brief      Performs a synchronous duty cycle update of the specified MCAL PWM channel.
 * \param      ChannelId: ID of a specific MCAL PWM channel.
 * \param      Duty: Duty cycle to be applied on the specified MCAL PWM channel.
 * \return     -
 */
void IoHwAb_PwmSetChannel(IoHwAb_PwmChannelType ChannelId, IoHwAb_PwmDutyType Duty)
{
   Pwm_SetDutyCycle((Pwm_ChannelType) ChannelId, (uint16) Duty);

}

#endif /* (STD_ON == IOHWAB_PWM_API) */

/*-------------------------------------------------- LCD Interfaces -------------------------------------------------*/
#if (STD_ON == IOHWAB_LCD_API)

/*
 * \brief  Inits the display interface with a default message.
 * \param  -
 * \return -
 */
void IoHwAb_LcdInit(void)
{
   Lcd_gv_Init();
}

/*
 * \brief Sends text to display interface.
 * \param String: value to be displayed
 * \return -
 *
 */
void IoHwAb_LcdSendString(uint8 * String)
{
   Lcd_gv_SendString(String);
}

/*
 * \brief Sends text to display interface at a specified position.
 * \param Row: lcd row number.
 * \param Position: lcd column number.
 * \param String: value to be displayed
 * \return -
 *
 */
void IoHwAb_LcdSendStringXY(uint8 Row, uint8 Position, uint8 *String)
{
   Lcd_gv_SendStringXY(Row, Position, String);
}

/*
 * \brief  Clears the display interface.
 * \param  -
 * \return -
 *
 */
void IoHwAb_LcdClear(void)
{
   Lcd_gv_Clear();
}

/*
 * \brief  Display cursor on LCD. Sends the enable command for cursor.
 * \param  -
 * \return -
 *
 */
void IoHwAb_LcdCursor(void)
{
   Lcd_gv_Cursor();
}

/*
 * \brief  Sends the disable command for cursor .
 * \param  -
 * \return -
 *
 */
void IoHwAb_LcdDisableCursor(void)
{
   Lcd_gv_DisableCursor();
}

/*
 * \brief  Stores in LCD's RAM controller all the custom characters from puc_LcdCustomCharacters.
 * \param  -
 * \return -
 *
 */
void IoHwAb_LcdCustomCharacter(void)
{
   Lcd_gv_CreateCustomCharacter();
}

/*
 * \brief  Displays a custom character from RAM memory at a specific row and column.
 * \param  -
 * \return -
 *
 */
void IoHwAb_LcdPutCustomCharacter(uint8 uc_Row, uint8 uc_Position, uint8 uc_Index)
{
   Lcd_gv_PutCustomCharacter(uc_Row, uc_Position, uc_Index);
}
#endif /* (STD_ON == IOHWAB_LCD_API) */

/*-------------------------------------------------- UART Interfaces -------------------------------------------------*/
#if (STD_ON == IOHWAB_UART_API)

/*
 * \brief
 * \param  -
 * \return -
 *
 */
void IoHwAbUartTransmitData(IoHwAb_UartChannelType t_ChannelId, uint8 * puc_TransmitAddr)
{
   Uart_gv_Transmit(t_ChannelId, puc_TransmitAddr);
}

/*
 * \brief
 * \param  -
 * \return -
 *
 */
void IoHwAbUartReceiveData(IoHwAb_UartChannelType t_ChannelId, uint8 * puc_ReceiveAddr)
{
   Uart_gv_Receive(t_ChannelId, puc_ReceiveAddr);
}

/*
 * \brief
 * \param  -
 * \return -
 *
 */
IoHwAb_UartTxStatusType IoHwAb_UartGetTransmitStatus(IoHwAb_UartChannelType t_ChannelId)
{

   IoHwAb_UartTxStatusType t_Return;
   t_Return = Uart_gt_GetTransmitStatus(t_ChannelId);

   return t_Return;
}

/*
 * \brief
 * \param  -
 * \return -
 *
 */
IoHwAb_UartRxStatusType IoHwAb_UartGetReceiveStatus(IoHwAb_UartChannelType t_ChannelId)
{
   IoHwAb_UartRxStatusType t_Return;
   t_Return = Uart_gt_GetReceiveStatus(t_ChannelId);

   return t_Return;
}
#endif

#endif /* (STD_ON == IOHWAB_UART_API) */

/*-------------------------------------------------- UART Interfaces -------------------------------------------------*/
#if (STD_ON == IOHWAB_MOTOR_API)

void IoHwAb_EnableStartSequence()
{
   MotorControl_gv_EnableStartSequence();
}
void IoHwAb_EnableAlignSequence()
{
   MotorControl_gv_EnableAlignSequence();
}
void IoHwAb_DisableStartSequence()
{
   MotorControl_gv_DisableStartSequence();
}
void IoHwAb_DisableAlignSequence()
{
   MotorControl_gv_DisableAlignSequence();
}

#endif /* (STD_ON == IOHWAB_UART_API) */
