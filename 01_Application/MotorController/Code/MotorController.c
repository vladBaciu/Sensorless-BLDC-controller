/*-------------------------------------------------------------------------------------------------------------------*/
/**
 *    \file       MotorController.c
 *    \author     Baciu Vlad-Eusebiu
 *    \brief      Empty template to be used for all .c files. This file provides an example for the case in which a
 *                detailed description is not needed.
 */
/*-------------------------------------------------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------------------------------------------------*/
/*                                                     Inclusions                                                    */
/*-------------------------------------------------------------------------------------------------------------------*/
#include "MotorController.h"
#include "Os_Interrupts_Cfg.h"
/*-------------------------------------------------------------------------------------------------------------------*/
/*                                             Definition Of Local Macros                                            */
/*-------------------------------------------------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------------------------------------------------*/
/*                                           Definition Of Local Data Types                                          */
/*-------------------------------------------------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------------------------------------------------*/
/*                                           Declaration Of Local Variables                                          */
/*-------------------------------------------------------------------------------------------------------------------*/
uint8 MotorController_uc_AllignedDone = 0;
uint8 MotorController_uc_StartDone = 0;
/*-------------------------------------------------------------------------------------------------------------------*/
/*                                          Declaration Of Global Variables                                          */
/*-------------------------------------------------------------------------------------------------------------------*/
Rte_MotorFlagType MotorController_StartFlag;
Rte_SpeedType MotorController_Rpm;
Rte_SpeedType MotorController_Duty;
Rte_DirectionType MotorController_Direction;
/*-------------------------------------------------------------------------------------------------------------------*/
/*                                           Declaration Of Local Constants                                          */
/*-------------------------------------------------------------------------------------------------------------------*/
uint8 MotorController_DirectionFlag = 0;
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
void MotorController_Main(void)
{
   Rte_Read_In_RpmValue(&MotorController_Rpm);
   Rte_Read_In_LcdDirectionIndicator(&MotorController_Direction);
   Rte_Read_In_MotorFlag(&MotorController_StartFlag);
   if ((MotorController_Direction == RTE_FORWARD) && (MotorController_DirectionFlag == 0))
   {
      uc_StepIrq = MOTORCONTROLLER_FORWARD_START;
      MotorController_DirectionFlag = 1;
   }
   else if ((MotorController_Direction == RTE_BACKWARD) && (MotorController_DirectionFlag == 0))
   {
      uc_StepIrq = MOTORCONTROLLER_BACKWARD_START;
      MotorController_DirectionFlag = 1;
   }
   else
   {

   }

   if ((MotorController_StartFlag == STD_ON) && (MotorController_uc_AllignedDone == STD_OFF))
   {
      IoHwAb_EnableStartSequence();
      MotorController_uc_AllignedDone = STD_ON;
      MotorController_uc_StartDone = STD_ON;
   }
   else if ((MotorController_StartFlag == STD_OFF) && (MotorController_uc_StartDone == STD_ON))
   {

      IoHwAb_DisableStartSequence();
      MotrolControl_v_TurnOffPwm();
      MotorController_uc_AllignedDone = STD_OFF;
      MotorController_uc_StartDone = STD_OFF;
      uc_StepIrq = 0;
      uc_IndexIrq = 0;
      uc_InterruptNumber = 0;
      uc_StartupRampFlag = 0;
      MotorController_Duty = 0;
      Rte_Write_Out_Percentage(&MotorController_Duty);

   }

}
