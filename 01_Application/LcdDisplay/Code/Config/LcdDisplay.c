/*-------------------------------------------------------------------------------------------------------------------*/
/**
 *    \file       LcdDisplay.c
 *    \author     Baciu Vlad-Eusebiu
 *    \brief      Empty template to be used for all .c files. This file provides an example for the case in which a
 *                detailed description is not needed.
 */
/*-------------------------------------------------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------------------------------------------------*/
/*                                                     Inclusions                                                    */
/*-------------------------------------------------------------------------------------------------------------------*/
#include "LcdDisplay.h"
#include "UserControl.h"
#include "Rte_LcdDisplay.h"
#include "ControllerSensors.h"
/*-------------------------------------------------------------------------------------------------------------------*/
/*                                             Definition Of Local Macros                                            */
/*-------------------------------------------------------------------------------------------------------------------*/
#define LCDDISPLAY_UP_ARROW_RAM_INDEX             (0x00U)

#define LCDDISPLAY_DOWN_ARROW_RAM_INDEX           (0x01U)

#define LCDDISPLAY_BATTERY_FULLY_CHARGED          (0x02U)

#define LCDDISPLAY_BATTERY_ALMOST_CHARGED         (0x03U)

#define LCDDISPLAY_BATTERY_DISCHARGED_CHARGED     (0x04U)

#define LCDDISPLAY_ARROW_INDICATOR                (0x05U)

#define LCDDISPLAY_ARROW_SUBMENU                  (0x06U)

#define LCDDISPLAY_SMILEY_FACE                    (0x07U)

#define LCDDISPLAY_VOLTAGE_DIGITS                 (5U)

#define LCDDISPLAY_AMPERE_DIGITS                 (5U)

#define LCDDISPLAY_RPM_DIGITS                   (4U)

#define LCDDISPLAY_DUTY_DIGITS                  (3U)
/*-------------------------------------------------------------------------------------------------------------------*/
/*                                           Definition Of Local Data Types                                          */
/*-------------------------------------------------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------------------------------------------------*/
/*                                           Declaration Of Local Variables                                          */
/*-------------------------------------------------------------------------------------------------------------------*/
static uint8 uc_ClearFlag = 1;
uint8 *LcdDisplay_puc_BatPercentage;
/*-------------------------------------------------------------------------------------------------------------------*/
/*                                          Declaration Of Global Variables                                          */
/*-------------------------------------------------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------------------------------------------------*/
/*                                           Declaration Of Local Constants                                          */
/*-------------------------------------------------------------------------------------------------------------------*/
char * UserLcd_pc_InitMessage1 = "SENSORLESS BLDC";
char * UserLcd_pc_InitMessage2 = "CONTROLLER";

char * UserLcd_pc_Interfaces[] =
{ "MOTOR CONTROL",
   "BATTERY LEVEL",
   "CURRENT LEVEL",
   "UART INTERFACE"
};

char * UserLcd_pc_SubInterfaces[] =
{ "DIRECTION",
   "START",
   "SPEED"
};

char * UserLcd_pc_SubInterfaces2[] =
{ "F",
   "B"
};

char *UserLcd_pc_CustomMessages[] =
{
   "",
   "START-PRESS BTN",
   "DIR: ",
   "BACKWARD",
   "FORWARD",
   "SPEED: ",
   "RPM",
   "BAUD RATE: ",
   "9600",
   "PARITY: ",
   "NONE",
   "STOP BITS: ",
   "2",
   "DATA FRAME: ",
   "8",
   "ENABLE",
   "DISABLE",
   " ",
   "%"

};

