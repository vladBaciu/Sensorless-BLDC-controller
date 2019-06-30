/*-------------------------------------------------------------------------------------------------------------------*/
/**
 *    \file       Rte_LcdDisplay.h
 *    \author     RTE Generator
 *    \brief      Generated file - shall not be manually edited. 
 *                Implements all the RTE read and write operations that are performed by the LcdDisplay software
 *                component.
 */
/*-------------------------------------------------------------------------------------------------------------------*/

#ifndef RTE_LCDDISPLAY_H
#define RTE_LCDDISPLAY_H

/*-------------------------------------------------------------------------------------------------------------------*/
/*                                                     Inclusions                                                    */
/*-------------------------------------------------------------------------------------------------------------------*/

#include "Rte.h"

/*-------------------------------------------------------------------------------------------------------------------*/
/*                                            Definition Of Global Macros                                            */
/*-------------------------------------------------------------------------------------------------------------------*/

#define Rte_IsUpdated_In_LcdStruct() (Rte_LcdInterface_In_LcdStruct_UpdateFlag)
#define Rte_Read_In_LcdStruct(x) \
   do \
   { \
      (*x) = Rte_LcdInterface_LcdStruct_Buf; \
      Rte_LcdInterface_In_LcdStruct_UpdateFlag = FALSE; \
   } while(0)

#define Rte_Read_In_LcdDirectionIndicator(x) ((*x) = Rte_LcdDirection_LcdDirectionIndicator_Buf)

#define Rte_Read_In_BatLevel(x) ((*x) = Rte_BatPercentage_BatLevel_Buf)

#define Rte_Read_In_BatSoc(x) ((*x) = Rte_BatSoc_BatSoc_Buf)

#define Rte_Read_In_BatVoltage(x) ((*x) = Rte_BatVoltage_BatVoltage_Buf)

#define Rte_Read_In_CurrentAmp(x) ((*x) = Rte_CurrentValue_CurrentAmp_Buf)

#define Rte_Read_In_RpmValue(x) ((*x) = Rte_MotorSpeed_RpmValue_Buf)

#define Rte_Read_In_Percentage(x) ((*x) = Rte_DutyCyclePercentage_Percentage_Buf)

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
#endif /* RTE_LCDDISPLAY_H */