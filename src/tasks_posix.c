/*******************************************************************************
   System Tasks File

   File Name:
    tasks.c

   Summary:
    This file contains source code necessary to maintain system's polled tasks.

   Description:
    This file contains source code necessary to maintain system's polled tasks.
    It implements the "SYS_Tasks" function that calls the individual "Tasks"
    functions for all polled MPLAB Harmony modules in the system.

   Remarks:
    This file requires access to the systemObjects global data structure that
    contains the object handles to all MPLAB Harmony module objects executing
    polled in the system.  These handles are passed into the individual module
    "Tasks" functions to identify the instance of the module to maintain.
*******************************************************************************/

// DOM-IGNORE-BEGIN
/*******************************************************************************
* Copyright (C) 2018 Microchip Technology Inc. and its subsidiaries.
*
* Subject to your compliance with these terms, you may use Microchip software
* and any derivatives exclusively with Microchip products. It is your
* responsibility to comply with third party license terms applicable to your
* use of third party software (including open source software) that may
* accompany Microchip software.
*
* THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER
* EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED
* WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A
* PARTICULAR PURPOSE.
*
* IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE,
* INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND
* WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS
* BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO THE
* FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS IN
* ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF ANY,
* THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.
*******************************************************************************/
// DOM-IGNORE-END

// *****************************************************************************
// *****************************************************************************
// Section: Included Files
// *****************************************************************************
// *****************************************************************************

#include "definitions.h"
#include "tasks.h"

// *****************************************************************************
// *****************************************************************************
// Section: RTOS "Tasks" Routine
// *****************************************************************************
// *****************************************************************************


TaskHandle_t xSim_Tasks;
void lSim_Tasks(  void *pvParameters  )
{
    while(1)
    {
        SIM_APP_Tasks();
        vTaskDelay(10 / portTICK_PERIOD_MS);
    }
}


TaskHandle_t xTask1;
void lTask1(  void *pvParameters  )
{
    while(1)
    {
        Task1_Loop();
    }
}

TaskHandle_t xTask2;
void lTask2(  void *pvParameters  )
{
    while(1)
    {
        Task2_Loop();
    }
}


// *****************************************************************************
// *****************************************************************************
// Section: System "Tasks" Routine
// *****************************************************************************
// *****************************************************************************

/*******************************************************************************
   Function:
    void SYS_Tasks ( void )

   Remarks:
    See prototype in system/common/sys_module.h.
 */
void SYS_Tasks ( void )
{
    /* Maintain system services */


    /* Task used for peripheral emulation in sim */
    (void) xTaskCreate((TaskFunction_t) lSim_Tasks,
                "Sim_Tasks",
                512,
                NULL,
                configMAX_PRIORITIES-1,
                &xSim_Tasks);

    /* Create OS Thread for Task1. */
    (void) xTaskCreate((TaskFunction_t) lTask1,
                "Task1",
                512,
                NULL,
                TASK1_PRIORITY,
                &xTask1);

    /* Create OS Thread for Task2. */
    (void) xTaskCreate((TaskFunction_t) lTask2,
                "Task2",
                512,
                NULL,
                TASK2_PRIORITY,
                &xTask2);

    // Initalize prime number queue to handler type
    // So we can access the queue in both tasks
    prime_queue = xQueueCreate(QUEUE_LEN, sizeof(QUEUE_DATATYPE));
    configASSERT(prime_queue != NULL);
    /* Start RTOS Scheduler. */

    /**********************************************************************
     * Create all Threads for APP Tasks before starting FreeRTOS Scheduler *
     ***********************************************************************/
    vTaskStartScheduler(); /* This function never returns. */

}

/*******************************************************************************
   End of File
 */

