/*-------------------------------------------------------------------------------------------------------------------*/
/**
 *    \file       UserLcd.c
 *    \author     Baciu Vlad-Eusebiu
 *    \brief      Empty template to be used for all .c files. This file provides an example for the case in which a
 *                detailed description is not needed.
 */
/*-------------------------------------------------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------------------------------------------------*/
/*                                                     Inclusions                                                    */
/*-------------------------------------------------------------------------------------------------------------------*/
#include <UserControl.h>

/*-------------------------------------------------------------------------------------------------------------------*/
/*                                             Definition Of Local Macros                                            */
/*-------------------------------------------------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------------------------------------------------*/
/*                                           Definition Of Local Data Types                                          */
/*-------------------------------------------------------------------------------------------------------------------*/
static uint32 UserControl_CountStart;
/*-------------------------------------------------------------------------------------------------------------------*/
/*                                           Declaration Of Local Variables                                          */
/*-------------------------------------------------------------------------------------------------------------------*/

Rte_PotPosType t_YAxisRaw;

Rte_PotPosType t_XAxisRaw;

Rte_SpeedType UserControl_t_DutySpeed;
/*-------------------------------------------------------------------------------------------------------------------*/
/*                                          Declaration Of Global Variables                                          */
/*-------------------------------------------------------------------------------------------------------------------*/
Rte_UartEnableType UserControl_gt_UartIndicator;

Rte_MotorFlagType UserControl_gt_StartFlag;

Rte_LcdInterfaceType USerControl_gt_GlobalInterface;

Rte_DirectionType USerControl_gt_Direction;

Rte_SpeedType USerControl_gt_Speed;

Rte_SpeedType USerControl_gt_PercentageDuty;
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
 * \brief      Init function for LCD. Prints a default message to the LCD.
 * \param      -
 * \return     -
 */
void UserControl_Init(void)
{

   USerControl_gt_GlobalInterface.t_Menu = RTE_INIT;
   USerControl_gt_GlobalInterface.t_Submenu = RTE_NONE;
   USerControl_gt_Direction = RTE_UNSET;
   USerControl_gt_Speed = 0U;
   UserControl_CountStart = 0U;
   UserControl_gt_UartIndicator = 0U;
   UserControl_gt_StartFlag = 0U;
}

/**
 * \brief      Main LCD function. Handles menu navigation and user interface.
 * \param      -
 * \return     -
 */
