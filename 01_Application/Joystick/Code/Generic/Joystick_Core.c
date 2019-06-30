/*-------------------------------------------------------------------------------------------------------------------*/
/**
 *    \file       Joystick_Core.c
 *    \author     Baciu Vlad-Eusebiu
 *    \brief      Empty template to be used for all .c files. This file provides an example for the case in which a
 *                detailed description is not needed.
 */
/*-------------------------------------------------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------------------------------------------------*/
/*                                                     Inclusions                                                    */
/*-------------------------------------------------------------------------------------------------------------------*/
#include "../../../Joystick/Code/Generic/Joystick_Core.h"
/*-------------------------------------------------------------------------------------------------------------------*/
/*                                             Definition Of Local Macros                                            */
/*-------------------------------------------------------------------------------------------------------------------*/
#define JOYSTICK_AXIS_HIGHER_TRESHOLD          (3000U)
#define JOYSTICK_AXIS_LOWER_TRESHOLD           (1000U)
/*-------------------------------------------------------------------------------------------------------------------*/
/*                                           Definition Of Local Data Types                                          */
/*-------------------------------------------------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------------------------------------------------*/
/*                                           Declaration Of Local Variables                                          */
/*-------------------------------------------------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------------------------------------------------*/
/*                                          Declaration Of Global Variables                                          */
/*-------------------------------------------------------------------------------------------------------------------*/
/** \brief  Defines the raw input values from the ADCs and button */
IoHwAb_DigitalLevelType Joystick_gat_BtnInputValue;
IoHwAb_AnalogLevelType Joystick_gat_PotInputXValue;
IoHwAb_AnalogLevelType Joystick_gat_PotInputYValue;

/** \brief  Defines the output values after processing the raw input values representing the positions. */
Rte_BtnPressType Joystick_gat_BtnOutputValue;
Rte_PotPosType Joystick_gat_PotOutputXValue;
Rte_PotPosType Joystick_gat_PotOutputYValue;
Rte_JoystickType Joystick_gat_PotOutputXDirection;
Rte_JoystickType Joystick_gat_PotOutputYDirection;
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
/*
 * \brief
 * \param
 * \return
 */
void Joystick_Init()
{
   Joystick_gat_BtnInputValue = STD_LOW;
   Joystick_gat_BtnOutputValue = RTE_BTN_NOT_PRESSED;

   Joystick_gat_PotInputXValue = 0U;
   Joystick_gat_PotInputYValue = 0U;
   Joystick_gat_PotOutputXValue = 0U;
   Joystick_gat_PotOutputYValue = 0U;
}

/*
 * \brief
 * \param
 * \return
 */
void Joystick_Main()
{

   Joystick_gv_RteInputUpdate();
   if (Joystick_gat_BtnInputValue == Joystick_gkat_BtnActiveValue)
   {
      Joystick_gat_BtnOutputValue = RTE_BTN_PRESSED;
   }
   else
   {
      Joystick_gat_BtnOutputValue = RTE_BTN_NOT_PRESSED;
   }
   Joystick_gat_PotOutputXValue = Joystick_gat_PotInputXValue;
   Joystick_gat_PotOutputYValue = Joystick_gat_PotInputYValue;

   if (Joystick_gat_PotInputXValue >= JOYSTICK_AXIS_HIGHER_TRESHOLD)
   {
      Joystick_gat_PotOutputXDirection = RTE_JOYSTICK_LEFT;
   }
   else if (Joystick_gat_PotInputXValue <= JOYSTICK_AXIS_LOWER_TRESHOLD)
   {
      Joystick_gat_PotOutputXDirection = RTE_JOYSTICK_RIGHT;
   }
   else
   {
      Joystick_gat_PotOutputXDirection = RTE_JOYSTICK_CENTER;
   }

   if (Joystick_gat_PotInputYValue >= JOYSTICK_AXIS_HIGHER_TRESHOLD)
   {
      Joystick_gat_PotOutputYDirection = RTE_JOYSTICK_LEFT;
   }
   else if (Joystick_gat_PotInputYValue <= JOYSTICK_AXIS_LOWER_TRESHOLD)
   {
      Joystick_gat_PotOutputYDirection = RTE_JOYSTICK_RIGHT;
   }
   else
   {
      Joystick_gat_PotOutputYDirection = RTE_JOYSTICK_CENTER;
   }

   Joystick_gv_RteOutputUpdate();
}