Rte_BatteryPercentageType LcdDisplay_t_BatteryPercentage;
Rte_BatteryStateOfChargeType LcdDisplay_t_BatterySoc;
Rte_BatteryVoltageType LcdDisplay_t_BatteryVoltage;
Rte_CurrentAmpType LcdDisplay_t_CurrentValue;
Rte_SpeedType LcdDisplay_t_RpmValue;
Rte_SpeedType LcdDisplay_t_DutySpeed;
/*-------------------------------------------------------------------------------------------------------------------*/
/*                                          Declaration Of Global Constants                                          */
/*-------------------------------------------------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------------------------------------------------*/
/*                                           Declaration Of Local Functions                                          */
/*-------------------------------------------------------------------------------------------------------------------*/
void LcdDisplay_RteUpdate(void);
void LcdDisplay_DisplayVoltage(Rte_BatteryVoltageType LcdDisplay_t_BatteryVoltage);
void LcdDisplay_DisplayPercentage(Rte_BatteryPercentageType LcdDisplay_t_BatteryPercentage);
Rte_BatteryPercentageType LcdDisplay_DisplayIndicator(Rte_BatteryPercentageType LcdDisplay_t_BatteryPercentage);
void LcdDisplay_DisplayCurrent(Rte_CurrentAmpType LcdDisplay_t_CurrentValue);
void LcdDisplay_DisplayRpm(Rte_SpeedType LcdDisplay_t_RpmValue);
void LcdDisplay_DisplayDuty(Rte_SpeedType LcdDisplay_t_DutyValue);
/*-------------------------------------------------------------------------------------------------------------------*/
/*                                         Implementation Of Local Functions                                         */
/*-------------------------------------------------------------------------------------------------------------------*/
/*
 * \brief
 * \param
 * \return
 */
void LcdDisplay_RteUpdate(void)
{
   Rte_Read_In_BatLevel(&LcdDisplay_t_BatteryPercentage);
   Rte_Read_In_BatSoc(&LcdDisplay_t_BatterySoc);
   Rte_Read_In_BatVoltage(&LcdDisplay_t_BatteryVoltage);
   Rte_Read_In_CurrentAmp(&LcdDisplay_t_CurrentValue);
   Rte_Read_In_RpmValue(&LcdDisplay_t_RpmValue);
   Rte_Read_In_Percentage(&LcdDisplay_t_DutySpeed);
}

/*
 * \brief
 * \param
 * \return
 */
Rte_BatteryPercentageType LcdDisplay_DisplayIndicator(Rte_BatteryPercentageType LcdDisplay_t_BatteryPercentage)
{
   Rte_BatteryPercentageType t_Return;
   if (Sensors_DischargedBattery == LcdDisplay_t_BatteryPercentage)
   {
      t_Return = LCDDISPLAY_BATTERY_DISCHARGED_CHARGED;
   }
   else if (Sensors_MediumBattery == LcdDisplay_t_BatteryPercentage)
   {
      t_Return = LCDDISPLAY_BATTERY_ALMOST_CHARGED;
   }
   else if (Sensors_ChargedBattery == LcdDisplay_t_BatteryPercentage)
   {
      t_Return = LCDDISPLAY_BATTERY_FULLY_CHARGED;
   }
   else
   {
      t_Return = LCDDISPLAY_BATTERY_DISCHARGED_CHARGED;
   }
   return t_Return;
}

/*
 * \brief
 * \param
 * \return
 */
void LcdDisplay_DisplayPercentage(Rte_BatteryPercentageType LcdDisplay_t_BatteryPercentage)
{
   uint8 uc_Index0, uc_Index1;
   char *puc_Index0;
   char *puc_Index1;
   char *puc_Percentage = "%";
   uc_Index0 = LcdDisplay_t_BatteryPercentage % 10;
   LcdDisplay_t_BatteryPercentage = LcdDisplay_t_BatteryPercentage / 10;
   uc_Index1 = LcdDisplay_t_BatteryPercentage % 10;
   LcdDisplay_t_BatteryPercentage = LcdDisplay_t_BatteryPercentage / 10;

   switch (uc_Index0)
   {
      case 0:
      puc_Index0 = "0";
         break;
      case 1:
      puc_Index0 = "1";
         break;
      case 2:
      puc_Index0 = "2";
         break;
      case 3:
      puc_Index0 = "3";
         break;
      case 4:
      puc_Index0 = "4";
         break;
      case 5:
      puc_Index0 = "5";
         break;
      case 6:
      puc_Index0 = "6";
         break;
      case 7:
      puc_Index0 = "7";
         break;
      case 8:
      puc_Index0 = "8";
         break;
      case 9:
      puc_Index0 = "9";
         break;
      default:
      puc_Index0 = "";
         break;
   }

   switch (uc_Index1)
   {
      case 0:
      puc_Index1 = "0";
         break;
      case 1:
      puc_Index1 = "1";
         break;
      case 2:
      puc_Index1 = "2";
         break;
      case 3:
      puc_Index1 = "3";
         break;
      case 4:
      puc_Index1 = "4";
         break;
      case 5:
      puc_Index1 = "5";
         break;
      case 6:
      puc_Index1 = "6";
         break;
      case 7:
      puc_Index1 = "7";
         break;
      case 8:
      puc_Index1 = "8";
         break;
      case 9:
      puc_Index1 = "9";
         break;
      default:
      puc_Index1 = "";
         break;
   }
   IoHwAb_LcdSendStringXY(1, 10, (uint8*) puc_Index1);
   IoHwAb_LcdSendStringXY(1, 11, (uint8*) puc_Index0);
   IoHwAb_LcdSendStringXY(1, 12, (uint8*) puc_Percentage);
}

