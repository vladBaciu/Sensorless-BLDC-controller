/*-------------------------------------------------------------------------------------------------------------------*/
/**
 *    \file       Rte_ControllerSensors.h
 *    \author     RTE Generator
 *    \brief      Generated file - shall not be manually edited. 
 *                Implements all the RTE read and write operations that are performed by the ControllerSensors software
 *                component.
 */
/*-------------------------------------------------------------------------------------------------------------------*/

#ifndef RTE_CONTROLLERSENSORS_H
#define RTE_CONTROLLERSENSORS_H

/*-------------------------------------------------------------------------------------------------------------------*/
/*                                                     Inclusions                                                    */
/*-------------------------------------------------------------------------------------------------------------------*/

#include "Rte.h"

/*-------------------------------------------------------------------------------------------------------------------*/
/*                                            Definition Of Global Macros                                            */
/*-------------------------------------------------------------------------------------------------------------------*/

#define Rte_Read_In_BatteryRaw(x) ((*x) = IoHwAb_AnalogGetChannel(IOHWAB_ANALOG_BATTERY_SENSOR))

#define Rte_Read_In_CurrentRaw(x) ((*x) = IoHwAb_AnalogGetChannel(IOHWAB_ANALOG_CURRENT_SENSOR))

#define Rte_Write_Out_BatteryCommand(x) (IoHwAb_DigitalSetChannel(IOHWAB_DIGITAL_READ_BATTERY_COMMAND, (*x)))

#define Rte_Write_Out_BatLevel(x) (Rte_BatPercentage_BatLevel_Buf = (*x))

#define Rte_Write_Out_BatSoc(x) (Rte_BatSoc_BatSoc_Buf = (*x))

#define Rte_Write_Out_BatVoltage(x) (Rte_BatVoltage_BatVoltage_Buf = (*x))

#define Rte_Write_Out_CurrentAmp(x) (Rte_CurrentValue_CurrentAmp_Buf = (*x))

#define Rte_Write_Out_LedLeft(x) (Rte_LedIn_LedLeft_Buf = (*x))
#define Rte_Write_Out_LedCenter(x) (Rte_LedIn_LedCenter_Buf = (*x))
#define Rte_Write_Out_LedRight(x) (Rte_LedIn_LedRight_Buf = (*x))

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
#endif /* RTE_CONTROLLERSENSORS_H */