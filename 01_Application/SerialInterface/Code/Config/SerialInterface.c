/*-------------------------------------------------------------------------------------------------------------------*/
/**
 *    \file       SerialInterface.c
 *    \author     Baciu Vlad-Eusebiu
 *    \brief      Empty template to be used for all .c files. This file provides an example for the case in which a
 *                detailed description is not needed.
 */
/*-------------------------------------------------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------------------------------------------------*/
/*                                                     Inclusions                                                    */
/*-------------------------------------------------------------------------------------------------------------------*/

#include "Uart.h"
#include "SerialInterface.h"
/*-------------------------------------------------------------------------------------------------------------------*/
/*                                             Definition Of Local Macros                                            */
/*-------------------------------------------------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------------------------------------------------*/
/*                                           Definition Of Local Data Types                                          */
/*-------------------------------------------------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------------------------------------------------*/
/*                                           Declaration Of Local Variables                                          */
/*-------------------------------------------------------------------------------------------------------------------*/
uint8 * puc_ReceiveAddrSpeed;

/*-------------------------------------------------------------------------------------------------------------------*/
/*                                          Declaration Of Global Variables                                          */
/*-------------------------------------------------------------------------------------------------------------------*/
Rte_SpeedType SerialInterface_Speed;
Rte_BatteryVoltageType SerialInterface_BatteryLevel;
Rte_UartEnableType SerialInterface_UartFlagEnable;
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

/*
 *  \brief
 *  \param
 *  \return
 */
void SerialInterface_Init(void)
{
   SerialInterface_Speed = 0UL;
   SerialInterface_BatteryLevel = 0UL;
}

/*
 *  \brief
 *  \param
 *  \return
 */
void SerialInterface_Receive()
{
   uint8 uc_Receive;
   IoHwAbUartReceiveData(IOHWAB_UART_RX_PIN, &uc_Receive);
   switch (uc_Receive)
   {
      case 0x73:
         break;
      default:
         break;

   }
}

/*
 *  \brief
 *  \param
 *  \return
 */
void SerialInterface_TransmitSpeed()
{
   Rte_Read_In_UartFlag(&SerialInterface_UartFlagEnable);
   if (SerialInterface_UartFlagEnable == STD_ON)
   {
      uint8 uc_SpeedIdentifier = 0x73;
      IoHwAbUartTransmitData(IOHWAB_UART_TX_PIN, &uc_SpeedIdentifier);
      Rte_Read_In_RpmValue(&SerialInterface_Speed);
      uint8 uc_LowBits = (uint8) SerialInterface_Speed;
      uint8 uc_HighBits = (uint8) (SerialInterface_Speed >> 8);
      IoHwAbUartTransmitData(IOHWAB_UART_TX_PIN, &uc_LowBits);
      IoHwAbUartTransmitData(IOHWAB_UART_TX_PIN, &uc_HighBits);
   }
   else
   {

   }
}

/*
 *  \brief
 *  \param
 *  \return
 */
void SerialInterface_TransmitBattery()
{
   Rte_Read_In_UartFlag(&SerialInterface_UartFlagEnable);
   if (SerialInterface_UartFlagEnable == STD_ON)
   {
      uint8 uc_BatteryIdentifier = 0x42;
      IoHwAbUartTransmitData(IOHWAB_UART_TX_PIN, &uc_BatteryIdentifier);
      Rte_Read_In_BatVoltage(&SerialInterface_BatteryLevel);
      uint8 uc_LowBits = (uint8) SerialInterface_BatteryLevel;
      uint8 uc_HighBits = (uint8) (SerialInterface_BatteryLevel >> 8);
      IoHwAbUartTransmitData(IOHWAB_UART_TX_PIN, &uc_LowBits);
      IoHwAbUartTransmitData(IOHWAB_UART_TX_PIN, &uc_HighBits);
   }
   else
   {

   }
}