/*
 * \brief
 * \param
 * \return
 */
void LcdDisplay_DisplayVoltage(Rte_BatteryVoltageType LcdDisplay_t_BatteryVoltage)
{
   char *puc_Dot = ".";
   char *puc_Volt = "V";
   char *puc_Index[LCDDISPLAY_VOLTAGE_DIGITS];
   uint8 uc_Index[LCDDISPLAY_VOLTAGE_DIGITS];
   for (uint8 uc_I = 0; uc_I <= (LCDDISPLAY_VOLTAGE_DIGITS - 1); uc_I++)
   {
      uc_Index[uc_I] = LcdDisplay_t_BatteryVoltage % 10;
      LcdDisplay_t_BatteryVoltage = LcdDisplay_t_BatteryVoltage / 10;
      switch (uc_Index[uc_I])
      {
         case 0:
         puc_Index[uc_I] = "0";
            break;
         case 1:
         puc_Index[uc_I] = "1";
            break;
         case 2:
         puc_Index[uc_I] = "2";
            break;
         case 3:
         puc_Index[uc_I] = "3";
            break;
         case 4:
         puc_Index[uc_I] = "4";
            break;
         case 5:
         puc_Index[uc_I] = "5";
            break;
         case 6:
         puc_Index[uc_I] = "6";
            break;
         case 7:
         puc_Index[uc_I] = "7";
            break;
         case 8:
         puc_Index[uc_I] = "8";
            break;
         case 9:
         puc_Index[uc_I] = "9";
            break;
         default:
         puc_Index[uc_I] = "";
            break;
      }
   }

   IoHwAb_LcdSendStringXY(1, 0, (uint8*) puc_Index[LCDDISPLAY_VOLTAGE_DIGITS - 1]);
   IoHwAb_LcdSendStringXY(1, 1, (uint8*) puc_Index[LCDDISPLAY_VOLTAGE_DIGITS - 2]);
   IoHwAb_LcdSendStringXY(1, 2, (uint8*) puc_Dot);
   IoHwAb_LcdSendStringXY(1, 3, (uint8*) puc_Index[LCDDISPLAY_VOLTAGE_DIGITS - 3]);
   IoHwAb_LcdSendStringXY(1, 4, (uint8*) puc_Index[LCDDISPLAY_VOLTAGE_DIGITS - 4]);
   IoHwAb_LcdSendStringXY(1, 5, (uint8*) puc_Volt);
}

/*
 *  \brief
 *  \param
 *  \return
 */
