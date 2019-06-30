/*-------------------------------------------------------------------------------------------------------------------*/
/**
 *    \file       ControllerSensors.c
 *    \author     Baciu Vlad-Eusebiu
 *    \brief      Empty template to be used for all .c files. This file provides an example for the case in which a
 *                detailed description is not needed.
 */
/*-------------------------------------------------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------------------------------------------------*/
/*                                                     Inclusions                                                    */
/*-------------------------------------------------------------------------------------------------------------------*/
#include "ControllerSensors.h"
#include "Rte_ControllerSensors.h"
#include "DigitalSmooth.h"
/*-------------------------------------------------------------------------------------------------------------------*/
/*                                             Definition Of Local Macros                                            */
/*-------------------------------------------------------------------------------------------------------------------*/
#define CONTROLLERSENSORS_SOC_NUMBER                  (10U)

#define CONTROLLERSSENSORS_VCC                        (3000U)

#define CONTROLLERSENSORS_MAX_VALUE                   (4095U)

#define CONTROLLERSENSORS_RESISTOR1_VALUE             (150U)

#define CONTROLLERSENSORS_RESISTOR2_VALUE             (13U)

#define CONTROLLERSENSORS_HIGH_LIMIT_L                (70U)

#define CONTROLLERSENSORS_HIGH_LIMIT_H                (100U)

#define CONTROLLERSENSORS_MEDIUM_LIMIT_L              (30U)

#define CONTROLLERSENSORS_MEDIUM_LIMIT_H              (70U)
/*-------------------------------------------------------------------------------------------------------------------*/
/*                                           Definition Of Local Data Types                                          */
/*-------------------------------------------------------------------------------------------------------------------*/
typedef IoHwAb_AnalogLevelType ControllerSensors_BatteryVoltage;
typedef uint8 ControllerControllerSensors_BatteryPercentage;
typedef uint8 ControllerSensors_BatteryStateOfCharge;
typedef struct
{
   ControllerSensors_BatteryVoltage t_Voltage;
   ControllerControllerSensors_BatteryPercentage t_Percentage;
} ControllerSensors_StateOfChargeTable;
/*-------------------------------------------------------------------------------------------------------------------*/
/*                                           Declaration Of Local Variables                                          */
/*-------------------------------------------------------------------------------------------------------------------*/
const ControllerSensors_StateOfChargeTable at_StateOfCharge[CONTROLLERSENSORS_SOC_NUMBER] =
{
   { 37650, 100 },
   { 37600, 90 },
   { 37500, 80 },
   { 37120, 70 },
   { 36720, 60 },
   { 36310, 50 },
   { 35870, 40 },
   { 35440, 30 },
   { 34900, 20 },
   { 34500, 10 }

};

IoHwAb_AnalogLevelType ControllerSensors_t_AdcBateryValue;
IoHwAb_AnalogLevelType ControllerSensors_t_AdcCurrentValue;
DigitalSmooth_MedianFilter ControllerSensors_T_BatteryFilterBuffer;
DigitalSmooth_MedianFilter ControllerSensors_T_CurrentFilterBuffer;
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
ControllerSensors_BatteryStateOfCharge ControllerSensors_BatterySOC(uint16 BatteryLevel)
{
   ControllerSensors_BatteryStateOfCharge uc_ReturnValue = 0;

   if ((BatteryLevel >= CONTROLLERSENSORS_HIGH_LIMIT_L) && (BatteryLevel <= CONTROLLERSENSORS_HIGH_LIMIT_H))
   {
      uc_ReturnValue = Sensors_ChargedBattery;
   }
   else if ((BatteryLevel >= CONTROLLERSENSORS_MEDIUM_LIMIT_L) && (BatteryLevel < CONTROLLERSENSORS_MEDIUM_LIMIT_H))
   {
      uc_ReturnValue = Sensors_MediumBattery;
   }
   else
   {
      uc_ReturnValue = Sensors_DischargedBattery;
   }

   return uc_ReturnValue;
}

IoHwAb_AnalogLevelType ControllerSensors_BatteryLevel(uint16 AdcValue)
{
   IoHwAb_AnalogLevelType uc_BatteryVoltage = 0;
   /* Get the voltage from the voltage divider
    * must be divided by 100 for real value*/
   IoHwAb_AnalogLevelType uc_AdcVoltage = (CONTROLLERSSENSORS_VCC * AdcValue) / CONTROLLERSENSORS_MAX_VALUE;
   /* Get the battery voltage
    * must be divided by 1000 for real value*/
   uc_BatteryVoltage =
   ((uc_AdcVoltage * (CONTROLLERSENSORS_RESISTOR1_VALUE + CONTROLLERSENSORS_RESISTOR2_VALUE))
      / CONTROLLERSENSORS_RESISTOR2_VALUE);

   return uc_BatteryVoltage;
}

