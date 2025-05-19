/*******************************************************************************
  File Name:
    Tasks.c
 *******************************************************************************/

#include <string.h>
#include <math.h>

#include "tasks.h"
#include "definitions.h"


// The existing code below is provided as a reference for existing functions you can use
void Task1_Loop ( void )
{
    // Attempt to read from UART2
    uint8_t buffer[64];
    size_t bytes_read = UART2_Read(buffer, 64);

    if(bytes_read == 0){
        return;
    }

    uint32_t primeNum = 0;
    memcpy(&primeNum, buffer, sizeof(primeNum));

    // Print to console 
    console_print("Input Number: %d\r\n", primeNum);

    // Write acknowledgment to UART2
    uint8_t ack = 1;
    size_t bytes_written = UART2_Write(&ack, sizeof(ack));

    vTaskDelay(10);
}

void Task2_Loop ( void )
{
    // Write to UART3
    uint32_t divisor = 7;
    UART3_Write((uint8_t*)&divisor, sizeof(divisor));
    vTaskDelay(10); 
}