void LcdDisplay_DisplayCurrent(Rte_CurrentAmpType LcdDisplay_t_CurrentValue)
{
   char *puc_Dot = ".";
   char *puc_Ampere = "A";
   char *puc_Index[LCDDISPLAY_AMPERE_DIGITS];
   uint8 uc_Index[LCDDISPLAY_AMPERE_DIGITS];
   for (uint8 uc_I = 0; uc_I <= (LCDDISPLAY_AMPERE_DIGITS - 1); uc_I++)
   {
      uc_Index[uc_I] = LcdDisplay_t_CurrentValue % 10;
      LcdDisplay_t_CurrentValue = LcdDisplay_t_CurrentValue / 10;
      switch (uc_Index[uc_I])
      {
         case 0:
         puc_Index[uc_I] = "0";
            break;
         case 1:
         puc_Index[uc_I] = "1";
            break;
         case 2:
         puc_Index[uc_I] = "2";
            break;
         case 3:
         puc_Index[uc_I] = "3";
            break;
         case 4:
         puc_Index[uc_I] = "4";
            break;
         case 5:
         puc_Index[uc_I] = "5";
            break;
         case 6:
         puc_Index[uc_I] = "6";
            break;
         case 7:
         puc_Index[uc_I] = "7";
            break;
         case 8:
         puc_Index[uc_I] = "8";
            break;
         case 9:
         puc_Index[uc_I] = "9";
            break;
         default:
         puc_Index[uc_I] = "";
            break;
      }
   }

   IoHwAb_LcdSendStringXY(1, 0, (uint8*) puc_Index[LCDDISPLAY_AMPERE_DIGITS - 1]);
   IoHwAb_LcdSendStringXY(1, 1, (uint8*) puc_Index[LCDDISPLAY_AMPERE_DIGITS - 2]);
   IoHwAb_LcdSendStringXY(1, 2, (uint8*) puc_Dot);
   IoHwAb_LcdSendStringXY(1, 3, (uint8*) puc_Index[LCDDISPLAY_AMPERE_DIGITS - 3]);
   IoHwAb_LcdSendStringXY(1, 4, (uint8*) puc_Index[LCDDISPLAY_AMPERE_DIGITS - 4]);
   IoHwAb_LcdSendStringXY(1, 5, (uint8*) puc_Ampere);
}

/*
 *  \brief
 *  \param
 *  \return
 */
void LcdDisplay_DisplayRpm(Rte_SpeedType LcdDisplay_t_RpmValue)
{

   char *puc_Index[LCDDISPLAY_RPM_DIGITS];
   uint8 uc_Index[LCDDISPLAY_RPM_DIGITS];
   uint16 uc_RpmAux;
   uc_RpmAux = LcdDisplay_t_RpmValue;
   for (uint8 uc_I = 0; uc_I <= (LCDDISPLAY_RPM_DIGITS - 1); uc_I++)
   {
      uc_Index[uc_I] = LcdDisplay_t_RpmValue % 10;
      LcdDisplay_t_RpmValue = LcdDisplay_t_RpmValue / 10;
      switch (uc_Index[uc_I])
      {
         case 0:
         puc_Index[uc_I] = "0";
            break;
         case 1:
         puc_Index[uc_I] = "1";
            break;
         case 2:
         puc_Index[uc_I] = "2";
            break;
         case 3:
         puc_Index[uc_I] = "3";
            break;
         case 4:
         puc_Index[uc_I] = "4";
            break;
         case 5:
         puc_Index[uc_I] = "5";
            break;
         case 6:
         puc_Index[uc_I] = "6";
            break;
         case 7:
         puc_Index[uc_I] = "7";
            break;
         case 8:
         puc_Index[uc_I] = "8";
            break;
         case 9:
         puc_Index[uc_I] = "9";
            break;
         default:
         puc_Index[uc_I] = "";
            break;
      }
   }
   if (uc_RpmAux < 10)
   {
      IoHwAb_LcdSendStringXY(1, 0, (uint8*) UserLcd_pc_CustomMessages[17]);
      IoHwAb_LcdSendStringXY(1, 1, (uint8*) UserLcd_pc_CustomMessages[17]);
      IoHwAb_LcdSendStringXY(1, 2, (uint8*) UserLcd_pc_CustomMessages[17]);
      IoHwAb_LcdSendStringXY(1, 3, (uint8*) puc_Index[LCDDISPLAY_RPM_DIGITS - 4]);
   }
   else if ((uc_RpmAux >= 10) && (uc_RpmAux <= 99))
   {
      IoHwAb_LcdSendStringXY(1, 0, (uint8*) UserLcd_pc_CustomMessages[17]);
      IoHwAb_LcdSendStringXY(1, 1, (uint8*) UserLcd_pc_CustomMessages[17]);
      IoHwAb_LcdSendStringXY(1, 2, (uint8*) puc_Index[LCDDISPLAY_RPM_DIGITS - 3]);
      IoHwAb_LcdSendStringXY(1, 3, (uint8*) puc_Index[LCDDISPLAY_RPM_DIGITS - 4]);
   }
   else if ((uc_RpmAux >= 100) && (uc_RpmAux <= 999))
   {
      IoHwAb_LcdSendStringXY(1, 0, (uint8*) UserLcd_pc_CustomMessages[17]);
      IoHwAb_LcdSendStringXY(1, 1, (uint8*) puc_Index[LCDDISPLAY_RPM_DIGITS - 2]);
      IoHwAb_LcdSendStringXY(1, 2, (uint8*) puc_Index[LCDDISPLAY_RPM_DIGITS - 3]);
      IoHwAb_LcdSendStringXY(1, 3, (uint8*) puc_Index[LCDDISPLAY_RPM_DIGITS - 4]);
   }
   else if ((uc_RpmAux >= 1000) && (uc_RpmAux <= 9999))
   {
      IoHwAb_LcdSendStringXY(1, 0, (uint8*) puc_Index[LCDDISPLAY_RPM_DIGITS - 1]);
      IoHwAb_LcdSendStringXY(1, 1, (uint8*) puc_Index[LCDDISPLAY_RPM_DIGITS - 2]);
      IoHwAb_LcdSendStringXY(1, 2, (uint8*) puc_Index[LCDDISPLAY_RPM_DIGITS - 3]);
      IoHwAb_LcdSendStringXY(1, 3, (uint8*) puc_Index[LCDDISPLAY_RPM_DIGITS - 4]);
   }

}

