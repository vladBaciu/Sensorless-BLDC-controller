/*-------------------------------------------------------------------------------------------------------------------*/
/**
 *    \file       MotorControl_PBcfg.c
 *    \author     Baciu Vlad-Eusebiu
 *    \brief      Empty template to be used for all .c files. This file provides an example for the case in which a
 *                detailed description is not needed.
 */
/*-------------------------------------------------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------------------------------------------------*/
/*                                                     Inclusions                                                    */
/*-------------------------------------------------------------------------------------------------------------------*/
#include "MotorControl.h"
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

/*-------------------------------------------------------------------------------------------------------------------*/
/*                                           Declaration Of Local Constants                                          */
/*-------------------------------------------------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------------------------------------------------*/
/*                                          Declaration Of Global Constants                                          */
/*-------------------------------------------------------------------------------------------------------------------*/
static const MotorControl_GroupCfgType MotorControl_gkt_AlignSteps[MOTORCONTROL_NUMBER_OF_STEPS] =
{
   { 0x700, MOTORCONTROL_MS_PERIOD },
   { 0x800, MOTORCONTROL_MS_PERIOD },
   { 0x900, MOTORCONTROL_MS_PERIOD },
   { 0x1000, MOTORCONTROL_MS_PERIOD },
   { 0x1200, MOTORCONTROL_MS_PERIOD },
   { 0x1300, MOTORCONTROL_MS_PERIOD },
   { 0x1464, MOTORCONTROL_MS_PERIOD },
   { 0x1516, MOTORCONTROL_MS_PERIOD },
   { 0x1668, MOTORCONTROL_MS_PERIOD },
   { 0x1720, MOTORCONTROL_MS_PERIOD },
   { 0x1872, MOTORCONTROL_MS_PERIOD },
   { 0x1924, MOTORCONTROL_MS_PERIOD },
   { 0x2076, MOTORCONTROL_MS_PERIOD },
   { 0x2228, MOTORCONTROL_MS_PERIOD },
   { 0x2380, MOTORCONTROL_MS_PERIOD },
   { 0x2432, MOTORCONTROL_MS_PERIOD },
   { 0x2684, MOTORCONTROL_MS_PERIOD },
   { 0x2836, MOTORCONTROL_MS_PERIOD },
   { 0x3088, MOTORCONTROL_MS_PERIOD },
   { 0x3140, MOTORCONTROL_MS_PERIOD },
   { 0x3392, MOTORCONTROL_MS_PERIOD },
   { 0x3744, MOTORCONTROL_MS_PERIOD },
   { 0x3996, MOTORCONTROL_MS_PERIOD },
   { 0x4048, MOTORCONTROL_MS_PERIOD },
   { MOTOR_LAST_ALIGN_PWM_VALUE, MOTORCONTROL_MS_PERIOD },

};

