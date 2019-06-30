/*-------------------------------------------------------------------------------------------------------------------*/
/**
 *    \file       MotorControl.h
 *    \author     Baciu Vlad-Eusebiu
 *    \brief      Empty template to be used for all .h files. This file provides an example for the case in which a
 *                detailed description is not needed.
 */
/*-------------------------------------------------------------------------------------------------------------------*/

#ifndef MOTOR_CONTROL_H
#define MOTOR_CONTROL_H

/*-------------------------------------------------------------------------------------------------------------------*/
/*                                                     Inclusions                                                    */
/*-------------------------------------------------------------------------------------------------------------------*/
#include "Std_Types.h"
#include "MotorControl_Cfg.h"
/*-------------------------------------------------------------------------------------------------------------------*/
/*                                            Definition Of Global Macros                                            */
/*-------------------------------------------------------------------------------------------------------------------*/
#define MOTORCONTROL_NUMBER_OF_STEPS               (25U)

#define MOTORCONTROL_RAMPUP_STEPS                  (166U)
/*-------------------------------------------------------------------------------------------------------------------*/
/*                                          Definition Of Global Data Types                                          */
/*-------------------------------------------------------------------------------------------------------------------*/
/** \brief */
typedef uint16 MotorControl_ValueType;

typedef uint32 MotorControl_TimeValueType;
/** \brief */
typedef struct
{
   MotorControl_ValueType t_Value;
   MotorControl_TimeValueType t_Time;
} MotorControl_GroupCfgType;

/** \brief */

typedef struct
{
   const MotorControl_GroupCfgType *pt_ConfigGroup;
   uint16 ul_NumberOfSteps;
} MotorControl_ConfigType;
/*-------------------------------------------------------------------------------------------------------------------*/
/*                                             Export Of Global Variables                                            */
/*-------------------------------------------------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------------------------------------------------*/
/*                                             Export Of Global Constants                                            */
/*-------------------------------------------------------------------------------------------------------------------*/
extern const MotorControl_ConfigType MotorControl_gkt_AlignmentCfg;
extern const MotorControl_ConfigType MotorControl_gkt_RampUpCfg;
/*-------------------------------------------------------------------------------------------------------------------*/
/*                                             Export Of Global Functions                                            */
/*-------------------------------------------------------------------------------------------------------------------*/
extern void MotorControl_gv_Init();
extern void MotorControl_gv_AlignRoutine(const MotorControl_ConfigType *ConfigPtr, uint8 Step);
extern void MotorControl_gv_SetRampUpTime(const MotorControl_ConfigType *ConfigPtr, uint8 Step);
extern void MotorControl_gv_Step1(uint16 DutyCylce);
extern void MotorControl_gv_Step2(uint16 DutyCylce);
extern void MotorControl_gv_Step3(uint16 DutyCylce);
extern void MotorControl_gv_Step4(uint16 DutyCylce);
extern void MotorControl_gv_Step5(uint16 DutyCylce);
extern void MotorControl_gv_Step6(uint16 DutyCylce);
extern void MotorControl_gv_Move(uint8 Step, uint16 DutyCylce);
extern void MotrolControl_v_TurnOffPwm();
extern void MotorControl_gv_BemfAFalling();
extern void MotorControl_gv_BemfARising();
extern void MotorControl_gv_BemfBFalling();
extern void MotorControl_gv_BemfBRising();
extern void MotorControl_gv_BemfCFalling();
extern void MotorControl_gv_BemfCRising();
extern void MotorControl_gv_EnableStartSequence();
extern void MotorControl_gv_EnableAlignSequence();
extern void MotorControl_gv_DisableStartSequence();
extern void MotorControl_gv_DisableAlignSequence();
/*-------------------------------------------------------------------------------------------------------------------*/
#endif /* MOTOR_CONTROL_H */