/*
 *  \brief
 *  \param
 *  \return
 */
void LcdDisplay_DisplayDuty(Rte_SpeedType LcdDisplay_t_DutyValue)
{

   char *puc_Index[LCDDISPLAY_DUTY_DIGITS];
   uint8 uc_Index[LCDDISPLAY_DUTY_DIGITS];
   uint16 uc_RpmAux;
   uc_RpmAux = LcdDisplay_t_DutyValue;
   for (uint8 uc_I = 0; uc_I <= (LCDDISPLAY_DUTY_DIGITS - 1); uc_I++)
   {
      uc_Index[uc_I] = LcdDisplay_t_DutyValue % 10;
      LcdDisplay_t_DutyValue = LcdDisplay_t_DutyValue / 10;
      switch (uc_Index[uc_I])
      {
         case 0:
         puc_Index[uc_I] = "0";
            break;
         case 1:
         puc_Index[uc_I] = "1";
            break;
         case 2:
         puc_Index[uc_I] = "2";
            break;
         case 3:
         puc_Index[uc_I] = "3";
            break;
         case 4:
         puc_Index[uc_I] = "4";
            break;
         case 5:
         puc_Index[uc_I] = "5";
            break;
         case 6:
         puc_Index[uc_I] = "6";
            break;
         case 7:
         puc_Index[uc_I] = "7";
            break;
         case 8:
         puc_Index[uc_I] = "8";
            break;
         case 9:
         puc_Index[uc_I] = "9";
            break;
         default:
         puc_Index[uc_I] = "";
            break;
      }
   }
   if (uc_RpmAux < 10)
   {

      IoHwAb_LcdSendStringXY(0, 8, (uint8*) UserLcd_pc_CustomMessages[17]);
      IoHwAb_LcdSendStringXY(0, 9, (uint8*) UserLcd_pc_CustomMessages[17]);
      IoHwAb_LcdSendStringXY(0, 10, (uint8*) puc_Index[LCDDISPLAY_DUTY_DIGITS - 3]);
   }
   else if ((uc_RpmAux >= 10) && (uc_RpmAux <= 99))
   {

      IoHwAb_LcdSendStringXY(0, 8, (uint8*) UserLcd_pc_CustomMessages[17]);
      IoHwAb_LcdSendStringXY(0, 9, (uint8*) puc_Index[LCDDISPLAY_DUTY_DIGITS - 2]);
      IoHwAb_LcdSendStringXY(0, 10, (uint8*) puc_Index[LCDDISPLAY_DUTY_DIGITS - 3]);
   }
   else
   {

      IoHwAb_LcdSendStringXY(0, 8, (uint8*) puc_Index[LCDDISPLAY_DUTY_DIGITS - 1]);
      IoHwAb_LcdSendStringXY(0, 9, (uint8*) puc_Index[LCDDISPLAY_DUTY_DIGITS - 2]);
      IoHwAb_LcdSendStringXY(0, 10, (uint8*) puc_Index[LCDDISPLAY_DUTY_DIGITS - 3]);
   }

}

