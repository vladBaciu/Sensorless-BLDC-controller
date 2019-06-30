/*-------------------------------------------------------------------------------------------------------------------*/
/**
 *    \file       Led_Core.c
 *    \author     Baciu Vlad-Eusebiu
 *    \brief      Implements the behavior of the software component through generic runnables. The behavior can support
 *                multiple instances and the interaction with the RTE is performed through clearly defined input and
 *                output interfaces with configurable content.
 */
/*-------------------------------------------------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------------------------------------------------*/
/*                                                     Inclusions                                                    */
/*-------------------------------------------------------------------------------------------------------------------*/
#include "Led_Core.h"
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
Rte_LedEnableType Led_gat_InputValues[LED_NUMBER_OF_INSTANCES];
IoHwAb_DigitalLevelType Led_gat_OutputValues[LED_NUMBER_OF_INSTANCES];
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
 * \brief      Initializes all the core global variables and turns off all LED channels.
 * \param      -
 * \return     -
 */
void Led_Init(void)
{
   uint8 uc_I;

   for (uc_I = 0U; uc_I < LED_NUMBER_OF_INSTANCES; uc_I++)
   {
      Led_gat_InputValues[uc_I] = RTE_LED_OFF;
      if (STD_HIGH == Led_gkat_ActiveValues[uc_I])
      {
         Led_gat_OutputValues[uc_I] = STD_LOW;
      }
      else
      {
         Led_gat_OutputValues[uc_I] = STD_HIGH;
      }
   }
   Led_gv_RteOutputUpdate();
}

void Led_Main(void)
{
   uint8 uc_I;
   Led_gv_RteInputUpdate();
   for (uc_I = 0U; uc_I < LED_NUMBER_OF_INSTANCES; uc_I++)
   {
      switch (Led_gat_InputValues[uc_I])
      {
         case (RTE_LED_ON):
         {
            if (STD_HIGH == Led_gkat_ActiveValues[uc_I])
            {
               Led_gat_OutputValues[uc_I] = STD_HIGH;

            }
            else
            {
               Led_gat_OutputValues[uc_I] = STD_LOW;

            }
            break;
         }
         case (RTE_LED_OFF):
         {
            if (STD_HIGH == Led_gkat_ActiveValues[uc_I])
            {
               Led_gat_OutputValues[uc_I] = STD_LOW;
            }
            else
            {
               Led_gat_OutputValues[uc_I] = STD_HIGH;
            }
            break;
         }
         default:
         {
            break;
         }
      }
   }

   /* Write the logic level to all DIO channels with Led_gat_OutputValues[]. */
   Led_gv_RteOutputUpdate();
}