void UserControl_Main(void)
{
   uint8 uc_ChangeFlag = 0;
   Rte_BtnPressType t_BtnPress;
   Rte_JoystickType t_YAxis;
   Rte_JoystickType t_XAxis;

   Rte_Read_BtnIn_BtnJoystick(&t_BtnPress);
   Rte_Read_PotYIn_PotYLcd(&t_YAxis);
   Rte_Read_PotXIn_PotXLcd(&t_XAxis);
   Rte_Read_PotYRaw_PotYAxis(&t_YAxisRaw);
   Rte_Read_PotXRaw_PotXAxis(&t_XAxisRaw);
   if ((USerControl_gt_GlobalInterface.t_Menu != RTE_CURRENT_MENU)
      && (USerControl_gt_GlobalInterface.t_Menu != RTE_BATTERY_MENU))
   {
      Delay_gv_Ms(150);
   }
   else
   {
      Delay_gv_Ms(40);
   }
   if (t_BtnPress == RTE_BTN_PRESSED && USerControl_gt_GlobalInterface.t_Menu == RTE_INIT)
   {
      UserControl_CountStart++;
      if (UserControl_CountStart >= 5)
      {
         USerControl_gt_GlobalInterface.t_Menu = RTE_MOTOR_MENU;
         UserControl_CountStart = 0;
         uc_ChangeFlag = 1;
      }
   }

   if ((USerControl_gt_GlobalInterface.t_Menu == RTE_MOTOR_MENU) && (t_XAxis == RTE_JOYSTICK_LEFT)
      && (USerControl_gt_GlobalInterface.t_Submenu == RTE_NONE))
   {
      USerControl_gt_GlobalInterface.t_Menu = (USerControl_gt_GlobalInterface.t_Menu + 1) % 5;
      uc_ChangeFlag = 1;
   }
   else if ((USerControl_gt_GlobalInterface.t_Menu == RTE_MOTOR_MENU) && (t_XAxis == RTE_JOYSTICK_RIGHT)
      && (USerControl_gt_GlobalInterface.t_Submenu == RTE_NONE))
   {
      USerControl_gt_GlobalInterface.t_Menu = 4;
      uc_ChangeFlag = 1;
   }
   else if ((USerControl_gt_GlobalInterface.t_Menu == RTE_BATTERY_MENU) && (t_XAxis == RTE_JOYSTICK_LEFT)
      && (USerControl_gt_GlobalInterface.t_Submenu == RTE_NONE))
   {
      USerControl_gt_GlobalInterface.t_Menu = (USerControl_gt_GlobalInterface.t_Menu + 1) % 5;
      uc_ChangeFlag = 1;
   }
   else if ((USerControl_gt_GlobalInterface.t_Menu == RTE_BATTERY_MENU) && (t_XAxis == RTE_JOYSTICK_RIGHT)
      && (USerControl_gt_GlobalInterface.t_Submenu == RTE_NONE))
   {
      USerControl_gt_GlobalInterface.t_Menu = USerControl_gt_GlobalInterface.t_Menu - 1;
      uc_ChangeFlag = 1;
   }
   else if ((USerControl_gt_GlobalInterface.t_Menu == RTE_CURRENT_MENU) && (t_XAxis == RTE_JOYSTICK_LEFT)
      && (USerControl_gt_GlobalInterface.t_Submenu == RTE_NONE))
   {
      USerControl_gt_GlobalInterface.t_Menu = (USerControl_gt_GlobalInterface.t_Menu + 1) % 5;
      uc_ChangeFlag = 1;
   }
   else if ((USerControl_gt_GlobalInterface.t_Menu == RTE_CURRENT_MENU) && (t_XAxis == RTE_JOYSTICK_RIGHT)
      && (USerControl_gt_GlobalInterface.t_Submenu == RTE_NONE))
   {
      USerControl_gt_GlobalInterface.t_Menu = USerControl_gt_GlobalInterface.t_Menu - 1;
      uc_ChangeFlag = 1;
   }
   else if ((USerControl_gt_GlobalInterface.t_Menu == RTE_UART_MENU) && (t_XAxis == RTE_JOYSTICK_LEFT)
      && (USerControl_gt_GlobalInterface.t_Submenu == RTE_NONE))
   {
      USerControl_gt_GlobalInterface.t_Menu = ((USerControl_gt_GlobalInterface.t_Menu + 1) % 5) + 1;
      uc_ChangeFlag = 1;
   }
   else if ((USerControl_gt_GlobalInterface.t_Menu == RTE_UART_MENU) && (t_XAxis == RTE_JOYSTICK_RIGHT)
      && (USerControl_gt_GlobalInterface.t_Submenu == RTE_NONE))
   {
      USerControl_gt_GlobalInterface.t_Menu = USerControl_gt_GlobalInterface.t_Menu - 1;
      uc_ChangeFlag = 1;
   }
   else if ((USerControl_gt_GlobalInterface.t_Menu == RTE_MOTOR_MENU) && (t_YAxis == RTE_JOYSTICK_RIGHT)
      && (USerControl_gt_Direction == RTE_UNSET))
   {
      USerControl_gt_GlobalInterface.t_Submenu = USerControl_gt_GlobalInterface.t_Submenu + 1;
      USerControl_gt_Direction = RTE_FORWARD;
      uc_ChangeFlag = 1;
   }
   else if ((USerControl_gt_GlobalInterface.t_Submenu == RTE_DIRECTION) && (t_YAxis == RTE_JOYSTICK_RIGHT)
      && (USerControl_gt_Direction == RTE_FORWARD))
   {
      USerControl_gt_Direction = RTE_BACKWARD;
      uc_ChangeFlag = 1;
   }
   else if ((USerControl_gt_GlobalInterface.t_Submenu == RTE_DIRECTION) && (t_YAxis == RTE_JOYSTICK_LEFT)
      && (USerControl_gt_Direction == RTE_BACKWARD))
   {
      USerControl_gt_Direction = RTE_FORWARD;
      uc_ChangeFlag = 1;
   }
   else if ((USerControl_gt_GlobalInterface.t_Submenu == RTE_DIRECTION) && (t_YAxis == RTE_JOYSTICK_LEFT)
      && (USerControl_gt_Direction == RTE_BACKWARD))
   {
      USerControl_gt_Direction = RTE_BACKWARD;
   }
   else if ((USerControl_gt_GlobalInterface.t_Submenu == RTE_DIRECTION) && (t_BtnPress == RTE_BTN_PRESSED))
   {
      USerControl_gt_GlobalInterface.t_Submenu = USerControl_gt_GlobalInterface.t_Submenu + 1;
      uc_ChangeFlag = 1;
   }
   else if ((USerControl_gt_GlobalInterface.t_Submenu == RTE_DIRECTION) && (t_YAxis == RTE_JOYSTICK_LEFT)
      && (USerControl_gt_Direction == RTE_FORWARD))
   {
      USerControl_gt_Direction = RTE_UNSET;
      USerControl_gt_GlobalInterface.t_Submenu = RTE_NONE;
      uc_ChangeFlag = 1;
   }
   else if ((USerControl_gt_GlobalInterface.t_Submenu == RTE_START) && (t_YAxis == RTE_JOYSTICK_LEFT))
   {
      USerControl_gt_Direction = RTE_UNSET;
      USerControl_gt_GlobalInterface.t_Submenu = RTE_NONE;
      uc_ChangeFlag = 1;
   }
   else if ((USerControl_gt_GlobalInterface.t_Submenu == RTE_START) && (t_BtnPress == RTE_BTN_PRESSED))
   {
      UserControl_CountStart++;
      if (UserControl_CountStart >= 5)
      {
         UserControl_gt_StartFlag = 1;
         USerControl_gt_GlobalInterface.t_Submenu = USerControl_gt_GlobalInterface.t_Submenu + 1;
         uc_ChangeFlag = 1;
         UserControl_CountStart = 0;
      }
   }
   else if ((USerControl_gt_GlobalInterface.t_Submenu == RTE_SPEED) && (t_YAxis == RTE_JOYSTICK_LEFT))
   {
      USerControl_gt_GlobalInterface.t_Menu = RTE_BATTERY_MENU;
      USerControl_gt_GlobalInterface.t_Submenu = RTE_NONE;
      uc_ChangeFlag = 1;
   }
   else if ((USerControl_gt_GlobalInterface.t_Menu == RTE_MOTOR_MENU) && (t_YAxis == RTE_JOYSTICK_RIGHT)
      && (USerControl_gt_Direction != RTE_UNSET) && (USerControl_gt_GlobalInterface.t_Submenu != RTE_DIRECTION)
      && (USerControl_gt_GlobalInterface.t_Submenu != RTE_START))
   {
      USerControl_gt_GlobalInterface.t_Submenu = RTE_SPEED;
      uc_ChangeFlag = 1;
   }
   else if ((USerControl_gt_GlobalInterface.t_Submenu == RTE_SPEED) && (t_BtnPress == RTE_BTN_PRESSED))
   {
      UserControl_CountStart++;
      if (UserControl_CountStart >= 5)
      {
         UserControl_gt_StartFlag = 0U;
         USerControl_gt_GlobalInterface.t_Menu = RTE_MOTOR_MENU;
         USerControl_gt_GlobalInterface.t_Submenu = RTE_NONE;
         USerControl_gt_Direction = RTE_UNSET;
         uc_ChangeFlag = 1;
         UserControl_CountStart = 0;
      }
      else
      {
         /* wait */
      }
   }
   else if ((USerControl_gt_GlobalInterface.t_Menu == RTE_UART_MENU) && (t_YAxis == RTE_JOYSTICK_RIGHT)
      && (USerControl_gt_GlobalInterface.t_Submenu == RTE_NONE))
   {
      USerControl_gt_GlobalInterface.t_Submenu = RTE_BAUDRATE;
      uc_ChangeFlag = 1;
   }
   else if ((USerControl_gt_GlobalInterface.t_Submenu == RTE_BAUDRATE) && (t_XAxis == RTE_JOYSTICK_LEFT))
   {
      USerControl_gt_GlobalInterface.t_Submenu = RTE_STOPBITS;
      uc_ChangeFlag = 1;
   }
   else if ((USerControl_gt_GlobalInterface.t_Submenu == RTE_BAUDRATE) && (t_XAxis == RTE_JOYSTICK_RIGHT))
   {
      USerControl_gt_GlobalInterface.t_Submenu = RTE_BAUDRATE;

   }
   else if ((USerControl_gt_GlobalInterface.t_Submenu == RTE_STOPBITS) && (t_XAxis == RTE_JOYSTICK_LEFT) &&
      (UserControl_gt_UartIndicator == 1))
   {
      USerControl_gt_GlobalInterface.t_Submenu = RTE_ENABLE;
      UserControl_gt_UartIndicator = 1;
      uc_ChangeFlag = 1;
   }
   else if ((USerControl_gt_GlobalInterface.t_Submenu == RTE_STOPBITS) && (t_XAxis == RTE_JOYSTICK_LEFT) &&
      (UserControl_gt_UartIndicator == 0))
   {
      USerControl_gt_GlobalInterface.t_Submenu = RTE_DISABLE;
      UserControl_gt_UartIndicator = 0;
      uc_ChangeFlag = 1;
   }
   else if ((USerControl_gt_GlobalInterface.t_Submenu == RTE_STOPBITS) && (t_XAxis == RTE_JOYSTICK_RIGHT))
   {
      USerControl_gt_GlobalInterface.t_Submenu = RTE_BAUDRATE;
      uc_ChangeFlag = 1;
   }
   else if ((USerControl_gt_GlobalInterface.t_Submenu == RTE_ENABLE) && (t_XAxis == RTE_JOYSTICK_RIGHT))
   {
      USerControl_gt_GlobalInterface.t_Submenu = RTE_ENABLE;

   }
   else if ((USerControl_gt_GlobalInterface.t_Submenu == RTE_ENABLE) && (t_XAxis == RTE_JOYSTICK_LEFT))
   {
      USerControl_gt_GlobalInterface.t_Submenu = RTE_DISABLE;
      UserControl_gt_UartIndicator = 0;
      uc_ChangeFlag = 1;
   }
   else if ((USerControl_gt_GlobalInterface.t_Submenu == RTE_DISABLE) && (t_XAxis == RTE_JOYSTICK_RIGHT))
   {
      USerControl_gt_GlobalInterface.t_Submenu = RTE_ENABLE;
      UserControl_gt_UartIndicator = 1;
      uc_ChangeFlag = 1;
   }
   else if (((USerControl_gt_GlobalInterface.t_Submenu == RTE_ENABLE) ||
      (USerControl_gt_GlobalInterface.t_Submenu == RTE_DISABLE) ||
      (USerControl_gt_GlobalInterface.t_Submenu == RTE_BAUDRATE) ||
      (USerControl_gt_GlobalInterface.t_Submenu == RTE_STOPBITS)) && t_YAxis == RTE_JOYSTICK_LEFT)
   {
      USerControl_gt_GlobalInterface.t_Submenu = RTE_NONE;
      uc_ChangeFlag = 1;
   }
   else if (USerControl_gt_GlobalInterface.t_Menu == RTE_BATTERY_MENU)
   {
      USerControl_gt_GlobalInterface.t_Menu = RTE_BATTERY_MENU;
      uc_ChangeFlag = 1;
   }
   else if (USerControl_gt_GlobalInterface.t_Menu == RTE_CURRENT_MENU)
   {
      USerControl_gt_GlobalInterface.t_Menu = RTE_CURRENT_MENU;
      uc_ChangeFlag = 1;
   }
   else if ((USerControl_gt_GlobalInterface.t_Submenu == RTE_SPEED)
      && (t_XAxis == RTE_JOYSTICK_CENTER))
   {
      USerControl_gt_GlobalInterface.t_Submenu = RTE_SPEED;
      uc_ChangeFlag = 1;
   }
   else if ((USerControl_gt_GlobalInterface.t_Submenu == RTE_SPEED) &&
      (t_XAxis == RTE_JOYSTICK_RIGHT))
   {
      if (USerControl_gt_PercentageDuty < 100)
      {
         USerControl_gt_PercentageDuty = USerControl_gt_PercentageDuty + 5;
      }
      else
      {
         USerControl_gt_PercentageDuty = 100;
      }
      uc_ChangeFlag = 1;
   }
   else if ((USerControl_gt_GlobalInterface.t_Submenu == RTE_SPEED) &&
      (t_XAxis == RTE_JOYSTICK_LEFT))
   {
      if (USerControl_gt_PercentageDuty > 5)
      {
         USerControl_gt_PercentageDuty = USerControl_gt_PercentageDuty - 5;
      }
      else
      {
         USerControl_gt_PercentageDuty = 0;
      }
      uc_ChangeFlag = 1;
   }
   if(UserControl_gt_StartFlag == 0)
   {
      USerControl_gt_PercentageDuty = 0;
   }
   Rte_Write_Out_Percentage(&USerControl_gt_PercentageDuty);
   Rte_Write_Out_UartFlag(&UserControl_gt_UartIndicator);
  // Rte_Write_Out_LedRight(&UserControl_gt_UartIndicator);
   Rte_Write_Out_MotorFlag(&UserControl_gt_StartFlag);
   Rte_Write_Out_LedCenter(&UserControl_gt_StartFlag);
   //  Rte_Write_Out_Percentage(&UserControl_t_DutySpeed);
   if (uc_ChangeFlag == 1)
   {

      Rte_Write_Out_LcdStruct(&USerControl_gt_GlobalInterface);
      Rte_Write_Out_LcdDirectionIndicator(&USerControl_gt_Direction);

   }
}

