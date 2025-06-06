
#ifndef FREERTOS_CONFIG_POSIX_H
#define FREERTOS_CONFIG_POSIX_H

#include <stdio.h>
#include <limits.h>
#include <pthread.h>


/* MISRA C-2012 Rule 3.1, 5.4 deviated below. Deviation record ID -  
   H3_MISRAC_2012_R_3_1_DR_1 & H3_MISRAC_2012_R_5_4_DR_1*/
/*
 * FreeRTOS Kernel V10.4.0
 * Copyright (C) 2019 Amazon.com, Inc. or its affiliates.  All Rights Reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of
 * this software and associated documentation files (the "Software"), to deal in
 * the Software without restriction, including without limitation the rights to
 * use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
 * the Software, and to permit persons to whom the Software is furnished to do so,
 * subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
 * FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
 * COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
 * IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 * http://www.FreeRTOS.org
 * http://aws.amazon.com/freertos
 *
 * 1 tab == 4 spaces!
 */
 
/*-----------------------------------------------------------
 * Application specific definitions.
 *
 * Parameters adjusted for RTOS posix simulator 
 *
 * THESE PARAMETERS ARE DESCRIBED WITHIN THE 'CONFIGURATION' SECTION OF THE
 * FreeRTOS API DOCUMENTATION AVAILABLE ON THE FreeRTOS.org WEB SITE.
 *
 * See http://www.freertos.org/a00110.html
 *----------------------------------------------------------*/

#define SYS_INT_IsEnabled                       0

#define configUSE_RECURSIVE_MUTEXES             1
#define configUSE_PORT_OPTIMISED_TASK_SELECTION 0

#define configUSE_PREEMPTION                       1
#define configUSE_PORT_OPTIMISED_TASK_SELECTION    0
#define configUSE_IDLE_HOOK                        1
#define configUSE_TICK_HOOK                        1
#define configUSE_DAEMON_TASK_STARTUP_HOOK         0
#define configTICK_RATE_HZ                         ( 1000 )                  /* In this non-real time simulated environment the tick frequency has to be at least a multiple of the Win32 tick frequency, and therefore very slow. */
#define configMINIMAL_STACK_SIZE                   ( ( unsigned short ) 16384 ) /* The stack size being passed is equal to the minimum stack size needed by pthread_create(). */
#define configTOTAL_HEAP_SIZE                      ( ( size_t ) ( 65 * 2048 ) )
#define configMAX_TASK_NAME_LEN                    ( 12 )
// #define configUSE_TRACE_FACILITY                   1
#define configUSE_16_BIT_TICKS                     0
#define configIDLE_SHOULD_YIELD                    1
#define configUSE_MUTEXES                          1
#define configCHECK_FOR_STACK_OVERFLOW             0
#define configUSE_RECURSIVE_MUTEXES                1
#define configQUEUE_REGISTRY_SIZE                  20
#define configUSE_APPLICATION_TASK_TAG             1
#define configUSE_COUNTING_SEMAPHORES              1
#define configUSE_ALTERNATIVE_API                  0
#define configUSE_QUEUE_SETS                       1
#define configUSE_TASK_NOTIFICATIONS               1

/* The following 2  memory allocation schemes are possible for this demo:
 *
 * 1. Dynamic Only.
 *    #define configSUPPORT_STATIC_ALLOCATION  0
 *    #define configSUPPORT_DYNAMIC_ALLOCATION 1
 *
 * 2. Static and Dynamic.
 *    #define configSUPPORT_STATIC_ALLOCATION  1
 *    #define configSUPPORT_DYNAMIC_ALLOCATION 1
 *
 * Static only configuration is not possible for this demo as it utilizes
 * dynamic allocation.
 */
#define configSUPPORT_STATIC_ALLOCATION            0
#define configSUPPORT_DYNAMIC_ALLOCATION           1

#define configRECORD_STACK_HIGH_ADDRESS            1

/* Software timer related configuration options.  The maximum possible task
 * priority is configMAX_PRIORITIES - 1.  The priority of the timer task is
 * deliberately set higher to ensure it is correctly capped back to
 * configMAX_PRIORITIES - 1. */
#define configUSE_TIMERS                           1
#define configTIMER_TASK_PRIORITY                  ( configMAX_PRIORITIES - 1 )
#define configTIMER_QUEUE_LENGTH                   20
#define configTIMER_TASK_STACK_DEPTH               ( configMINIMAL_STACK_SIZE * 2 )

#define configMAX_PRIORITIES                       ( 7 )

/* Run time stats gathering configuration options. */
unsigned long ulGetRunTimeCounterValue( void ); /* Prototype of function that returns run time counter. */
void vConfigureTimerForRunTimeStats( void );    /* Prototype of function that initialises the run time counter. */
#define configGENERATE_RUN_TIME_STATS             1

/* Co-routine related configuration options. */
#define configUSE_CO_ROUTINES                     0
#define configMAX_CO_ROUTINE_PRIORITIES           ( 2 )

/* This demo can use of one or more example stats formatting functions.  These
 * format the raw data provided by the uxTaskGetSystemState() function in to human
 * readable ASCII form.  See the notes in the implementation of vTaskList() within
 * FreeRTOS/Source/tasks.c for limitations. */
#define configUSE_STATS_FORMATTING_FUNCTIONS      0

/* Enables the test whereby a stack larger than the total heap size is
 * requested. */
#define configSTACK_DEPTH_TYPE                    uint32_t

/* Set the following definitions to 1 to include the API function, or zero
 * to exclude the API function.  In most cases the linker will remove unused
 * functions anyway. */
#define INCLUDE_vTaskPrioritySet                  1
#define INCLUDE_uxTaskPriorityGet                 1
#define INCLUDE_vTaskDelete                       1
#define INCLUDE_vTaskCleanUpResources             0
#define INCLUDE_vTaskSuspend                      1
#define INCLUDE_vTaskDelayUntil                   1
#define INCLUDE_vTaskDelay                        1
#define INCLUDE_uxTaskGetStackHighWaterMark       1
#define INCLUDE_uxTaskGetStackHighWaterMark2      1
#define INCLUDE_xTaskGetSchedulerState            1
#define INCLUDE_xTimerGetTimerDaemonTaskHandle    1
#define INCLUDE_xTaskGetIdleTaskHandle            1
#define INCLUDE_xTaskGetHandle                    1
#define INCLUDE_eTaskGetState                     1
#define INCLUDE_xSemaphoreGetMutexHolder          1
#define INCLUDE_xTimerPendFunctionCall            1
#define INCLUDE_xTaskAbortDelay                   1

#define configINCLUDE_MESSAGE_BUFFER_AMP_DEMO     0
#if ( configINCLUDE_MESSAGE_BUFFER_AMP_DEMO == 1 )
    extern void vGenerateCoreBInterrupt( void * xUpdatedMessageBuffer );
    #define sbSEND_COMPLETED( pxStreamBuffer )    vGenerateCoreBInterrupt( pxStreamBuffer )
#endif /* configINCLUDE_MESSAGE_BUFFER_AMP_DEMO */

extern void vAssertCalled( const char * const pcFileName,
                           unsigned long ulLine );

#define configASSERT(x) if ((x) == 0) { \
    printf("ASSERTION FAILED at %s:%d\n", __FILE__, __LINE__); \
    while(1); \
}

#endif

