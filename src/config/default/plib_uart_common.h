/*******************************************************************************
  UART PLIB

  Company:
    Microchip Technology Inc.

  File Name:
    plib_uart.h

  Summary:
    UART PLIB Global Header File

  Description:
    None

*******************************************************************************/

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

#ifndef PLIB_UART_COMMON_H
#define PLIB_UART_COMMON_H

#include <stddef.h>
#include <stdbool.h>
#include <stdint.h>
#include "device.h" //For UART_*_Msk

// DOM-IGNORE-BEGIN
#ifdef __cplusplus  // Provide C++ Compatibility

    extern "C" {

#endif
// DOM-IGNORE-END

// *****************************************************************************
// *****************************************************************************
// Section: Interface
// *****************************************************************************
// *****************************************************************************


#define     UART_ERROR_NONE         (0U)
#define     UART_ERROR_OVERRUN      (UART_SR_OVRE_Msk)
#define     UART_ERROR_PARITY       (UART_SR_PARE_Msk)
#define     UART_ERROR_FRAMING      (UART_SR_FRAME_Msk)

typedef uint32_t UART_ERROR;


#define    UART_PARITY_NONE      (UART_MR_PAR_NO)

#define    UART_PARITY_ODD       (UART_MR_PAR_ODD)

#define    UART_PARITY_EVEN      (UART_MR_PAR_EVEN)

#define    UART_PARITY_MARK      (UART_MR_PAR_MARK)

#define    UART_PARITY_SPACE     (UART_MR_PAR_SPACE)

/* Force the compiler to reserve 32-bit space for each enum */
#define    UART_PARITY_INVALID   (0xFFFFFFFFU)

typedef uint32_t UART_PARITY;

typedef struct
{
    uint32_t baudRate;

    UART_PARITY parity;

} UART_SERIAL_SETUP;

typedef void (* UART_CALLBACK)( uintptr_t context );


// *****************************************************************************
// *****************************************************************************
// Section: Local: **** Do Not Use ****
// *****************************************************************************
// *****************************************************************************

typedef struct
{
    uint8_t *               txBuffer;
    size_t                  txSize;
    size_t                  txProcessedSize;
    UART_CALLBACK           txCallback;
    uintptr_t               txContext;
    bool                    txBusyStatus;

    uint8_t *               rxBuffer;
    size_t                  rxSize;
    size_t                  rxProcessedSize;
    UART_CALLBACK           rxCallback;
    uintptr_t               rxContext;
    bool                    rxBusyStatus;

} UART_OBJECT ;

typedef enum
{
    /* Threshold number of bytes are available in the receive ring buffer */
    UART_EVENT_READ_THRESHOLD_REACHED = 0,

    /* Receive ring buffer is full. Application must read the data out to avoid missing data on the next RX interrupt. */
    UART_EVENT_READ_BUFFER_FULL,

    /* USART error. Application must call the UARTx_ErrorGet API to get the type of error and clear the error. */
    UART_EVENT_READ_ERROR,

    /* Threshold number of free space is available in the transmit ring buffer */
    UART_EVENT_WRITE_THRESHOLD_REACHED,
}UART_EVENT;

typedef void (* UART_RING_BUFFER_CALLBACK)(UART_EVENT event, uintptr_t context );


// *****************************************************************************
// *****************************************************************************
// Section: Local: **** Do Not Use ****
// *****************************************************************************
// *****************************************************************************

typedef struct
{
    UART_RING_BUFFER_CALLBACK                           wrCallback;

    uintptr_t                               			wrContext;

    uint32_t                       			            wrInIndex;

    uint32_t                       			            wrOutIndex;

    bool                                    			isWrNotificationEnabled;

    uint32_t                                			wrThreshold;

    bool                                    			isWrNotifyPersistently;

    UART_RING_BUFFER_CALLBACK                  			rdCallback;

    uintptr_t                               			rdContext;

    uint32_t                       			            rdInIndex;

    uint32_t                       			            rdOutIndex;

    bool                                    			isRdNotificationEnabled;

    uint32_t                                			rdThreshold;

    bool                                    			isRdNotifyPersistently;

} UART_RING_BUFFER_OBJECT;

// DOM-IGNORE-BEGIN
#ifdef __cplusplus  // Provide C++ Compatibility

    }

#endif
// DOM-IGNORE-END
#endif // PLIB_UART_COMMON_H