static const MotorControl_GroupCfgType MotorControl_gkt_RampUpSteps[MOTORCONTROL_RAMPUP_STEPS] =
{

{ (MOTOR_STARTUP_PWM_VALUE + 0x200), (45 * MOTORCONTROL_MS_CLK) },
   { (MOTOR_STARTUP_PWM_VALUE + 0x200), (45 * MOTORCONTROL_MS_CLK) },
   { (MOTOR_STARTUP_PWM_VALUE + 0x200), (45 * MOTORCONTROL_MS_CLK) },
   { (MOTOR_STARTUP_PWM_VALUE + 0x200), (45 * MOTORCONTROL_MS_CLK) },
   { (MOTOR_STARTUP_PWM_VALUE + 0x200), (45 * MOTORCONTROL_MS_CLK) },
   { (MOTOR_STARTUP_PWM_VALUE + 0x200), (45 * MOTORCONTROL_MS_CLK) },
   { (MOTOR_STARTUP_PWM_VALUE + 0x200), (45 * MOTORCONTROL_MS_CLK) },
   { (MOTOR_STARTUP_PWM_VALUE + 0x200), (45 * MOTORCONTROL_MS_CLK) },
   { (MOTOR_STARTUP_PWM_VALUE + 0x200), (45 * MOTORCONTROL_MS_CLK) },
   { (MOTOR_STARTUP_PWM_VALUE + 0x200), (45 * MOTORCONTROL_MS_CLK) },

   { (MOTOR_STARTUP_PWM_VALUE + 0x300), (45 * MOTORCONTROL_MS_CLK) },
   { (MOTOR_STARTUP_PWM_VALUE + 0x300), (45 * MOTORCONTROL_MS_CLK) },
   { (MOTOR_STARTUP_PWM_VALUE + 0x300), (45 * MOTORCONTROL_MS_CLK) },
   { (MOTOR_STARTUP_PWM_VALUE + 0x300), (45 * MOTORCONTROL_MS_CLK) },
   { (MOTOR_STARTUP_PWM_VALUE + 0x300), (45 * MOTORCONTROL_MS_CLK) },
   { (MOTOR_STARTUP_PWM_VALUE + 0x300), (45 * MOTORCONTROL_MS_CLK) },
   { (MOTOR_STARTUP_PWM_VALUE + 0x300), (45 * MOTORCONTROL_MS_CLK) },
   { (MOTOR_STARTUP_PWM_VALUE + 0x300), (45 * MOTORCONTROL_MS_CLK) },
   { (MOTOR_STARTUP_PWM_VALUE + 0x300), (45 * MOTORCONTROL_MS_CLK) },

   { (MOTOR_STARTUP_PWM_VALUE + 0x400), (40 * MOTORCONTROL_MS_CLK) },
   { (MOTOR_STARTUP_PWM_VALUE + 0x400), (40 * MOTORCONTROL_MS_CLK) },
   { (MOTOR_STARTUP_PWM_VALUE + 0x400), (40 * MOTORCONTROL_MS_CLK) },
   { (MOTOR_STARTUP_PWM_VALUE + 0x400), (40 * MOTORCONTROL_MS_CLK) },
   { (MOTOR_STARTUP_PWM_VALUE + 0x400), (40 * MOTORCONTROL_MS_CLK) },
   { (MOTOR_STARTUP_PWM_VALUE + 0x400), (40 * MOTORCONTROL_MS_CLK) },
   { (MOTOR_STARTUP_PWM_VALUE + 0x400), (40 * MOTORCONTROL_MS_CLK) },
   { (MOTOR_STARTUP_PWM_VALUE + 0x400), (40 * MOTORCONTROL_MS_CLK) },

   { (MOTOR_STARTUP_PWM_VALUE + 0x500), (35 * MOTORCONTROL_MS_CLK) },
   { (MOTOR_STARTUP_PWM_VALUE + 0x500), (35 * MOTORCONTROL_MS_CLK) },
   { (MOTOR_STARTUP_PWM_VALUE + 0x500), (35 * MOTORCONTROL_MS_CLK) },
   { (MOTOR_STARTUP_PWM_VALUE + 0x500), (35 * MOTORCONTROL_MS_CLK) },
   { (MOTOR_STARTUP_PWM_VALUE + 0x500), (35 * MOTORCONTROL_MS_CLK) },
   { (MOTOR_STARTUP_PWM_VALUE + 0x500), (35 * MOTORCONTROL_MS_CLK) },
   { (MOTOR_STARTUP_PWM_VALUE + 0x500), (35 * MOTORCONTROL_MS_CLK) },
   { (MOTOR_STARTUP_PWM_VALUE + 0x500), (35 * MOTORCONTROL_MS_CLK) },

   { (MOTOR_STARTUP_PWM_VALUE + 0x600), (30 * MOTORCONTROL_MS_CLK) },
   { (MOTOR_STARTUP_PWM_VALUE + 0x600), (30 * MOTORCONTROL_MS_CLK) },
   { (MOTOR_STARTUP_PWM_VALUE + 0x600), (30 * MOTORCONTROL_MS_CLK) },
   { (MOTOR_STARTUP_PWM_VALUE + 0x600), (30 * MOTORCONTROL_MS_CLK) },
   { (MOTOR_STARTUP_PWM_VALUE + 0x600), (30 * MOTORCONTROL_MS_CLK) },
   { (MOTOR_STARTUP_PWM_VALUE + 0x600), (30 * MOTORCONTROL_MS_CLK) },
   { (MOTOR_STARTUP_PWM_VALUE + 0x600), (30 * MOTORCONTROL_MS_CLK) },
   { (MOTOR_STARTUP_PWM_VALUE + 0x600), (30 * MOTORCONTROL_MS_CLK) },

   { (MOTOR_STARTUP_PWM_VALUE + 0x700), (30 * MOTORCONTROL_MS_CLK) },
   { (MOTOR_STARTUP_PWM_VALUE + 0x700), (30 * MOTORCONTROL_MS_CLK) },
   { (MOTOR_STARTUP_PWM_VALUE + 0x700), (30 * MOTORCONTROL_MS_CLK) },
   { (MOTOR_STARTUP_PWM_VALUE + 0x700), (30 * MOTORCONTROL_MS_CLK) },
   { (MOTOR_STARTUP_PWM_VALUE + 0x700), (30 * MOTORCONTROL_MS_CLK) },
   { (MOTOR_STARTUP_PWM_VALUE + 0x700), (30 * MOTORCONTROL_MS_CLK) },
   { (MOTOR_STARTUP_PWM_VALUE + 0x700), (30 * MOTORCONTROL_MS_CLK) },
   { (MOTOR_STARTUP_PWM_VALUE + 0x700), (30 * MOTORCONTROL_MS_CLK) },
   { (MOTOR_STARTUP_PWM_VALUE + 0x700), (30 * MOTORCONTROL_MS_CLK) },

   { (MOTOR_STARTUP_PWM_VALUE + 0x800), (27 * MOTORCONTROL_MS_CLK) },
   { (MOTOR_STARTUP_PWM_VALUE + 0x800), (27 * MOTORCONTROL_MS_CLK) },
   { (MOTOR_STARTUP_PWM_VALUE + 0x800), (27 * MOTORCONTROL_MS_CLK) },
   { (MOTOR_STARTUP_PWM_VALUE + 0x800), (27 * MOTORCONTROL_MS_CLK) },
   { (MOTOR_STARTUP_PWM_VALUE + 0x800), (27 * MOTORCONTROL_MS_CLK) },
   { (MOTOR_STARTUP_PWM_VALUE + 0x800), (27 * MOTORCONTROL_MS_CLK) },
   { (MOTOR_STARTUP_PWM_VALUE + 0x800), (27 * MOTORCONTROL_MS_CLK) },
   { (MOTOR_STARTUP_PWM_VALUE + 0x800), (27 * MOTORCONTROL_MS_CLK) },
   { (MOTOR_STARTUP_PWM_VALUE + 0x800), (27 * MOTORCONTROL_MS_CLK) },

   { (MOTOR_STARTUP_PWM_VALUE + 0x900), (25 * MOTORCONTROL_MS_CLK) },
   { (MOTOR_STARTUP_PWM_VALUE + 0x900), (25 * MOTORCONTROL_MS_CLK) },
   { (MOTOR_STARTUP_PWM_VALUE + 0x900), (25 * MOTORCONTROL_MS_CLK) },
   { (MOTOR_STARTUP_PWM_VALUE + 0x900), (25 * MOTORCONTROL_MS_CLK) },
   { (MOTOR_STARTUP_PWM_VALUE + 0x900), (25 * MOTORCONTROL_MS_CLK) },
   { (MOTOR_STARTUP_PWM_VALUE + 0x900), (25 * MOTORCONTROL_MS_CLK) },
   { (MOTOR_STARTUP_PWM_VALUE + 0x900), (25 * MOTORCONTROL_MS_CLK) },
   { (MOTOR_STARTUP_PWM_VALUE + 0x900), (25 * MOTORCONTROL_MS_CLK) },

   { (MOTOR_STARTUP_PWM_VALUE + 0x1000), (23 * MOTORCONTROL_MS_CLK) },
   { (MOTOR_STARTUP_PWM_VALUE + 0x1000), (23 * MOTORCONTROL_MS_CLK) },
   { (MOTOR_STARTUP_PWM_VALUE + 0x1000), (23 * MOTORCONTROL_MS_CLK) },
   { (MOTOR_STARTUP_PWM_VALUE + 0x1000), (23 * MOTORCONTROL_MS_CLK) },
   { (MOTOR_STARTUP_PWM_VALUE + 0x1000), (23 * MOTORCONTROL_MS_CLK) },
   { (MOTOR_STARTUP_PWM_VALUE + 0x1000), (23 * MOTORCONTROL_MS_CLK) },
   { (MOTOR_STARTUP_PWM_VALUE + 0x1000), (23 * MOTORCONTROL_MS_CLK) },

   { (MOTOR_STARTUP_PWM_VALUE + 0x1200), (20 * MOTORCONTROL_MS_CLK) },
   { (MOTOR_STARTUP_PWM_VALUE + 0x1200), (20 * MOTORCONTROL_MS_CLK) },
   { (MOTOR_STARTUP_PWM_VALUE + 0x1200), (20 * MOTORCONTROL_MS_CLK) },
   { (MOTOR_STARTUP_PWM_VALUE + 0x1200), (20 * MOTORCONTROL_MS_CLK) },
   { (MOTOR_STARTUP_PWM_VALUE + 0x1200), (20 * MOTORCONTROL_MS_CLK) },
   { (MOTOR_STARTUP_PWM_VALUE + 0x1200), (20 * MOTORCONTROL_MS_CLK) },
   { (MOTOR_STARTUP_PWM_VALUE + 0x1200), (20 * MOTORCONTROL_MS_CLK) },

   { (MOTOR_STARTUP_PWM_VALUE + 0x1200), (18 * MOTORCONTROL_MS_CLK) },
   { (MOTOR_STARTUP_PWM_VALUE + 0x1200), (18 * MOTORCONTROL_MS_CLK) },
   { (MOTOR_STARTUP_PWM_VALUE + 0x1200), (18 * MOTORCONTROL_MS_CLK) },
   { (MOTOR_STARTUP_PWM_VALUE + 0x1200), (18 * MOTORCONTROL_MS_CLK) },
   { (MOTOR_STARTUP_PWM_VALUE + 0x1200), (18 * MOTORCONTROL_MS_CLK) },
   { (MOTOR_STARTUP_PWM_VALUE + 0x1200), (18 * MOTORCONTROL_MS_CLK) },
   { (MOTOR_STARTUP_PWM_VALUE + 0x1200), (18 * MOTORCONTROL_MS_CLK) },
   { (MOTOR_STARTUP_PWM_VALUE + 0x1200), (18 * MOTORCONTROL_MS_CLK) },
   { (MOTOR_STARTUP_PWM_VALUE + 0x1200), (18 * MOTORCONTROL_MS_CLK) },

   { (MOTOR_STARTUP_PWM_VALUE + 0x1200), (17 * MOTORCONTROL_MS_CLK) },
   { (MOTOR_STARTUP_PWM_VALUE + 0x1200), (17 * MOTORCONTROL_MS_CLK) },
   { (MOTOR_STARTUP_PWM_VALUE + 0x1200), (17 * MOTORCONTROL_MS_CLK) },
   { (MOTOR_STARTUP_PWM_VALUE + 0x1200), (17 * MOTORCONTROL_MS_CLK) },
   { (MOTOR_STARTUP_PWM_VALUE + 0x1200), (17 * MOTORCONTROL_MS_CLK) },
   { (MOTOR_STARTUP_PWM_VALUE + 0x1200), (17 * MOTORCONTROL_MS_CLK) },
   { (MOTOR_STARTUP_PWM_VALUE + 0x1200), (17 * MOTORCONTROL_MS_CLK) },
   { (MOTOR_STARTUP_PWM_VALUE + 0x1200), (17 * MOTORCONTROL_MS_CLK) },
   { (MOTOR_STARTUP_PWM_VALUE + 0x1200), (17 * MOTORCONTROL_MS_CLK) },

   { (MOTOR_STARTUP_PWM_VALUE + 0x1200), (16 * MOTORCONTROL_MS_CLK) },
   { (MOTOR_STARTUP_PWM_VALUE + 0x1200), (16 * MOTORCONTROL_MS_CLK) },
   { (MOTOR_STARTUP_PWM_VALUE + 0x1200), (16 * MOTORCONTROL_MS_CLK) },
   { (MOTOR_STARTUP_PWM_VALUE + 0x1200), (16 * MOTORCONTROL_MS_CLK) },
   { (MOTOR_STARTUP_PWM_VALUE + 0x1200), (16 * MOTORCONTROL_MS_CLK) },
   { (MOTOR_STARTUP_PWM_VALUE + 0x1200), (16 * MOTORCONTROL_MS_CLK) },
   { (MOTOR_STARTUP_PWM_VALUE + 0x1200), (16 * MOTORCONTROL_MS_CLK) },
   { (MOTOR_STARTUP_PWM_VALUE + 0x1200), (16 * MOTORCONTROL_MS_CLK) },
   { (MOTOR_STARTUP_PWM_VALUE + 0x1200), (16 * MOTORCONTROL_MS_CLK) },

   { (MOTOR_STARTUP_PWM_VALUE + 0x1200), (15 * MOTORCONTROL_MS_CLK) },
   { (MOTOR_STARTUP_PWM_VALUE + 0x1200), (15 * MOTORCONTROL_MS_CLK) },
   { (MOTOR_STARTUP_PWM_VALUE + 0x1200), (15 * MOTORCONTROL_MS_CLK) },
   { (MOTOR_STARTUP_PWM_VALUE + 0x1200), (15 * MOTORCONTROL_MS_CLK) },
   { (MOTOR_STARTUP_PWM_VALUE + 0x1200), (15 * MOTORCONTROL_MS_CLK) },
   { (MOTOR_STARTUP_PWM_VALUE + 0x1200), (15 * MOTORCONTROL_MS_CLK) },
   { (MOTOR_STARTUP_PWM_VALUE + 0x1200), (15 * MOTORCONTROL_MS_CLK) },
   { (MOTOR_STARTUP_PWM_VALUE + 0x1200), (15 * MOTORCONTROL_MS_CLK) },
   { (MOTOR_STARTUP_PWM_VALUE + 0x1200), (15 * MOTORCONTROL_MS_CLK) },

   { (MOTOR_STARTUP_PWM_VALUE + 0x1200), (14 * MOTORCONTROL_MS_CLK) },
   { (MOTOR_STARTUP_PWM_VALUE + 0x1200), (14 * MOTORCONTROL_MS_CLK) },
   { (MOTOR_STARTUP_PWM_VALUE + 0x1200), (14 * MOTORCONTROL_MS_CLK) },
   { (MOTOR_STARTUP_PWM_VALUE + 0x1200), (14 * MOTORCONTROL_MS_CLK) },
   { (MOTOR_STARTUP_PWM_VALUE + 0x1200), (14 * MOTORCONTROL_MS_CLK) },
   { (MOTOR_STARTUP_PWM_VALUE + 0x1200), (14 * MOTORCONTROL_MS_CLK) },
   { (MOTOR_STARTUP_PWM_VALUE + 0x1200), (14 * MOTORCONTROL_MS_CLK) },
   { (MOTOR_STARTUP_PWM_VALUE + 0x1200), (14 * MOTORCONTROL_MS_CLK) },
   { (MOTOR_STARTUP_PWM_VALUE + 0x1200), (14 * MOTORCONTROL_MS_CLK) },

   { (MOTOR_STARTUP_PWM_VALUE + 0x1200), (13 * MOTORCONTROL_MS_CLK) },
   { (MOTOR_STARTUP_PWM_VALUE + 0x1200), (13 * MOTORCONTROL_MS_CLK) },
   { (MOTOR_STARTUP_PWM_VALUE + 0x1200), (13 * MOTORCONTROL_MS_CLK) },
   { (MOTOR_STARTUP_PWM_VALUE + 0x1200), (13 * MOTORCONTROL_MS_CLK) },
   { (MOTOR_STARTUP_PWM_VALUE + 0x1200), (13 * MOTORCONTROL_MS_CLK) },
   { (MOTOR_STARTUP_PWM_VALUE + 0x1200), (13 * MOTORCONTROL_MS_CLK) },
   { (MOTOR_STARTUP_PWM_VALUE + 0x1200), (13 * MOTORCONTROL_MS_CLK) },
   { (MOTOR_STARTUP_PWM_VALUE + 0x1200), (13 * MOTORCONTROL_MS_CLK) },

   { (MOTOR_STARTUP_PWM_VALUE + 0x1200), (12 * MOTORCONTROL_MS_CLK) },
   { (MOTOR_STARTUP_PWM_VALUE + 0x1200), (12 * MOTORCONTROL_MS_CLK) },
   { (MOTOR_STARTUP_PWM_VALUE + 0x1200), (12 * MOTORCONTROL_MS_CLK) },
   { (MOTOR_STARTUP_PWM_VALUE + 0x1200), (12 * MOTORCONTROL_MS_CLK) },
   { (MOTOR_STARTUP_PWM_VALUE + 0x1200), (12 * MOTORCONTROL_MS_CLK) },
   { (MOTOR_STARTUP_PWM_VALUE + 0x1200), (12 * MOTORCONTROL_MS_CLK) },
   { (MOTOR_STARTUP_PWM_VALUE + 0x1200), (12 * MOTORCONTROL_MS_CLK) },
   { (MOTOR_STARTUP_PWM_VALUE + 0x1200), (12 * MOTORCONTROL_MS_CLK) },

   { (MOTOR_STARTUP_PWM_VALUE + 0x1200), (10 * MOTORCONTROL_MS_CLK) },
   { (MOTOR_STARTUP_PWM_VALUE + 0x1200), (10 * MOTORCONTROL_MS_CLK) },
   { (MOTOR_STARTUP_PWM_VALUE + 0x1200), (10 * MOTORCONTROL_MS_CLK) },
   { (MOTOR_STARTUP_PWM_VALUE + 0x1200), (10 * MOTORCONTROL_MS_CLK) },
   { (MOTOR_STARTUP_PWM_VALUE + 0x1200), (10 * MOTORCONTROL_MS_CLK) },
   { (MOTOR_STARTUP_PWM_VALUE + 0x1200), (10 * MOTORCONTROL_MS_CLK) },
   { (MOTOR_STARTUP_PWM_VALUE + 0x1200), (10 * MOTORCONTROL_MS_CLK) },
   { (MOTOR_STARTUP_PWM_VALUE + 0x1200), (10 * MOTORCONTROL_MS_CLK) },
   { (MOTOR_STARTUP_PWM_VALUE + 0x1200), (10 * MOTORCONTROL_MS_CLK) },
   { (MOTOR_STARTUP_PWM_VALUE + 0x1200), (10 * MOTORCONTROL_MS_CLK) },
   { (MOTOR_STARTUP_PWM_VALUE + 0x1200), (10 * MOTORCONTROL_MS_CLK) },
   { (MOTOR_STARTUP_PWM_VALUE + 0x1200), (10 * MOTORCONTROL_MS_CLK) },

   { (MOTOR_STARTUP_PWM_VALUE + 0x1200), (8 * MOTORCONTROL_MS_CLK) },
   { (MOTOR_STARTUP_PWM_VALUE + 0x1200), (8 * MOTORCONTROL_MS_CLK) },
   { (MOTOR_STARTUP_PWM_VALUE + 0x1200), (8 * MOTORCONTROL_MS_CLK) },
   { (MOTOR_STARTUP_PWM_VALUE + 0x1200), (8 * MOTORCONTROL_MS_CLK) },
   { (MOTOR_STARTUP_PWM_VALUE + 0x1200), (8 * MOTORCONTROL_MS_CLK) },

   { (MOTOR_STARTUP_PWM_VALUE + 0x1200), (6 * MOTORCONTROL_MS_CLK) },
   { (MOTOR_STARTUP_PWM_VALUE + 0x1200), (6 * MOTORCONTROL_MS_CLK) },
   { (MOTOR_STARTUP_PWM_VALUE + 0x1200), (6 * MOTORCONTROL_MS_CLK) },
   { (MOTOR_STARTUP_PWM_VALUE + 0x1200), (6 * MOTORCONTROL_MS_CLK) },
   { (MOTOR_STARTUP_PWM_VALUE + 0x1200), (6 * MOTORCONTROL_MS_CLK) },

};

/** \brief Configuration with rotor-stator alignment steps duty cycle */
const MotorControl_ConfigType MotorControl_gkt_AlignmentCfg =
{
   MotorControl_gkt_AlignSteps,
   MOTORCONTROL_NUMBER_OF_STEPS
};

/** \brief Configuration that stores the ramp up sequence */
const MotorControl_ConfigType MotorControl_gkt_RampUpCfg =
{
   MotorControl_gkt_RampUpSteps,
   MOTORCONTROL_RAMPUP_STEPS
};

/*-------------------------------------------------------------------------------------------------------------------*/
/*                                           Declaration Of Local Functions                                          */
/*-------------------------------------------------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------------------------------------------------*/
/*                                         Implementation Of Local Functions                                         */
/*-------------------------------------------------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------------------------------------------------*/
/*                                         Implementation Of Global Functions                                        */
/*-------------------------------------------------------------------------------------------------------------------*/
