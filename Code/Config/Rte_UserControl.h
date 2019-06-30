/*-------------------------------------------------------------------------------------------------------------------*/
/**
 *    \file       Rte_UserControl.h
 *    \author     RTE Generator
 *    \brief      Generated file - shall not be manually edited. 
 *                Implements all the RTE read and write operations that are performed by the UserControl software
 *                component.
 */
/*-------------------------------------------------------------------------------------------------------------------*/

#ifndef RTE_USERCONTROL_H
#define RTE_USERCONTROL_H

/*-------------------------------------------------------------------------------------------------------------------*/
/*                                                     Inclusions                                                    */
/*-------------------------------------------------------------------------------------------------------------------*/

#include "Rte.h"

/*-------------------------------------------------------------------------------------------------------------------*/
/*                                            Definition Of Global Macros                                            */
/*-------------------------------------------------------------------------------------------------------------------*/

#define Rte_IsUpdated_PotXIn_PotXLcd() (Rte_PotXOutToLcd_PotXIn_PotXLcd_UpdateFlag)
#define Rte_Read_PotXIn_PotXLcd(x) \
   do \
   { \
      (*x) = Rte_PotXOutToLcd_PotXLcd_Buf; \
      Rte_PotXOutToLcd_PotXIn_PotXLcd_UpdateFlag = FALSE; \
   } while(0)

#define Rte_IsUpdated_PotYIn_PotYLcd() (Rte_PotYOutToLcd_PotYIn_PotYLcd_UpdateFlag)
#define Rte_Read_PotYIn_PotYLcd(x) \
   do \
   { \
      (*x) = Rte_PotYOutToLcd_PotYLcd_Buf; \
      Rte_PotYOutToLcd_PotYIn_PotYLcd_UpdateFlag = FALSE; \
   } while(0)

#define Rte_Read_BtnIn_BtnJoystick(x) ((*x) = Rte_BtnOut_BtnJoystick_Buf)

#define Rte_IsUpdated_PotXRaw_PotXAxis() (Rte_PotXOut_PotXRaw_PotXAxis_UpdateFlag)
#define Rte_Read_PotXRaw_PotXAxis(x) \
   do \
   { \
      (*x) = Rte_PotXOut_PotXAxis_Buf; \
      Rte_PotXOut_PotXRaw_PotXAxis_UpdateFlag = FALSE; \
   } while(0)

#define Rte_IsUpdated_PotYRaw_PotYAxis() (Rte_PotYOut_PotYRaw_PotYAxis_UpdateFlag)
#define Rte_Read_PotYRaw_PotYAxis(x) \
   do \
   { \
      (*x) = Rte_PotYOut_PotYAxis_Buf; \
      Rte_PotYOut_PotYRaw_PotYAxis_UpdateFlag = FALSE; \
   } while(0)

#define Rte_Write_Out_LcdStruct(x) \
   do \
   { \
      Rte_LcdInterface_LcdStruct_Buf = (*x); \
      Rte_LcdInterface_In_LcdStruct_UpdateFlag = TRUE; \
   } while(0)

#define Rte_Write_Out_LcdDirectionIndicator(x) (Rte_LcdDirection_LcdDirectionIndicator_Buf = (*x))

#define Rte_Write_Out_RpmValue(x) (Rte_MotorSpeed_RpmValue_Buf = (*x))

#define Rte_Write_Out_UartFlag(x) (Rte_UartEnable_UartFlag_Buf = (*x))

#define Rte_Write_Out_LedLeft(x) (Rte_LedIn_LedLeft_Buf = (*x))
#define Rte_Write_Out_LedCenter(x) (Rte_LedIn_LedCenter_Buf = (*x))
#define Rte_Write_Out_LedRight(x) (Rte_LedIn_LedRight_Buf = (*x))

#define Rte_Write_Out_MotorFlag(x) (Rte_MotorRunning_MotorFlag_Buf = (*x))

#define Rte_Write_Out_Percentage(x) (Rte_DutyCyclePercentage_Percentage_Buf = (*x))

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
#endif /* RTE_USERCONTROL_H */