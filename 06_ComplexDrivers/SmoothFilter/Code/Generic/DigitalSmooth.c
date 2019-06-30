/*-------------------------------------------------------------------------------------------------------------------*/
/**
 *    \file       DigitalSmooth.c
 *    \author     Baciu Vlad-Eusebiu
 *    \brief      Empty template to be used for all .c files. This file provides an example for the case in which a
 *                detailed description is not needed.
 */
/*-------------------------------------------------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------------------------------------------------*/
/*                                                     Inclusions                                                    */
/*-------------------------------------------------------------------------------------------------------------------*/
#include "DigitalSmooth.h"
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
/*
 *    /brief
 *    /param
 *    /return
 */
uint16 DigialSmooth_LPF(uint16 RawData, uint16 SmoothedValue)
{
   SmoothedValue = ((RawData * (10 - DIGITALSMOOTH_LPF_COEFFICIENT)) + (SmoothedValue * DIGITALSMOOTH_LPF_COEFFICIENT))
      / 10;

   return SmoothedValue;
}
/*
 *    /brief
 *    /param
 *    /return
 */
uint16 DigitalSmooth_Filter(DigitalSmooth_MedianFilter *Filter, uint16 Value)
{
   uint16 us_Result;
   /* get current data arrray position */
   uint8 uc_Position = Filter->uc_Position;
   /* get current length */
   uint8 uc_Length = Filter->uc_Count;
   uint8 uc_Flag = 0;
   uint8 uc_OldIndex;
   uint16 uc_OldValue = 0;

   if (uc_Length != 0)
   {
      if (uc_Length == DIGITALSMOOTH_LPF_SIZE)
      {
         uc_OldIndex = 0;
         while (Filter->auc_IndexArray[uc_OldIndex] != uc_Position)
         {
            ++uc_OldIndex;
         }
         uc_OldValue = Filter->aul_DataArray[uc_Position];
         uc_Flag = 0;
      }
      else
      {
         Filter->auc_IndexArray[uc_Position] = uc_Position;
         uc_OldIndex = uc_Position;
         uc_Flag = 1;
      }

      Filter->aul_DataArray[uc_Position] = Value;
      uint8 *puc_Index = &Filter->auc_IndexArray[uc_OldIndex];

      if (uc_OldValue < Value)
      {
         uint8 uc_CheckIndex;
         while (uc_OldIndex != uc_Length)
         {
            uc_OldIndex++;
            uc_CheckIndex = *(++puc_Index);
            if (Filter->aul_DataArray[uc_CheckIndex] < Value)
            {
               *puc_Index = *(puc_Index - 1);
               *(puc_Index - 1) = uc_CheckIndex;
            }
            else
               break;
         }
      }
      else if ((uc_OldValue > Value) || (uc_Flag == 1))
      {
         uint8 uc_CheckIndex;
         while (uc_OldIndex-- != 0)
         {
            uc_CheckIndex = *(--puc_Index);
            if (Filter->aul_DataArray[uc_CheckIndex] > Value)
            {
               *puc_Index = *(puc_Index + 1);
               *(puc_Index + 1) = uc_CheckIndex;
            }
            else
               break;
         }
      }
      us_Result = Filter->aul_DataArray[Filter->auc_IndexArray[uc_Length / 2]];
   }
   else
   {
      Filter->uc_Position = 0;
      *Filter->auc_IndexArray = 0;
      *Filter->aul_DataArray = Value;
      us_Result = Value;
   }
   uc_Position++;
   Filter->uc_Position = (uc_Position == DIGITALSMOOTH_LPF_SIZE) ? (0) : uc_Position;
   if (uc_Length < DIGITALSMOOTH_LPF_SIZE)
   {
      Filter->uc_Count++;
   }

   return us_Result;
}