/*-------------------------------------------------------------------------------------------------------------------*/
/*                                         Implementation Of Global Functions                                        */
/*-------------------------------------------------------------------------------------------------------------------*/

/*
 *  \brief
 *  \param
 *  \return
 */
void LcdDisplay_Init(void)
{
   LcdDisplay_t_BatteryPercentage = 0;
   LcdDisplay_t_BatterySoc = 0;
   LcdDisplay_t_BatteryVoltage = 0;
   LcdDisplay_t_RpmValue = 0;
   LcdDisplay_t_DutySpeed = 0;
   LcdDisplay_puc_BatPercentage = &LcdDisplay_t_BatteryPercentage;
   IoHwAb_LcdClear();
   IoHwAb_LcdSendStringXY(0, 1, (uint8*) UserLcd_pc_InitMessage1);
   IoHwAb_LcdSendStringXY(1, 3, (uint8*) UserLcd_pc_InitMessage2);
   IoHwAb_LcdCustomCharacter();
   IoHwAb_LcdPutCustomCharacter(1, 15, LCDDISPLAY_SMILEY_FACE);
}

/*
 *  \brief
 *  \param
 *  \return
 */
void LcdDisplay_Main(void)
{
   LcdDisplay_RteUpdate();
   static Rte_LcdInterfaceType t_Interface;
   Rte_DirectionType t_Direction;
   Rte_BatteryPercentageType t_BatteryCustomIndicator;
   t_BatteryCustomIndicator = LcdDisplay_DisplayIndicator(LcdDisplay_t_BatterySoc);
   if (Rte_LcdInterface_In_LcdStruct_UpdateFlag == TRUE)
   {

      if (uc_ClearFlag)
         IoHwAb_LcdClear();

      Rte_Read_In_LcdStruct(&t_Interface);
      Rte_Read_In_LcdDirectionIndicator(&t_Direction);

      IoHwAb_LcdDisableCursor();
      if ((t_Interface.t_Menu == RTE_MOTOR_MENU) && (t_Interface.t_Submenu == RTE_NONE))
      {
         IoHwAb_LcdClear();
         IoHwAb_LcdSendStringXY(0, 0, (uint8*) UserLcd_pc_Interfaces[0]);
         IoHwAb_LcdPutCustomCharacter(0, 15, LCDDISPLAY_ARROW_SUBMENU);
         uc_ClearFlag = 1;
      }
      else if ((t_Interface.t_Menu == RTE_BATTERY_MENU) && (t_Interface.t_Submenu == RTE_NONE))
      {

         IoHwAb_LcdSendStringXY(0, 0, (uint8*) UserLcd_pc_Interfaces[1]);
         LcdDisplay_DisplayVoltage(LcdDisplay_t_BatteryVoltage);
         LcdDisplay_DisplayPercentage(LcdDisplay_t_BatteryPercentage);
         IoHwAb_LcdPutCustomCharacter(0, 15, t_BatteryCustomIndicator);
         if ( LCDDISPLAY_BATTERY_DISCHARGED_CHARGED == t_BatteryCustomIndicator)
         {
            IoHwAb_LcdPutCustomCharacter(1, 13, LCDDISPLAY_DOWN_ARROW_RAM_INDEX);
         }
         else
         {
            IoHwAb_LcdSendStringXY(1, 13, (uint8*) UserLcd_pc_CustomMessages[17]);
         }
         IoHwAb_LcdSendStringXY(1, 6, (uint8*) UserLcd_pc_CustomMessages[17]);
         IoHwAb_LcdSendStringXY(1, 7, (uint8*) UserLcd_pc_CustomMessages[17]);
         IoHwAb_LcdSendStringXY(1, 8, (uint8*) UserLcd_pc_CustomMessages[17]);
         IoHwAb_LcdSendStringXY(1, 15, (uint8*) UserLcd_pc_CustomMessages[17]);

         uc_ClearFlag = 0;
      }
      else if ((t_Interface.t_Menu == RTE_CURRENT_MENU) && (t_Interface.t_Submenu == RTE_NONE))
      {

         IoHwAb_LcdSendStringXY(0, 0, (uint8*) UserLcd_pc_Interfaces[2]);
         LcdDisplay_DisplayCurrent(LcdDisplay_t_CurrentValue);
         IoHwAb_LcdSendStringXY(0, 15, (uint8*) UserLcd_pc_CustomMessages[17]);
         IoHwAb_LcdSendStringXY(1, 10, (uint8*) UserLcd_pc_CustomMessages[17]);
         IoHwAb_LcdSendStringXY(1, 11, (uint8*) UserLcd_pc_CustomMessages[17]);
         IoHwAb_LcdSendStringXY(1, 12, (uint8*) UserLcd_pc_CustomMessages[17]);
         IoHwAb_LcdSendStringXY(1, 13, (uint8*) UserLcd_pc_CustomMessages[17]);
         uc_ClearFlag = 0;
      }
      else if ((t_Interface.t_Menu == RTE_UART_MENU) && (t_Interface.t_Submenu == RTE_NONE))
      {
         IoHwAb_LcdClear();
         IoHwAb_LcdSendStringXY(0, 0, (uint8*) UserLcd_pc_Interfaces[3]);
         IoHwAb_LcdPutCustomCharacter(0, 15, LCDDISPLAY_ARROW_SUBMENU);
         uc_ClearFlag = 1;
      }
      else if ((t_Interface.t_Menu == RTE_MOTOR_MENU) && (t_Interface.t_Submenu == RTE_DIRECTION)
         && (t_Direction == RTE_FORWARD))
      {

         IoHwAb_LcdSendStringXY(0, 0, (uint8*) UserLcd_pc_SubInterfaces[0]);
         IoHwAb_LcdSendStringXY(0, 11, (uint8*) UserLcd_pc_SubInterfaces2[0]);
         IoHwAb_LcdSendStringXY(0, 14, (uint8*) UserLcd_pc_SubInterfaces2[1]);
         IoHwAb_LcdSendStringXY(0, 11, 0x00);
         IoHwAb_LcdCursor();
         uc_ClearFlag = 0;

      }
      else if ((t_Interface.t_Menu == RTE_MOTOR_MENU) && (t_Interface.t_Submenu == RTE_DIRECTION)
         && (t_Direction == RTE_BACKWARD))
      {
         IoHwAb_LcdSendStringXY(0, 0, (uint8*) UserLcd_pc_SubInterfaces[0]);
         IoHwAb_LcdSendStringXY(0, 11, (uint8*) UserLcd_pc_SubInterfaces2[0]);
         IoHwAb_LcdSendStringXY(0, 14, (uint8*) UserLcd_pc_SubInterfaces2[1]);
         IoHwAb_LcdSendStringXY(0, 14, 0x00);
         IoHwAb_LcdCursor();
         uc_ClearFlag = 0;

      }
      else if ((t_Interface.t_Menu == RTE_MOTOR_MENU) && (t_Interface.t_Submenu == RTE_START))
      {
         IoHwAb_LcdClear();
         IoHwAb_LcdSendStringXY(0, 0, (uint8*) UserLcd_pc_CustomMessages[1]);
         IoHwAb_LcdSendStringXY(1, 0, (uint8*) UserLcd_pc_CustomMessages[2]);
         if (t_Direction == RTE_BACKWARD)
         {
            IoHwAb_LcdSendStringXY(1, 5, (uint8*) UserLcd_pc_CustomMessages[3]);
         }
         else
         {
            IoHwAb_LcdSendStringXY(1, 5, (uint8*) UserLcd_pc_CustomMessages[4]);
         }
         uc_ClearFlag = 1;
      }
      else if ((t_Interface.t_Menu == RTE_MOTOR_MENU) && (t_Interface.t_Submenu == RTE_SPEED))
      {

         IoHwAb_LcdSendStringXY(0, 0, (uint8*) UserLcd_pc_CustomMessages[5]);
         IoHwAb_LcdSendStringXY(0, 12, (uint8*) UserLcd_pc_CustomMessages[18]);
         IoHwAb_LcdSendStringXY(1, 5, (uint8*) UserLcd_pc_CustomMessages[6]);
         IoHwAb_LcdPutCustomCharacter(0, 15, LCDDISPLAY_UP_ARROW_RAM_INDEX);
         IoHwAb_LcdPutCustomCharacter(1, 15, LCDDISPLAY_DOWN_ARROW_RAM_INDEX);
         LcdDisplay_DisplayDuty(LcdDisplay_t_DutySpeed);
         LcdDisplay_DisplayRpm(LcdDisplay_t_RpmValue);
         uc_ClearFlag = 0;
      }
      else if (((t_Interface.t_Menu == RTE_UART_MENU) && (t_Interface.t_Submenu == RTE_BAUDRATE)))
      {
         IoHwAb_LcdClear();
         IoHwAb_LcdSendStringXY(0, 0, (uint8*) UserLcd_pc_CustomMessages[7]);
         IoHwAb_LcdSendStringXY(0, 11, (uint8*) UserLcd_pc_CustomMessages[8]);
         IoHwAb_LcdSendStringXY(1, 0, (uint8*) UserLcd_pc_CustomMessages[9]);
         IoHwAb_LcdSendStringXY(1, 11, (uint8*) UserLcd_pc_CustomMessages[10]);
         uc_ClearFlag = 1;
      }
      else if (((t_Interface.t_Menu == RTE_UART_MENU) && (t_Interface.t_Submenu == RTE_STOPBITS)))
      {
         IoHwAb_LcdClear();
         IoHwAb_LcdSendStringXY(0, 0, (uint8*) UserLcd_pc_CustomMessages[11]);
         IoHwAb_LcdSendStringXY(0, 13, (uint8*) UserLcd_pc_CustomMessages[12]);
         IoHwAb_LcdSendStringXY(1, 0, (uint8*) UserLcd_pc_CustomMessages[13]);
         IoHwAb_LcdSendStringXY(1, 13, (uint8*) UserLcd_pc_CustomMessages[14]);
         uc_ClearFlag = 1;
      }
      else if (((t_Interface.t_Menu == RTE_UART_MENU) && (t_Interface.t_Submenu == RTE_ENABLE)))
      {
         IoHwAb_LcdPutCustomCharacter(0, 9, LCDDISPLAY_ARROW_INDICATOR);
         IoHwAb_LcdSendStringXY(1, 9, (uint8*) UserLcd_pc_CustomMessages[17]);

         IoHwAb_LcdSendStringXY(0, 0, (uint8*) UserLcd_pc_CustomMessages[15]);
         IoHwAb_LcdSendStringXY(1, 0, (uint8*) UserLcd_pc_CustomMessages[16]);

         uc_ClearFlag = 0;
      }
      else if (((t_Interface.t_Menu == RTE_UART_MENU) && (t_Interface.t_Submenu == RTE_DISABLE)))
      {
         IoHwAb_LcdSendStringXY(0, 9, (uint8*) UserLcd_pc_CustomMessages[17]);
         IoHwAb_LcdPutCustomCharacter(1, 9, LCDDISPLAY_ARROW_INDICATOR);

         IoHwAb_LcdSendStringXY(0, 0, (uint8*) UserLcd_pc_CustomMessages[15]);
         IoHwAb_LcdSendStringXY(1, 0, (uint8*) UserLcd_pc_CustomMessages[16]);

         uc_ClearFlag = 0;
      }
   }
}
