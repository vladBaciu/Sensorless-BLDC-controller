/*-------------------------------------------------------------------------------------------------------------------*/
/**
 *    \file       Joystick_Core.h
 *    \author     Baciu Vlad-Eusebiu
 *    \brief      Empty template to be used for all .h files. This file provides an example for the case in which a
 *                detailed description is not needed.
 */
/*-------------------------------------------------------------------------------------------------------------------*/

#ifndef JOYSTICK_CORE_H
#define JOYSTICK_CORE_H

/*-------------------------------------------------------------------------------------------------------------------*/
/*                                                     Inclusions                                                    */
/*-------------------------------------------------------------------------------------------------------------------*/
#include "../../../Joystick/Code/Config/Joystick_Cfg.h"
#include "Rte_Joystick.h"
/*-------------------------------------------------------------------------------------------------------------------*/
/*                                            Definition Of Global Macros                                            */
/*-------------------------------------------------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------------------------------------------------*/
/*                                          Definition Of Global Data Types                                          */
/*-------------------------------------------------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------------------------------------------------*/
/*                                             Export Of Global Variables                                            */
/*-------------------------------------------------------------------------------------------------------------------*/
extern IoHwAb_DigitalLevelType Joystick_gat_BtnInputValue;
extern Rte_BtnPressType Joystick_gat_BtnOutputValue;
extern IoHwAb_AnalogLevelType Joystick_gat_PotInputXValue;
extern IoHwAb_AnalogLevelType Joystick_gat_PotInputYValue;
extern Rte_PotPosType Joystick_gat_PotOutputXValue;
extern Rte_PotPosType Joystick_gat_PotOutputYValue;
extern Rte_JoystickType Joystick_gat_PotOutputXDirection;
extern Rte_JoystickType Joystick_gat_PotOutputYDirection;
/*-------------------------------------------------------------------------------------------------------------------*/
/*                                             Export Of Global Constants                                            */
/*-------------------------------------------------------------------------------------------------------------------*/
extern const IoHwAb_DigitalLevelType Joystick_gkat_BtnActiveValue;
/*-------------------------------------------------------------------------------------------------------------------*/
/*                                             Export Of Global Functions                                            */
/*-------------------------------------------------------------------------------------------------------------------*/
extern void Joystick_gv_RteInputUpdate(void);
extern void Joystick_gv_RteOutputUpdate(void);

/*-------------------------------------------------------------------------------------------------------------------*/
#endif /* JOYSTICK_CORE_H */
