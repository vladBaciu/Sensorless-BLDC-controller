/*-------------------------------------------------------------------------------------------------------------------*/
/**
 *    \file       Dio.c
 *    \author     Baciu Vlad-Eusebiu
 *    \brief      Implements the interfaces of DIO module.
 */
/*-------------------------------------------------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------------------------------------------------*/
/*                                                     Inclusions                                                    */
/*-------------------------------------------------------------------------------------------------------------------*/
#include "Dio.h"
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

/**
 * \brief      Read a bit from a GPIOx IDR register. That bit represents the state of the selected channel.
 * \param      ChannelId: index of the channel from channel configuration array.
 * \return     The state of the channel (STD_HIGH or STD_LOW).
 */
Dio_LevelType Dio_ReadChannel(Dio_ChannelType ChannelId)
{
   /* Indicates the state of the channel. */
   Dio_LevelType t_Level = 0;

   /* Read the entire port and store the value of every channel. */
   Dio_PortLevelType t_PortVal = (Dio_PortLevelType) Dio_gkat_PortAdress[Dio_gkat_ChannelCfg[ChannelId].t_Port]
      .pt_Registers->IDR;

   /* Get the mask for the specified channel. */
   Dio_PortLevelType t_Bit = (Dio_PortLevelType) Dio_gkat_ChannelCfg[ChannelId].us_Mask;

   /* Determine the state of the channel. */
   if ((t_PortVal & t_Bit) == t_Bit)
   {

      t_Level = STD_HIGH;
   }
   else
   {

      t_Level = STD_LOW;
   }
   return t_Level;
}

/**
 * \brief      Writes data in ODR register for a specific channel.
 * \param      ChannelId: channel index from channel configuration array.
 * \param      Level: specifies the value to be written (STD_LOW or STD_HIGH).
 * \return     -
 */
void Dio_WriteChannel(Dio_ChannelType ChannelId, Dio_LevelType Level)
{
   /* Get the mask for output register position of the channel. */
   uint16 us_Mask = Dio_gkat_ChannelCfg[ChannelId].us_Mask;

   /* Store the port that the channel belongs to.  */
   Dio_PortType t_Port = Dio_gkat_ChannelCfg[ChannelId].t_Port;

   /* Apply the mask with respect to t_Level value. */
   if (Level == STD_HIGH)
   {
      Dio_gkat_PortAdress[t_Port].pt_Registers->ODR |= us_Mask;
   }
   else
   {
      Dio_gkat_PortAdress[t_Port].pt_Registers->ODR &= ~(us_Mask);
   }

}

/**
 * \brief      Reads the entire IDR port register.
 * \param      PortId: the index of the port in the list of ports.
 * \return     Returns the state of the channels.
 */
Dio_PortLevelType Dio_ReadPort(Dio_PortType PortId)
{
   return (Dio_PortLevelType) Dio_gkat_PortAdress[PortId].pt_Registers->IDR;
}

/**
 * \brief      Writes the ODR port register.
 * \param      PortId: the index of the port in the list of ports.
 * \param      Level:  the state for every channel in the port.
 * \return     -
 */
void Dio_WritePort(Dio_PortType PortId, Dio_PortLevelType Level)
{
   Dio_gkat_PortAdress[PortId].pt_Registers->ODR = (uint32) Level;

}

