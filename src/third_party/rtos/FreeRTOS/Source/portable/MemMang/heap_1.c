/*
 * FreeRTOS Kernel V11.1.0
 * Copyright (C) 2021 Amazon.com, Inc. or its affiliates. All Rights Reserved.
 *
 * SPDX-License-Identifier: MIT
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
 * https://www.FreeRTOS.org
 * https://github.com/FreeRTOS
 *
 */


/*
 * The simplest possible implementation of pvPortMalloc().  Note that this
 * implementation does NOT allow allocated memory to be freed again.
 *
 * See heap_2.c, heap_3.c and heap_4.c for alternative implementations, and the
 * memory management pages of https://www.FreeRTOS.org for more information.
 */
#include <stdlib.h>
#include "definitions.h"

/* Defining MPU_WRAPPERS_INCLUDED_FROM_API_FILE prevents task.h from redefining
 * all the API functions to use the MPU wrappers.  That should only be done when
 * task.h is included from an application file. */
#define MPU_WRAPPERS_INCLUDED_FROM_API_FILE

#include "FreeRTOS.h"
#include "task.h"

#undef MPU_WRAPPERS_INCLUDED_FROM_API_FILE

#if ( configSUPPORT_DYNAMIC_ALLOCATION == 0 )
    #error This file must not be used if configSUPPORT_DYNAMIC_ALLOCATION is 0
#endif

/* A few bytes might be lost to byte aligning the heap start address. */
#define configADJUSTED_HEAP_SIZE    ( configTOTAL_HEAP_SIZE - portBYTE_ALIGNMENT )

/* Allocate the memory for the heap. */
#if ( configAPPLICATION_ALLOCATED_HEAP == 1 )

/* The application writer has already defined the array used for the RTOS
* heap - probably so it can be placed in a special segment or address. */

#ifndef POSIX
    uint8_t ucHeap[configTOTAL_HEAP_SIZE] __attribute__((section(".heap")));
#else
    uint8_t ucHeap[configTOTAL_HEAP_SIZE];
#endif


    // extern uint8_t ucHeap[ configTOTAL_HEAP_SIZE ];
#else
    static uint8_t ucHeap[ configTOTAL_HEAP_SIZE ];
#endif /* configAPPLICATION_ALLOCATED_HEAP */

/* Index into the ucHeap array. */
static size_t xNextFreeByte = ( size_t ) 0U;

/*-----------------------------------------------------------*/

void * pvPortMalloc( size_t xWantedSize )
{

    void * pvReturn = NULL;
    static uint8_t * pucAlignedHeap = NULL;
    pinVal(0x01);


    /* Ensure that blocks are always aligned. */
    #if ( portBYTE_ALIGNMENT != 1 )
    {
            pinVal(0x02);

        if( xWantedSize & portBYTE_ALIGNMENT_MASK )
        {
                pinVal(0x03);

            /* Byte alignment required. Check for overflow. */
            if( ( xWantedSize + ( portBYTE_ALIGNMENT - ( xWantedSize & portBYTE_ALIGNMENT_MASK ) ) ) > xWantedSize )
            {
                    pinVal(0x04);

                xWantedSize += ( portBYTE_ALIGNMENT - ( xWantedSize & portBYTE_ALIGNMENT_MASK ) );
            }
            else

            {
                    pinVal(0x05);

                xWantedSize = 0;
            }
        }
    }
    #endif /* if ( portBYTE_ALIGNMENT != 1 ) */

    vTaskSuspendAll();
    {

            pinVal(0x06);

        if( pucAlignedHeap == NULL )
        {
                pinVal(0x07);

            /* Ensure the heap starts on a correctly aligned boundary. */
            pucAlignedHeap = ( uint8_t * ) ( ( ( portPOINTER_SIZE_TYPE ) & ucHeap[ portBYTE_ALIGNMENT - 1 ] ) & ( ~( ( portPOINTER_SIZE_TYPE ) portBYTE_ALIGNMENT_MASK ) ) );
        }
            // pinVal(0xFF);
            // pinVal(0xFF);
            
            // pinVal((uint8_t)0);
            // pinVal((uint8_t)(xWantedSize > 0));
            // pinVal((uint8_t)( xNextFreeByte + xWantedSize ) < configADJUSTED_HEAP_SIZE);
            // pinVal((uint8_t)(( xNextFreeByte + xWantedSize ) > xNextFreeByte ) );
            // pinVal((uint8_t)0);

            // pinVal(0xFF);


            pinVal(0xFF);
            uint8_t byte3 = (xNextFreeByte >> 0) & 0xFF;  // Least significant byte
            uint8_t byte2 = (xNextFreeByte >> 8) & 0xFF;
            uint8_t byte1 = (xNextFreeByte >> 16) & 0xFF;
            uint8_t byte0 = (xNextFreeByte >> 24) & 0xFF; // Most significant byte

            // Send each byte sequentially
            pinVal(byte0);
            pinVal(byte1);
            pinVal(byte2);
            pinVal(byte3);
            pinVal(0xFF);

            pinVal(0x0);
            byte3 = (xWantedSize >> 0) & 0xFF;  // Least significant byte
            byte2 = (xWantedSize >> 8) & 0xFF;
            byte1 = (xWantedSize >> 16) & 0xFF;
            byte0 = (xWantedSize >> 24) & 0xFF; // Most significant byte

            // Send each byte sequentially
            pinVal(byte0);
            pinVal(byte1);
            pinVal(byte2);
            pinVal(byte3);
            pinVal(0x0);

        /* Check there is enough room left for the allocation and. */
        if( ( xWantedSize > 0 ) &&                                /* valid size */
            ( ( xNextFreeByte + xWantedSize ) < configADJUSTED_HEAP_SIZE ) &&
            ( ( xNextFreeByte + xWantedSize ) > xNextFreeByte ) ) /* Check for overflow. */
        {
            // NOT GOING HERE 

                pinVal(0x09);

            /* Return the next free byte then increment the index past this
             * block. */


            pvReturn = pucAlignedHeap + xNextFreeByte;
            xNextFreeByte += xWantedSize;
        }
         pinVal(0x10);

        traceMALLOC( pvReturn, xWantedSize );
                 pinVal(0x11);

    }
    ( void ) xTaskResumeAll();

             pinVal(0x12);


    #if ( configUSE_MALLOC_FAILED_HOOK == 1 )
    {
        if( pvReturn == NULL )
        {
            vApplicationMallocFailedHook();
        }
    }
    #endif

    return pvReturn;
}
/*-----------------------------------------------------------*/

void vPortFree( void * pv )
{
    /* Memory cannot be freed using this scheme.  See heap_2.c, heap_3.c and
     * heap_4.c for alternative implementations, and the memory management pages of
     * https://www.FreeRTOS.org for more information. */
    ( void ) pv;

    /* Force an assert as it is invalid to call this function. */
    configASSERT( pv == NULL );
}
/*-----------------------------------------------------------*/

void vPortInitialiseBlocks( void )
{
    /* Only required when static memory is not cleared. */
    xNextFreeByte = ( size_t ) 0;
}
/*-----------------------------------------------------------*/

size_t xPortGetFreeHeapSize( void )
{
    return( configADJUSTED_HEAP_SIZE - xNextFreeByte );
}

/*-----------------------------------------------------------*/

/*
 * Reset the state in this file. This state is normally initialized at start up.
 * This function must be called by the application before restarting the
 * scheduler.
 */
void vPortHeapResetState( void )
{
    xNextFreeByte = ( size_t ) 0U;
}
/*-----------------------------------------------------------*/
