/*-------------------------------------------------------------------------------------------------------------------*/
/**
 *    \file       Mcu.c
 *    \author     Nicolae-Bogdan Bacrau
 *    \brief      Implements the AUTOSAR MCU driver initialization function which sets up and distributes clocks,
 *                enables flash acceleration features, sets voltage regulator settings and initializes RAM sections,
 *                and the MCU reset function which forces a SW reset.
 */
/*-------------------------------------------------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------------------------------------------------*/
/*                                                     Inclusions                                                    */
/*-------------------------------------------------------------------------------------------------------------------*/

#include "Mcu.h"
#include "stm32f407xx.h"
#include "Linker_Symbols.h"

/*-------------------------------------------------------------------------------------------------------------------*/
/*                                             Definition Of Local Macros                                            */
/*-------------------------------------------------------------------------------------------------------------------*/

/** \brief  Defines the fill pattern to be used in the .stack section for permitting easy measurements of the stack
 *          usage. */
#define MCU_STACK_FILL_PATTERN  (0xEFBEADDE)

/*-------------------------------------------------------------------------------------------------------------------*/
/*                                           Definition Of Local Data Types                                          */
/*-------------------------------------------------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------------------------------------------------*/
/*                                           Declaration Of Local Variables                                          */
/*-------------------------------------------------------------------------------------------------------------------*/

/** \brief  Stores the value of the stack pointer inside the MCU initialization function. */
static uint32 * Mcu_pul_CurrentStackPointer;

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

void Mcu_v_ReadStackPointer(uint32 * pul_StackPointer);

/*-------------------------------------------------------------------------------------------------------------------*/
/*                                         Implementation Of Local Functions                                         */
/*-------------------------------------------------------------------------------------------------------------------*/
/**
 * \brief      Called via an ASM branch and link instruction to enable reading the stack pointer value. The visibility
 *             of the function needs to be global for this purpose, but from the module's point of view this function
 *             is local (it is used only inside Mcu_Init(); it is not exported).
 * \param      pul_StackPointer : Pointer to the current value of the stack pointer register.
 * \return     -
 */
void Mcu_v_ReadStackPointer(uint32 * pul_StackPointer)
{
   Mcu_pul_CurrentStackPointer = pul_StackPointer;
}

/*-------------------------------------------------------------------------------------------------------------------*/
/*                                         Implementation Of Global Functions                                        */
/*-------------------------------------------------------------------------------------------------------------------*/

/**
 * \brief      Initializes and distributes the PLL derived clocks to the peripherals using the masked RegInit API for
 *             32 bits registers and initializes the RAM sections. In order to correctly initialize the stack section,
 *             the current stack pointer value is read so that the used call stack up to this point is not be
 *             overwritten.
 * \param      ConfigPtr : Pointer to the post-build configuration data to be loaded.
 * \return     -
 */
void Mcu_Init(const Mcu_ConfigType* ConfigPtr)
{
   uint32 * ul_RamWriteAddress;
   uint32 * ul_FlashLoadAddress;

   /* Load the referenced post-build configuration. */
   RegInit_gv_Masked32Bits(ConfigPtr);

   /* Initialize the .data section in RAM with values from flash. */
   ul_RamWriteAddress = (uint32*) &_Linker_DataStart_;
   ul_FlashLoadAddress = (uint32*) &_Linker_DataLoad_;
   while (ul_RamWriteAddress < (uint32*) &_Linker_DataEnd_)
   {
      *ul_RamWriteAddress = *ul_FlashLoadAddress;
      ul_RamWriteAddress++;
      ul_FlashLoadAddress++;
   }

   /* Initialize the .bss section in RAM with 0. */
   ul_RamWriteAddress = (uint32*) &_Linker_BssStart_;
   while (ul_RamWriteAddress < (uint32*) &_Linker_BssEnd_)
   {
      *ul_RamWriteAddress = 0UL;
      ul_RamWriteAddress++;
   }

   /* Copy the stack pointer (SP) register value to register R0. */
   __asm("MOV R0, SP");
   /* Branch and link to pass the current value of the stack pointer to the local Mcu_v_ReadStackPointer function. */
   __asm("BL Mcu_v_ReadStackPointer");

   /* Fill the .stack section with a known pattern starting from the stack tail up to the current stack pointer. */
   ul_RamWriteAddress = (uint32*) &_Linker_StackTail_;
   while (ul_RamWriteAddress < (uint32*) Mcu_pul_CurrentStackPointer)
   {
      *ul_RamWriteAddress = MCU_STACK_FILL_PATTERN;
      ul_RamWriteAddress++;
   }
}

/**
 * \brief      Forces a software reset through writing the Application Interrupt and Reset Control Register (AIRCR).
 * \param      -
 * \return     -
 */
void Mcu_PerformReset(void)
{
   uint32 ulTemp;

   /* Ensure all outstanding memory accesses, including buffered write, are completed before reset */
   __DSB();

   /* AIRCR shall be written only once. A read, modify, write back strategy is used since some of the register's fields
    * need to remain the same and others need to be updated. */

   /* Read the current value of AIRCR. */
   ulTemp = SCB->AIRCR;

   /* Preserve the PRIGROUP field, reset the others. */
   ulTemp &= (SCB_AIRCR_PRIGROUP_Msk);

   /* Overwrite the VECTKEY and SYSRESETREQ fields. */
   ulTemp |= ((0x5FAUL << SCB_AIRCR_VECTKEY_Pos) | (1UL << SCB_AIRCR_SYSRESETREQ_Pos));

   /* Write back updated value to AIRCR. */
   SCB->AIRCR = (uint32) ulTemp;

   /* Ensure completion of memory access */
   __DSB();

   while (TRUE)
   {
      /* Wait for reset. */
   }
}