ControllerControllerSensors_BatteryPercentage ControllerSensors_BatteryPercentage(uint16 BatteryVoltage)
{
   uint8 uc_I = 0;
   ControllerControllerSensors_BatteryPercentage uc_ReturnValue = 0;
   if (BatteryVoltage < at_StateOfCharge[CONTROLLERSENSORS_SOC_NUMBER - 1].t_Voltage)
   {
      uc_ReturnValue = 10;
   }
   else
      for (uc_I = 0; uc_I < CONTROLLERSENSORS_SOC_NUMBER; uc_I++)
      {
         if ((BatteryVoltage < at_StateOfCharge[uc_I].t_Voltage)
            && (BatteryVoltage >= at_StateOfCharge[uc_I + 1].t_Voltage))
         {
            uc_ReturnValue = at_StateOfCharge[uc_I + 1].t_Percentage
               + ((100 * (at_StateOfCharge[uc_I].t_Percentage
                  - at_StateOfCharge[uc_I + 1].t_Percentage)
                  / (at_StateOfCharge[uc_I].t_Voltage - at_StateOfCharge[uc_I + 1].t_Voltage))
                  * (BatteryVoltage - at_StateOfCharge[uc_I + 1].t_Voltage)) / 100;

            uc_I = CONTROLLERSENSORS_SOC_NUMBER;
         }
         else
         {
            uc_ReturnValue = 99;
         }
      }

   return uc_ReturnValue;
}
/*-------------------------------------------------------------------------------------------------------------------*/
/*                                         Implementation Of Global Functions                                        */
/*-------------------------------------------------------------------------------------------------------------------*/
void ControllerSensors_Init()
{
   ControllerSensors_t_AdcBateryValue = 0;
   ControllerSensors_t_AdcCurrentValue = 0;
   ControllerSensors_T_BatteryFilterBuffer.uc_Count = 0;
   ControllerSensors_T_BatteryFilterBuffer.uc_Position = 0;
   ControllerSensors_T_CurrentFilterBuffer.uc_Count = 0;
   ControllerSensors_T_CurrentFilterBuffer.uc_Position = 0;

}
void ControllerSensors_ReadBattery()
{
   IoHwAb_DigitalLevelType t_Command;
   IoHwAb_AnalogLevelType t_FilteredAdc;
   IoHwAb_AnalogLevelType t_BatteryVoltage;
   ControllerControllerSensors_BatteryPercentage t_BatteryPercentage;
   ControllerSensors_BatteryStateOfCharge t_BatteryStateOfCharge;
   uint8 uc_BatteryIndicator = 0;
   t_Command = STD_HIGH;
   Rte_Write_Out_BatteryCommand(&t_Command);
   Rte_Read_In_BatteryRaw(&ControllerSensors_t_AdcBateryValue);
   t_FilteredAdc = DigitalSmooth_Filter(&ControllerSensors_T_BatteryFilterBuffer, ControllerSensors_t_AdcBateryValue);
   t_BatteryVoltage = ControllerSensors_BatteryLevel(t_FilteredAdc);
   t_BatteryVoltage = t_BatteryVoltage + 1600;
   t_BatteryPercentage = ControllerSensors_BatteryPercentage(t_BatteryVoltage);
   if(t_BatteryPercentage < 60 )
   {
      uc_BatteryIndicator = 1;
   }
   t_BatteryStateOfCharge = ControllerSensors_BatterySOC(t_BatteryPercentage);
   t_Command = STD_LOW;
   Rte_Write_Out_BatteryCommand(&t_Command);
   Rte_Write_Out_BatLevel(&t_BatteryPercentage);
   Rte_Write_Out_BatSoc(&t_BatteryStateOfCharge);
   Rte_Write_Out_BatVoltage(&t_BatteryVoltage);
   Rte_Write_Out_LedLeft(&uc_BatteryIndicator);
}
void ControllerSensors_ReadCurrent()
{
   IoHwAb_AnalogLevelType t_FilteredAdc;
   IoHwAb_AnalogLevelType ul_Voltage;
   Rte_CurrentAmpType ul_Current;
   Rte_Read_In_CurrentRaw(&ControllerSensors_t_AdcCurrentValue);
   t_FilteredAdc = DigitalSmooth_Filter(&ControllerSensors_T_CurrentFilterBuffer, ControllerSensors_t_AdcCurrentValue);
   if (t_FilteredAdc < 40)
   {
      ul_Voltage = (IoHwAb_AnalogLevelType) ((3000UL * t_FilteredAdc) / 4095);
   }
   else
   {
      ul_Voltage = (IoHwAb_AnalogLevelType) ((3000UL * t_FilteredAdc) / 4095) - 200;
   }
   if (ul_Voltage < 1500)
   {
      ul_Current = 0;
   }
   else if(ul_Voltage > 2700)
   {
      ul_Current = 0;
   }
   else
   {
      ul_Current = (Rte_CurrentAmpType) (ul_Voltage - 1500) * 40;
   }

   Rte_Write_Out_CurrentAmp(&ul_Current);
}
