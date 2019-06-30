/*-------------------------------------------------------------------------------------------------------------------*/
/**
 *    \file       Rte_Tasks.c
 *    \author     RTE Generator
 *    \brief      Generated file - shall not be manually edited. 
 *                Implements all the OS tasks. Maps software component runnables to tasks.
 */
/*-------------------------------------------------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------------------------------------------------*/
/*                                                     Inclusions                                                    */
/*-------------------------------------------------------------------------------------------------------------------*/

#include "Rte.h"
#include "Os.h"

/* SWC Headers. */
#include "Led.h"
#include "Joystick.h"
#include "UserControl.h"
#include "LcdDisplay.h"
#include "MotorControl.h"
#include "SerialInterface.h"
#include "ControllerSensors.h"
#include "MotorController.h"
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
 * \brief      Initializes RTE and all the SWCs.
 * \param      -
 * \return     -
 */
TASK(OS_INIT_TASK)
{
   Rte_Start();
   Led_Init();
   Joystick_Init();
   LcdDisplay_Init();
   UserControl_Init();
   SerialInterface_Init();
   ControllerSensors_Init();



}

/**
 * \brief      Application specific OS_FAST_TASK task.
 * \param      -
 * \return     -
 */
TASK(OS_FAST_TASK)
{

}

/**
 * \brief      Application specific OS_5MS_TASK task.
 * \param      -
 * \return     -
 */
uint8 step = 1;
uint8 start = 1;
uint8 start2 = 0;
uint16 i = 5000;
uint16 ul_StartDuty = 0x500;
uint8 uc_I = 0;
TASK(OS_5MS_TASK)
{

////   if (Dio_ReadChannel(DIO_A_0) == STD_LOW)
////   {
////      Dio_WriteChannel(DIO_D_15, STD_HIGH);
////      while (i > 4500)
////      {
////         Delay_gv_Us(i);
////         MotorControl_gv_Move(step, ul_StartDuty);
////         step++;
////         if (step >= 7)
////            step = 1;
////
////         i = i - 20;
////         ul_StartDuty = ul_StartDuty + 250;
////         if (ul_StartDuty >= 0x2000)
////         {
////            ul_StartDuty = 0x2000;
////
////         }
////         start2 = 0;
////      }
////      for (;;)
////      {
////         Delay_gv_Us(i);
////         MotorControl_gv_Move(step, ul_StartDuty);
////         step++;
////         if (step >= 7)
////            step = 1;
////
////      }
////
//////      while (i < 5000)
//////      {
//////         Delay_gv_Us(i);
//////         MotorControl_gv_Move(step, ul_StartDuty);
//////         step++;
//////         if (step >= 7)
//////            step = 1;
//////         i = i + 20;
//////
//////         if (ul_StartDuty <= 250)
//////         {
//////            ul_StartDuty = 0x500;
//////         }
//////         else
//////         {
//////            ul_StartDuty = ul_StartDuty - 250;
//////         }
//////         start2 = 0;
//////      }
//      Dio_WriteChannel(DIO_D_15, STD_LOW);
//
//      //  MotorControl_gv_Move(7, 0x0000);
//   }
//   else
//   {
//      i = 5000;
//      start2 = 1;
//      ul_StartDuty = 0x500;
//   }
//   //
//   //   if (start == 1)
//   //   {
//   //      TIM2->DIER = (TIM_DIER_UIE);
//   //      start = 0;
//   //      start2 = 1;
//   //   }
//   //   else
//   //   {
//   //
//   //   }
}

/**
 * \brief      Application specific OS_10MS_TASK task.
 * \param      -
 * \return     -
 */
TASK(OS_10MS_TASK)
{

   //   if(uc_Step <= 20)
   //   {
   //      uc_Step = 20;
   //   }
   //   else
   //   uc_Step = uc_Step - 20;

}

/**
 * \brief      Application specific OS_20MS_TASK task.
 * \param      -
 * \return     -
 */
TASK(OS_20MS_TASK)
{
}

/**
 * \brief      Application specific OS_100MS_TASK task.
 * \param      -
 * \return     -
 */
TASK(OS_100MS_TASK)
{
   Led_Main();
   Joystick_Main();
   ControllerSensors_ReadBattery();
   UserControl_Main();
   LcdDisplay_Main();
   SerialInterface_TransmitSpeed();
   ControllerSensors_ReadCurrent();
   MotorController_Main();
}

/**
 * \brief      Application specific OS_BACKGROUND_TASK task.
 * \param      -
 * \return     -
 */
TASK(OS_BACKGROUND_TASK)
{
}

