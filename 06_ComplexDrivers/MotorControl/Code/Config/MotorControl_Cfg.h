/*-------------------------------------------------------------------------------------------------------------------*/
/**
 *    \file       MotorControl_Cfg.h
 *    \author     Baciu Vlad-Eusebiu
 *    \brief      Empty template to be used for all .h files. This file provides an example for the case in which a
 *                detailed description is not needed.
 */
/*-------------------------------------------------------------------------------------------------------------------*/

#ifndef MOTOR_CONTROL_CFG_H
#define MOTOR_CONTROL_CFG_H

/*-------------------------------------------------------------------------------------------------------------------*/
/*                                                     Inclusions                                                    */
/*-------------------------------------------------------------------------------------------------------------------*/
#include "MotorControl.h"
/*-------------------------------------------------------------------------------------------------------------------*/
/*                                            Definition Of Global Macros                                            */
/*-------------------------------------------------------------------------------------------------------------------*/
/** \brief Phase A high side */
#define MOTORCONTROL_PHASE_AH  PWM_B_5

/** \brief Phase A low side */
#define MOTORCONTROL_PHASE_AL  DIO_D_0

/** \brief Phase B high side */
#define MOTORCONTROL_PHASE_BH  PWM_B_7

/** \brief Phase B low side */
#define MOTORCONTROL_PHASE_BL  DIO_D_2

/** \brief Phase C high side */
#define MOTORCONTROL_PHASE_CH  PWM_B_9

/** \brief Phase C low side */
#define MOTORCONTROL_PHASE_CL  DIO_D_4

/** \brief Duty cycle value for start routine */
#define MOTORCONTROL_PWM_START (0x2000)


#define MOTORCONTROL_MS_CLK                        (10000U)

#define MOTORCONTROL_MS_PERIOD                     (150U)

#define MOTORCONTROL_TIMER_VALUE                   (MOTORCONTROL_MS_PERIOD * MOTORCONTROL_MS_CLK)

#define MOTORCONTROL_MS_PERIOD_ALIGNMENT_VALUE         (30U)

#define MOTOR_TIMER_ALIGNMENT_VALUE                (MOTORCONTROL_MS_PERIOD_ALIGNMENT_VALUE * MOTORCONTROL_MS_CLK)

#define MOTOR_LAST_ALIGN_PWM_VALUE                 (0x4200U)

#define MOTOR_STARTUP_PWM_VALUE                    (0x300)
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
#endif /* MOTOR_CONTROL_CFG_H */
