/*-------------------------------------------------------------------------------------------------------------------*/
/**
 *    \file       Adc.h
 *    \author     Baciu Vlad-Eusebiu
 *    \brief      Exports ADC data types, post build configuration and ADC interfaces.
 */
/*-------------------------------------------------------------------------------------------------------------------*/

#ifndef ADC_H
#define ADC_H

/*-------------------------------------------------------------------------------------------------------------------*/
/*                                                     Inclusions                                                    */
/*-------------------------------------------------------------------------------------------------------------------*/
#include "Std_Types.h"
#include "stm32f407xx.h"
#include "RegInit.h"
#include "Adc_Cfg.h"
/*-------------------------------------------------------------------------------------------------------------------*/
/*                                            Definition Of Global Macros                                            */
/*-------------------------------------------------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------------------------------------------------*/
/*                                          Definition Of Global Data Types                                          */
/*-------------------------------------------------------------------------------------------------------------------*/

/** \brief  Implements the status of the conversion of the requested ADC channel group */
typedef enum
{
   /**
    * \brief The conversion has not been started.
    *        No result available.
    */
   ADC_IDLE,

   /**
    * \brief The conversion of the specified group has been started.
    *        No result available so far.
    */
   ADC_BUSY,

   /**
    * \brief A conversion has been finished.
    *        Result is available for all channels of the group.
    */
   ADC_COMPLETED,

   /**
    * \brief The result buffer is completely filled.
    *        For each channel of the selected group the result is available.
    */
   ADC_STREAM_COMPLETED,

} Adc_StatusType;
/**
 * \brief   Numeric ID of an ADC group.
 */
typedef uint8 Adc_GroupType;

/**
 * \brief   Type for reading the converted value of channel group.
 */
typedef uint16 Adc_ValueGroupType;

/** \brief  Group config type.*/
typedef struct
{
   /** \brief ADC channel number */
   Adc_GroupType t_Channel;

   /** \brief Pointer to ADC  struct. */

   ADC_TypeDef * pt_Registers;

} Adc_GroupCfgType;

typedef struct
{
   /** \brief Pointer to groups typedef */
   const Adc_GroupCfgType* pt_ConfigGroup;
   /** \brief Pointer to registers typedef */
   const RegInit_Masked32BitsConfigType*   pt_ConfigRegisters;
}Adc_ConfigType;
/*-------------------------------------------------------------------------------------------------------------------*/
/*                                             Export Of Global Variables                                            */
/*-------------------------------------------------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------------------------------------------------*/
/*                                             Export Of Global Constants                                            */
/*-------------------------------------------------------------------------------------------------------------------*/
extern const Adc_ConfigType Adc_gkt_Cfg;
/*-------------------------------------------------------------------------------------------------------------------*/
/*                                             Export Of Global Functions                                            */
/*-------------------------------------------------------------------------------------------------------------------*/

extern void Adc_Init(const Adc_ConfigType* ConfigPtr);
extern Std_ReturnType Adc_SetupResultBuffer(Adc_GroupType Group, const Adc_ValueGroupType* DataBufferPtr);
extern void Adc_StartGroupConversion(Adc_GroupType Group);
extern Adc_StatusType Adc_GetGroupStatus(Adc_GroupType Group);

/*-------------------------------------------------------------------------------------------------------------------*/
#endif /* ADC_H */
