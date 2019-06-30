/*-------------------------------------------------------------------------------------------------------------------*/
/**
 *    \file       Adc.c
 *    \author     Baciu Vlad-Eusebiu
 *    \brief      Implements the ADC interfaces: SetupResultBuffer,StartGroupConversion,GetGroupStatus.
 */
/*-------------------------------------------------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------------------------------------------------*/
/*                                                     Inclusions                                                    */
/*-------------------------------------------------------------------------------------------------------------------*/
#include "Adc.h"
/*-------------------------------------------------------------------------------------------------------------------*/
/*                                             Definition Of Local Macros                                            */
/*-------------------------------------------------------------------------------------------------------------------*/
#define ADC_CLEAR_CHANNEL_VALUE (0x00)
/*-------------------------------------------------------------------------------------------------------------------*/
/*                                           Definition Of Local Data Types                                          */
/*-------------------------------------------------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------------------------------------------------*/
/*                                           Declaration Of Local Variables                                          */
/*-------------------------------------------------------------------------------------------------------------------*/

/** \brief  Array that holds the addresses of the data buffers */
static uint32* Adc_apul_AdressBuffer[ADC_NUMBER_OF_GROUPS];

/** \brief  Stores the address of the selected post-build configuration. */
static Adc_GroupCfgType * Adc_pt_GroupsConfig;

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
 * \brief   Init all the registers from the configuration array.
 * \param   ConfigPtr: pointer to the configuration array.
 * \return  -
 */
void Adc_Init(const Adc_ConfigType* ConfigPtr)
{
   RegInit_gv_Masked32Bits(ConfigPtr->pt_ConfigRegisters);

   Adc_pt_GroupsConfig = (Adc_GroupCfgType *) ConfigPtr->pt_ConfigGroup;

}

/**
 * \brief    Sets the start bit in CR2 register in order to start the channel conversion.
 * \param    Group: number of group from array group configuration.
 * \return   -
 */
void Adc_StartGroupConversion(Adc_GroupType Group)
{

   Adc_GroupType t_Channel = (Adc_GroupType) Adc_pt_GroupsConfig[Group].t_Channel;

   Adc_pt_GroupsConfig[Group].pt_Registers->SQR3 &= (uint32) ADC_CLEAR_CHANNEL_VALUE;
   /* Select the position of the sampling sequence */
   Adc_pt_GroupsConfig[Group].pt_Registers->SQR3 |= (uint32) t_Channel;

   /* Start the regular conversion */
   Adc_pt_GroupsConfig[Group].pt_Registers->CR2 |= (uint32) ADC_CR2_SWSTART;

}

/**
 * \brief   Shows the status of the ADC conversion.
 * \param   Group: number of group from array group configuration.
 * \return  Status of the conversion (BUSY,COMPLETED,IDLE).
 */
Adc_StatusType Adc_GetGroupStatus(Adc_GroupType Group)
{
   /* Variable that holds the current state */
   Adc_StatusType t_ReturnValue;

   /* Variable that holds the SR state */
   uint32 ul_Status;

   /* Get ADCx_SR register state */
   ul_Status = (uint32) Adc_pt_GroupsConfig[Group].pt_Registers->SR;

   /* Check the status of the ADCx_SR register*/
   if ((ul_Status & (uint32) ADC_SR_STRT) == 0x00)
   {
      /* If the STRT bit is 0 then no regular conversion started */
      t_ReturnValue = ADC_IDLE;

   }
   else if (((ul_Status & (uint32) ADC_SR_EOC) != 0))
   {

      t_ReturnValue = ADC_COMPLETED;


      /* Store data register value to the Data Buffer */
      *Adc_apul_AdressBuffer[Adc_pt_GroupsConfig[Group].t_Channel] = Adc_pt_GroupsConfig[Group].pt_Registers->DR;


      Adc_pt_GroupsConfig[Group].pt_Registers->SR |= ~(ADC_SR_STRT);
   }
   else
   {

      t_ReturnValue = ADC_BUSY;

   }

   return t_ReturnValue;
}

/**
 * \brief   Stores the address of the buffer in the resultBuffer array.
 * \param   Group: number of group from array group configuration.
 *          DataBufferPtr: buffer address.
 * \return  Status of the operation (E_OK or E_NOT_OK).
 */
Std_ReturnType Adc_SetupResultBuffer(Adc_GroupType Group, const Adc_ValueGroupType* DataBufferPtr)
{
   /* Variable that holds the return value */
   Std_ReturnType t_ReturnValue;

   /* Store the address of the buffer in the result buffer */
   Adc_apul_AdressBuffer[Adc_pt_GroupsConfig[Group].t_Channel] = (uint32*) DataBufferPtr;

   t_ReturnValue = E_OK;

   return t_ReturnValue;
}
