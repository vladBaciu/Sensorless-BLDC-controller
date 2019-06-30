/*-------------------------------------------------------------------------------------------------------------------*/
/**
 *    \file       Rte_Joystick.h
 *    \author     RTE Generator
 *    \brief      Generated file - shall not be manually edited. 
 *                Implements all the RTE read and write operations that are performed by the Joystick software
 *                component.
 */
/*-------------------------------------------------------------------------------------------------------------------*/

#ifndef RTE_JOYSTICK_H
#define RTE_JOYSTICK_H

/*-------------------------------------------------------------------------------------------------------------------*/
/*                                                     Inclusions                                                    */
/*-------------------------------------------------------------------------------------------------------------------*/

#include "Rte.h"

/*-------------------------------------------------------------------------------------------------------------------*/
/*                                            Definition Of Global Macros                                            */
/*-------------------------------------------------------------------------------------------------------------------*/

#define Rte_Read_In_BtnJoystick(x) ((*x) = IoHwAb_DigitalGetChannel(IOHWAB_DIGITAL_BTN_JOYSTICK))

#define Rte_Read_In_PotXAxis(x) ((*x) = IoHwAb_AnalogGetChannel(IOHWAB_ANALOG_POTENTIOMETER_X_AXIS))
#define Rte_Read_In_PotYAxis(x) ((*x) = IoHwAb_AnalogGetChannel(IOHWAB_ANALOG_POTENTIOMETER_Y_AXIS))

#define Rte_Write_Out_BtnJoystick(x) (Rte_BtnOut_BtnJoystick_Buf = (*x))

#define Rte_Write_Out_PotXAxis(x) \
   do \
   { \
      Rte_PotXOut_PotXAxis_Buf = (*x); \
      Rte_PotXOut_PotXRaw_PotXAxis_UpdateFlag = TRUE; \
   } while(0)

#define Rte_Write_Out_PotYAxis(x) \
   do \
   { \
      Rte_PotYOut_PotYAxis_Buf = (*x); \
      Rte_PotYOut_PotYRaw_PotYAxis_UpdateFlag = TRUE; \
   } while(0)

#define Rte_Write_Out_PotXLcd(x) \
   do \
   { \
      Rte_PotXOutToLcd_PotXLcd_Buf = (*x); \
      Rte_PotXOutToLcd_PotXIn_PotXLcd_UpdateFlag = TRUE; \
   } while(0)

#define Rte_Write_Out_PotYLcd(x) \
   do \
   { \
      Rte_PotYOutToLcd_PotYLcd_Buf = (*x); \
      Rte_PotYOutToLcd_PotYIn_PotYLcd_UpdateFlag = TRUE; \
   } while(0)

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
#endif /* RTE_JOYSTICK_H */