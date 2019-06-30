/*-------------------------------------------------------------------------------------------------------------------*/
/**
 *    \file       Rte_Buffers.c
 *    \author     RTE Generator
 *    \brief      Generated file - shall not be manually edited. 
 *                Declares all the RTE buffers that are used in the read / write operations.
 */
/*-------------------------------------------------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------------------------------------------------*/
/*                                                     Inclusions                                                    */
/*-------------------------------------------------------------------------------------------------------------------*/

#include "Rte_Buffers.h"
#include "Rte.h"

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

/* Buffers. */
Rte_LedEnableType Rte_LedIn_LedLeft_Buf;
Rte_LedEnableType Rte_LedIn_LedCenter_Buf;
Rte_LedEnableType Rte_LedIn_LedRight_Buf;

Rte_BtnPressType Rte_BtnOut_BtnJoystick_Buf;

Rte_PotPosType Rte_PotXOut_PotXAxis_Buf;

Rte_PotPosType Rte_PotYOut_PotYAxis_Buf;

Rte_JoystickType Rte_PotXOutToLcd_PotXLcd_Buf;

Rte_JoystickType Rte_PotYOutToLcd_PotYLcd_Buf;

Rte_LcdInterfaceType Rte_LcdInterface_LcdStruct_Buf;

Rte_DirectionType Rte_LcdDirection_LcdDirectionIndicator_Buf;

Rte_SpeedType Rte_MotorSpeed_RpmValue_Buf;

Rte_SpeedType Rte_UartSpeed_RpmValueSerial_Buf;

Rte_BatteryPercentageType Rte_BatPercentage_BatLevel_Buf;

Rte_BatteryStateOfChargeType Rte_BatSoc_BatSoc_Buf;

Rte_BatteryVoltageType Rte_BatVoltage_BatVoltage_Buf;

Rte_UartEnableType Rte_UartEnable_UartFlag_Buf;

Rte_CurrentAmpType Rte_CurrentValue_CurrentAmp_Buf;

Rte_MotorFlagType Rte_MotorRunning_MotorFlag_Buf;

Rte_SpeedType Rte_DutyCyclePercentage_Percentage_Buf;

/* Update flags. */
boolean Rte_PotXOutToLcd_PotXIn_PotXLcd_UpdateFlag;
boolean Rte_PotYOutToLcd_PotYIn_PotYLcd_UpdateFlag;
boolean Rte_PotXOut_PotXRaw_PotXAxis_UpdateFlag;
boolean Rte_PotYOut_PotYRaw_PotYAxis_UpdateFlag;
boolean Rte_LcdInterface_In_LcdStruct_UpdateFlag;

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

