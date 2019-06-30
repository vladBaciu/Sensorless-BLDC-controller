/*-------------------------------------------------------------------------------------------------------------------*/
/**
 *    \file       Rte_Buffers.h
 *    \author     RTE Generator
 *    \brief      Generated file - shall not be manually edited. 
 *                Exports all the RTE buffers that are used in the read / write operations.
 */
/*-------------------------------------------------------------------------------------------------------------------*/

#ifndef RTE_BUFFERS_H
#define RTE_BUFFERS_H

/*-------------------------------------------------------------------------------------------------------------------*/
/*                                                     Inclusions                                                    */
/*-------------------------------------------------------------------------------------------------------------------*/

#include "Rte_Type.h"
#include "IoHwAb.h"

/*-------------------------------------------------------------------------------------------------------------------*/
/*                                            Definition Of Global Macros                                            */
/*-------------------------------------------------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------------------------------------------------*/
/*                                          Definition Of Global Data Types                                          */
/*-------------------------------------------------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------------------------------------------------*/
/*                                             Export Of Global Variables                                            */
/*-------------------------------------------------------------------------------------------------------------------*/

/* Buffers. */
extern Rte_LedEnableType Rte_LedIn_LedLeft_Buf;
extern Rte_LedEnableType Rte_LedIn_LedCenter_Buf;
extern Rte_LedEnableType Rte_LedIn_LedRight_Buf;

extern Rte_BtnPressType Rte_BtnOut_BtnJoystick_Buf;

extern Rte_PotPosType Rte_PotXOut_PotXAxis_Buf;

extern Rte_PotPosType Rte_PotYOut_PotYAxis_Buf;

extern Rte_JoystickType Rte_PotXOutToLcd_PotXLcd_Buf;

extern Rte_JoystickType Rte_PotYOutToLcd_PotYLcd_Buf;

extern Rte_LcdInterfaceType Rte_LcdInterface_LcdStruct_Buf;

extern Rte_DirectionType Rte_LcdDirection_LcdDirectionIndicator_Buf;

extern Rte_SpeedType Rte_MotorSpeed_RpmValue_Buf;

extern Rte_SpeedType Rte_UartSpeed_RpmValueSerial_Buf;

extern Rte_BatteryPercentageType Rte_BatPercentage_BatLevel_Buf;

extern Rte_BatteryStateOfChargeType Rte_BatSoc_BatSoc_Buf;

extern Rte_BatteryVoltageType Rte_BatVoltage_BatVoltage_Buf;

extern Rte_UartEnableType Rte_UartEnable_UartFlag_Buf;

extern Rte_CurrentAmpType Rte_CurrentValue_CurrentAmp_Buf;

extern Rte_MotorFlagType Rte_MotorRunning_MotorFlag_Buf;

extern Rte_SpeedType Rte_DutyCyclePercentage_Percentage_Buf;

/* Update flags. */
extern boolean Rte_PotXOutToLcd_PotXIn_PotXLcd_UpdateFlag;
extern boolean Rte_PotYOutToLcd_PotYIn_PotYLcd_UpdateFlag;
extern boolean Rte_PotXOut_PotXRaw_PotXAxis_UpdateFlag;
extern boolean Rte_PotYOut_PotYRaw_PotYAxis_UpdateFlag;
extern boolean Rte_LcdInterface_In_LcdStruct_UpdateFlag;

/*-------------------------------------------------------------------------------------------------------------------*/
/*                                             Export Of Global Constants                                            */
/*-------------------------------------------------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------------------------------------------------*/
/*                                             Export Of Global Functions                                            */
/*-------------------------------------------------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------------------------------------------------*/
#endif /* RTE_BUFFERS_H */