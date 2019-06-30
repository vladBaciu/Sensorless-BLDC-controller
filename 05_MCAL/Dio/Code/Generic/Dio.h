/*-------------------------------------------------------------------------------------------------------------------*/
/**
 *    \file       Dio.h
 *    \author     Baciu Vlad-Eusebiu
 *    \brief      Exports DIO data types, the DIO configuration and the interfaces of DIO module.
 */
/*-------------------------------------------------------------------------------------------------------------------*/

#ifndef DIO_H
#define DIO_H

/*-------------------------------------------------------------------------------------------------------------------*/
/*                                                     Inclusions                                                    */
/*-------------------------------------------------------------------------------------------------------------------*/
#include "Std_Types.h"
#include "stm32f407xx.h"
#include "Dio_Cfg.h"
/*-------------------------------------------------------------------------------------------------------------------*/
/*                                            Definition Of Global Macros                                            */
/*-------------------------------------------------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------------------------------------------------*/
/*                                          Definition Of Global Data Types                                          */
/*-------------------------------------------------------------------------------------------------------------------*/
/** \brief  Type for possibile levels that a DIO channel can have (STD_HIGH/STD_LOW). */
typedef uint8 Dio_LevelType;
/** \brief  Type that indicates the numeric ID of a DIO channel. */
typedef uint8 Dio_ChannelType;
/** \brief  Type that indicates the numeric ID of a DIO port.  */
typedef uint16 Dio_PortType;
/** \brief  Type that inherits the size of the port for STM32F4. */
typedef uint16 Dio_PortLevelType;
/** \brief  Configuration type for a channel inside a port. */
typedef struct
{

   /** \brief  Mask that indicates the position of channel in ODR/IDR register. */
   uint16 us_Mask;
   /** \brief  Indicates the port that channel belongs to. */
   Dio_PortType t_Port;

} Dio_ChannelCfgType;
/** \brief  Configuration type for a port. */
typedef struct
{
   /** \brief Pointer to GPIO port struct. */
   GPIO_TypeDef * pt_Registers;

} Dio_PortCfgType;
/*-------------------------------------------------------------------------------------------------------------------*/
/*                                             Export Of Global Variables                                            */
/*-------------------------------------------------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------------------------------------------------*/
/*                                             Export Of Global Constants                                            */
/*-------------------------------------------------------------------------------------------------------------------*/
extern const Dio_ChannelCfgType Dio_gkat_ChannelCfg[DIO_NUMBER_OF_CHANNELS];
extern const Dio_PortCfgType Dio_gkat_PortAdress[DIO_NUMBER_OF_PORTS];
/*-------------------------------------------------------------------------------------------------------------------*/
/*                                             Export Of Global Functions                                            */
/*-------------------------------------------------------------------------------------------------------------------*/
extern Dio_LevelType Dio_ReadChannel(Dio_ChannelType ChannelId);
extern void Dio_WriteChannel(Dio_ChannelType ChannelId, Dio_LevelType Level);
extern Dio_PortLevelType Dio_ReadPort(Dio_PortType PortId);
extern void Dio_WritePort(Dio_PortType PortId, Dio_PortLevelType Level);

/*-------------------------------------------------------------------------------------------------------------------*/
#endif /* DIO_H */
