/*-------------------------------------------------------------------------------------------------------------------*/
/**
 *    \file       Os_Tasks_Cfg.c
 *    \author     Nicolae-Bogdan Bacrau
 *    \brief      Defines the list of all the task function pointers and the slow tasks schedule table if the API is
 *                activated.
 */
/*-------------------------------------------------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------------------------------------------------*/
/*                                                     Inclusions                                                    */
/*-------------------------------------------------------------------------------------------------------------------*/

#include "Os_Core.h"
#include "Os_Tasks_Cfg.h"

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

/** \brief  Configures the schedule table for the slow tasks. Each entry defines the activation timestamp and slow task
 *          ID to be activated when the timestamp is reached. */
const Os_SlowTaskActivationType Os_gkat_ScheduleTable[OS_SCHEDULE_TABLE_NR_OF_ACTIVATIONS] =
   {
      { OS_MS2TICKS(0U), OS_5MS_TASK, },
      { OS_MS2TICKS(2U), OS_10MS_TASK, },
      { OS_MS2TICKS(5U), OS_5MS_TASK, },
      { OS_MS2TICKS(7U), OS_20MS_TASK, },
      { OS_MS2TICKS(10U), OS_5MS_TASK, },
      { OS_MS2TICKS(12U), OS_10MS_TASK, },
      { OS_MS2TICKS(15U), OS_5MS_TASK, },
      { OS_MS2TICKS(17U), OS_100MS_TASK, },
      { OS_MS2TICKS(20U), OS_5MS_TASK, },
      { OS_MS2TICKS(22U), OS_10MS_TASK, },
      { OS_MS2TICKS(25U), OS_5MS_TASK, },
      { OS_MS2TICKS(27U), OS_20MS_TASK, },
      { OS_MS2TICKS(30U), OS_5MS_TASK, },
      { OS_MS2TICKS(32U), OS_10MS_TASK, },
      { OS_MS2TICKS(35U), OS_5MS_TASK, },
      { OS_MS2TICKS(40U), OS_5MS_TASK, },
      { OS_MS2TICKS(42U), OS_10MS_TASK, },
      { OS_MS2TICKS(45U), OS_5MS_TASK, },
      { OS_MS2TICKS(47U), OS_20MS_TASK, },
      { OS_MS2TICKS(50U), OS_5MS_TASK, },
      { OS_MS2TICKS(52U), OS_10MS_TASK, },
      { OS_MS2TICKS(55U), OS_5MS_TASK, },
      { OS_MS2TICKS(60U), OS_5MS_TASK, },
      { OS_MS2TICKS(62U), OS_10MS_TASK, },
      { OS_MS2TICKS(65U), OS_5MS_TASK, },
      { OS_MS2TICKS(67U), OS_20MS_TASK, },
      { OS_MS2TICKS(70U), OS_5MS_TASK, },
      { OS_MS2TICKS(72U), OS_10MS_TASK, },
      { OS_MS2TICKS(75U), OS_5MS_TASK, },
      { OS_MS2TICKS(80U), OS_5MS_TASK, },
      { OS_MS2TICKS(82U), OS_10MS_TASK, },
      { OS_MS2TICKS(85U), OS_5MS_TASK, },
      { OS_MS2TICKS(87U), OS_20MS_TASK, },
      { OS_MS2TICKS(90U), OS_5MS_TASK, },
      { OS_MS2TICKS(92U), OS_10MS_TASK, },
      { OS_MS2TICKS(95U), OS_5MS_TASK, },
   };

/** \brief  Defines the list of all the task function pointers according to the defined task IDs (each ID defines an
 *          index from this list). */
const Os_Task Os_gkat_Tasks[OS_NR_OF_RUN_TIME_TASKS] =
   {
      &FUNC_OS_5MS_TASK, /*            OS_5MS_TASK        */
      &FUNC_OS_10MS_TASK, /*           OS_10MS_TASK       */
      &FUNC_OS_20MS_TASK, /*           OS_20MS_TASK       */
      &FUNC_OS_100MS_TASK, /*          OS_100MS_TASK      */
      &FUNC_OS_FAST_TASK, /*           OS_FAST_TASK       */
      &FUNC_OS_BACKGROUND_TASK, /*     OS_BACKGROUND_TASK */
   };

/*-------------------------------------------------------------------------------------------------------------------*/
/*                                           Declaration Of Local Functions                                          */
/*-------------------------------------------------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------------------------------------------------*/
/*                                         Implementation Of Local Functions                                         */
/*-------------------------------------------------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------------------------------------------------*/
/*                                         Implementation Of Global Functions                                        */
/*-------------------------------------------------------------------------------------------------------------------*/
