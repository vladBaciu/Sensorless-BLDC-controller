/*-------------------------------------------------------------------------------------------------------------------*/
/**
 *    \file       EcuM.c
 *    \author     Nicolae-Bogdan Bacrau
 *    \brief      Minimal implementation of the AUTOSAR ECU manager module.
 *
 *    According to the AUTOSAR specifications, a minimal initialization of the MCU has taken place upon reaching the
 *    main C function, so a stack has been set up and code can be executed. In this implementation all the
 *    initializations before the main C function are performed in a platform specific (microcontroller dependent)
 *    startup script.
 *    For stack usage optimizations EcuM_Init() is defined as the main function and it's purpose is initializing the
 *    MCAL drivers and starting the Operating system. In this implementation no wake-up reasons are being handled, all
 *    RTE and SWC initializations are performed in the initialization task, no post-build configuration is checked for
 *    consistency and there is no API for shutting down the microcontroller.
 */
/*-------------------------------------------------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------------------------------------------------*/
/*                                                     Inclusions                                                    */
/*-------------------------------------------------------------------------------------------------------------------*/

#include "EcuM.h"
#include "Os.h"


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
 * \brief      Carries out the startup procedure (initializes basic software) and starts the Operating System.
 * \param      -
 * \return     Never returns because control is handled to the Operating System.
 */
void EcuM_Init(void)
{
   /* Initialize basic software modules. */
   EcuM_AL_DriverInitOne();
   /* Handle control to the Operating System. This call never returns. */
   StartOS(OSDEFAULTAPPMODE);
}
