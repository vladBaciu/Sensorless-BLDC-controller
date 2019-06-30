/*-------------------------------------------------------------------------------------------------------------------*/
/**
 *    \file       Rte.c
 *    \author     RTE Generator
 *    \brief      Generated file - shall not be manually edited. 
 *                Implements the RTE initialization function which loads the RTE buffers with start values.
 */
/*-------------------------------------------------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------------------------------------------------*/
/*                                                     Inclusions                                                    */
/*-------------------------------------------------------------------------------------------------------------------*/

#include "Rte.h"

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
 * \brief      Initializes all the RTE buffers and update flags with start values.
 * \param      -
 * \return     Always E_OK.
 */
Std_ReturnType Rte_Start(void)
{
   /* Buffers. */
   Rte_LedIn_LedLeft_Buf = RTE_LED_OFF;
   Rte_LedIn_LedCenter_Buf = RTE_LED_OFF;
   Rte_LedIn_LedRight_Buf = RTE_LED_OFF;

   Rte_BtnOut_BtnJoystick_Buf = RTE_BTN_NOT_PRESSED;

   Rte_PotXOut_PotXAxis_Buf = 0UL;

   Rte_PotYOut_PotYAxis_Buf = 0UL;

   Rte_PotXOutToLcd_PotXLcd_Buf = RTE_JOYSTICK_CENTER;

   Rte_PotYOutToLcd_PotYLcd_Buf = RTE_JOYSTICK_CENTER;

   Rte_LcdInterface_LcdStruct_Buf.t_Menu = RTE_INIT;
   Rte_LcdInterface_LcdStruct_Buf.t_Submenu = RTE_NONE;

   Rte_LcdDirection_LcdDirectionIndicator_Buf = RTE_UNSET;

   Rte_MotorSpeed_RpmValue_Buf = 0U;

   Rte_UartSpeed_RpmValueSerial_Buf = 0U;

   Rte_BatPercentage_BatLevel_Buf = 0U;

   Rte_BatSoc_BatSoc_Buf = 0U;

   Rte_BatVoltage_BatVoltage_Buf = 0U;

   Rte_UartEnable_UartFlag_Buf = 0U;

   Rte_CurrentValue_CurrentAmp_Buf = 0U;

   Rte_MotorRunning_MotorFlag_Buf = 0U;

   Rte_DutyCyclePercentage_Percentage_Buf = 0U;

   /* Update flags. */
   Rte_PotXOutToLcd_PotXIn_PotXLcd_UpdateFlag = FALSE;
   Rte_PotYOutToLcd_PotYIn_PotYLcd_UpdateFlag = FALSE;
   Rte_PotXOut_PotXRaw_PotXAxis_UpdateFlag = FALSE;
   Rte_PotYOut_PotYRaw_PotYAxis_UpdateFlag = FALSE;
   Rte_LcdInterface_In_LcdStruct_UpdateFlag = FALSE;

   return E_OK;
}
