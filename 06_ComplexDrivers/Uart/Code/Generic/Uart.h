/*-------------------------------------------------------------------------------------------------------------------*/
/**
 *    \file       Uart.h
 *    \author     Baciu Vlad-Eusebiu
 *    \brief      Declares UART functions, exports the array configuration and define global data types.
 */
/*-------------------------------------------------------------------------------------------------------------------*/

#ifndef UART_H
#define UART_H

/*-------------------------------------------------------------------------------------------------------------------*/
/*                                                     Inclusions                                                    */
/*-------------------------------------------------------------------------------------------------------------------*/
#include "Std_Types.h"
#include "stm32f407xx.h"
#include "RegInit.h"
#include "Uart_Cfg.h"
/*-------------------------------------------------------------------------------------------------------------------*/
/*                                            Definition Of Global Macros                                            */
/*-------------------------------------------------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------------------------------------------------*/
/*                                          Definition Of Global Data Types                                          */
/*-------------------------------------------------------------------------------------------------------------------*/
/** \brief Status types for transmit process */
typedef enum
{
   UART_TX_BUSY,
   UART_TX_READY
} Uart_TxStatusType;

/** \brief Status types for receive process */
typedef enum
{
   UART_RX_NO_DATA,
   UART_RX_READY
} Uart_RxStatusType;

/** \brief Uart channel type */
typedef uint8 Uart_ChannelType;

/** \brief Channel config type */
typedef struct
{
   Uart_ChannelType t_Channel;
   USART_TypeDef * pt_Registers;
} Uart_GroupCfgType;

typedef struct
{
   const Uart_GroupCfgType *pt_ConfigGroup;
   const RegInit_Masked32BitsConfigType* pt_ConfigRegisters;
} Uart_ConfigType;
/*-------------------------------------------------------------------------------------------------------------------*/
/*                                             Export Of Global Variables                                            */
/*-------------------------------------------------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------------------------------------------------*/
/*                                             Export Of Global Constants                                            */
/*-------------------------------------------------------------------------------------------------------------------*/
extern const Uart_ConfigType Uart_gkt_Cfg;
/*-------------------------------------------------------------------------------------------------------------------*/
/*                                             Export Of Global Functions                                            */
/*-------------------------------------------------------------------------------------------------------------------*/
extern void Uart_gv_Init(const Uart_ConfigType * pt_Config);
extern Uart_TxStatusType Uart_gt_GetTransmitStatus(Uart_ChannelType t_ChannelId);
extern Uart_RxStatusType Uart_gt_GetReceiveStatus(Uart_ChannelType t_ChannelId);
extern void Uart_gv_Transmit(Uart_ChannelType t_ChannelId, uint8 * puc_TransmitAddr);
extern void Uart_gv_Receive(Uart_ChannelType t_ChannelId, uint8 * puc_ReceiveAddr);
/*-------------------------------------------------------------------------------------------------------------------*/
#endif /* UART_H */
