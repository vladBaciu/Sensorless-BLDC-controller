/*-------------------------------------------------------------------------------------------------------------------*/
/**
 *    \file       Pwm.h
 *    \author     Baciu Vlad-Eusebiu
 *    \brief      Exports PWM module interfaces (Init and SetDutyCycle) and post-build configuration.
 */
/*-------------------------------------------------------------------------------------------------------------------*/

#ifndef PWM_H
#define PWM_H

/*-------------------------------------------------------------------------------------------------------------------*/
/*                                                     Inclusions                                                    */
/*-------------------------------------------------------------------------------------------------------------------*/
#include "Std_Types.h"
#include "stm32f407xx.h"
#include "RegInit.h"
#include "Pwm_Cfg.h"
/*-------------------------------------------------------------------------------------------------------------------*/
/*                                            Definition Of Global Macros                                            */
/*-------------------------------------------------------------------------------------------------------------------*/
#define ASD
/*-------------------------------------------------------------------------------------------------------------------*/
/*                                          Definition Of Global Data Types                                          */
/*-------------------------------------------------------------------------------------------------------------------*/
/** \brief Numeric identifier of a PWM channel.*/
typedef uint8 Pwm_ChannelType;

/** \brief Channel config type */
typedef struct
{
   /** \brief Pointer to compare register CCRx */
   uint32* pul_DutyCycleRegister;
   /** \brief Pointer to TIMx structure */
   TIM_TypeDef* pt_Register;
} Pwm_CfgType;

/** \brief PWM config type */
typedef struct
{
   /** \brief Pointer to channel config array. */
   const Pwm_CfgType* kpt_ChannelCfg;
   /** \brief Pointer to register config array. */
   const RegInit_Masked32BitsConfigType* kpt_RegisterCfg;
} Pwm_ConfigType;
/*-------------------------------------------------------------------------------------------------------------------*/
/*                                             Export Of Global Variables                                            */
/*-------------------------------------------------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------------------------------------------------*/
/*                                             Export Of Global Constants                                            */
/*-------------------------------------------------------------------------------------------------------------------*/
extern const Pwm_ConfigType Pwm_gkt_Config;
/*-------------------------------------------------------------------------------------------------------------------*/
/*                                             Export Of Global Functions                                            */
/*-------------------------------------------------------------------------------------------------------------------*/
extern void Pwm_Init(const Pwm_ConfigType* ConfigPtr);
extern void Pwm_SetDutyCycle(Pwm_ChannelType ChannelNumber, uint16 DutyCycle);
/*-------------------------------------------------------------------------------------------------------------------*/
#endif /* PWM_H */
