/*-------------------------------------------------------------------------------------------------------------------*/
/**
 *    \file       Rte_Type.h
 *    \author     RTE Generator
 *    \brief      Generated file - shall not be manually edited. 
 *                Exports only the software component runnables (global functions), usually only one initialization
 *                and one cyclic runnable. This header must exist for every software component and its name shall be
 *                the short name of the component that is used as a prefix for all the global functions and variables
 *                inside the module.
 */
/*-------------------------------------------------------------------------------------------------------------------*/

#ifndef RTE_TYPE_H
#define RTE_TYPE_H

/*-------------------------------------------------------------------------------------------------------------------*/
/*                                                     Inclusions                                                    */
/*-------------------------------------------------------------------------------------------------------------------*/
#include "Std_Types.h"
/*-------------------------------------------------------------------------------------------------------------------*/
/*                                            Definition Of Global Macros                                            */
/*-------------------------------------------------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------------------------------------------------*/
/*                                          Definition Of Global Data Types                                          */
/*-------------------------------------------------------------------------------------------------------------------*/

typedef uint32 Rte_PotPosType;
typedef uint16 Rte_SpeedType;
typedef uint8 Rte_UartEnableType;
typedef uint8 Rte_BatteryPercentageType;
typedef uint8 Rte_BatteryStateOfChargeType;
typedef uint16 Rte_BatteryVoltageType;
typedef uint16 Rte_CurrentAmpType;
typedef uint8 Rte_MotorFlagType;

typedef enum
{
   RTE_LED_OFF,
   RTE_LED_ON,
} Rte_LedEnableType;

typedef enum
{
   RTE_BTN_PRESSED,
   RTE_BTN_NOT_PRESSED,
} Rte_BtnPressType;

typedef enum
{
   RTE_JOYSTICK_LEFT,
   RTE_JOYSTICK_CENTER,
   RTE_JOYSTICK_RIGHT,
} Rte_JoystickType;

typedef enum
{
   RTE_NONE,
   RTE_DIRECTION,
   RTE_START,
   RTE_SPEED,
   RTE_BAUDRATE,
   RTE_PARITY,
   RTE_STOPBITS,
   RTE_DATABITS,
   RTE_ENABLE,
   RTE_DISABLE,
} Rte_LcdSubmenuType;

typedef enum
{
   RTE_INIT,
   RTE_MOTOR_MENU,
   RTE_BATTERY_MENU,
   RTE_CURRENT_MENU,
   RTE_UART_MENU,
} Rte_LcdMenuType;

typedef enum
{
   RTE_FORWARD,
   RTE_BACKWARD,
   RTE_UNSET,
} Rte_DirectionType;

typedef struct
{
   Rte_LcdMenuType t_Menu;
   Rte_LcdSubmenuType t_Submenu;
} Rte_LcdInterfaceType;


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
#endif /* RTE_TYPE_H */