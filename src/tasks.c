/*******************************************************************************
  File Name:
    Tasks.c
 *******************************************************************************/

#include <string.h>
#include <math.h>

#include "tasks.h"
#include "definitions.h"


uint32_t primecount = 0;
uint32_t nonprimecount = 0;

QueueHandle_t prime_q_handle = NULL;

// Callback function when the main socket closes
// in order to reset the counters
void reset_counters()
{
    primecount = 0;
    nonprimecount = 0;
    if(prime_q_handle != NULL)
        xQueueReset(prime_q_handle);
}

// Returns first divisor of a passed number n
// Returns 0 as you can't divide by 0, If the number is prime or is 0 or 1
uint32_t find_divisor(uint32_t n)
{
    if (n < 2) 
        // 0 and 1 are not prime but have no proper divisors
        return 0;

    // Try to find a divisor from 2 up to sqrt(n)
    for (uint32_t i = 2; i * i <= n; i++) 
    {
        if (n % i == 0) 
        {
            // Found divisor
            return i;
        }
    }

    // No divisors found => prime
    return 0;
}

// The existing code below is provided as a reference for existing functions you can use
void Task1_Loop (QueueHandle_t prime_number_queue)
{
    // Attempt to read from UART2

    // Assign queue handle to static variable so we can
    // reset the queue when socket disconnects
    prime_q_handle = prime_number_queue;
    uint8_t buffer[sizeof(uint32_t)];
    size_t bytes_read = UART2_Read(buffer, sizeof(buffer));

    if(bytes_read == 0){
        // vTaskDelay(10);
        return;
    }

    // flush UART buffer of any extra data
    while(bytes_read > 0)
        bytes_read = UART2_Read(buffer, sizeof(buffer));

    uint32_t primeNum = 0;
    memcpy(&primeNum, buffer, sizeof(primeNum));
    // Print to console 
    console_print("Input Number: %u\r\n", primeNum);

    // add the prime to the back of the queue (non-blocking)
    BaseType_t result = xQueueSendToBack(prime_number_queue, &primeNum, 0);
    if(result == pdPASS)
    {
        // Write acknowledgment to UART2 as adding to queue was successful
        uint8_t ack = 1;
        size_t bytes_written = UART2_Write(&ack, sizeof(ack));
        while(bytes_written != sizeof(ack))
            bytes_written = UART2_Write(&ack, sizeof(ack));
    }
    else
    {
        // Write acknowledgment to UART2 as adding to queue was not successful
        // as the queue is full
        uint8_t ack = 0;
        size_t bytes_written = UART2_Write(&ack, sizeof(ack));
        while(bytes_written != sizeof(ack))
            bytes_written = UART2_Write(&ack, sizeof(ack));
    }

    vTaskDelay(5 / portTICK_PERIOD_MS);
}

void Task2_Loop (QueueHandle_t prime_number_queue)
{
    uint32_t prime_number;
    // pop prime number from queue waiting indefinitely for a new number
    BaseType_t result = xQueueReceive(prime_number_queue, &prime_number, portMAX_DELAY);
    if(result != pdPASS)
        return;
    uint32_t divisor = find_divisor(prime_number);
    if(divisor > 0)
    {
        // Write divisor to UART3
        nonprimecount++;
        size_t bytes_written = UART3_Write((uint8_t*)&divisor, sizeof(divisor));
        while(bytes_written != sizeof(divisor))
            bytes_written = UART3_Write((uint8_t*)&divisor, sizeof(divisor));
    }
    else
    {
        primecount++;
    }
    console_print("Prime count: %u\r\n", primecount);
    console_print("Non-Prime count: %u\r\n", nonprimecount);
    console_print("Total Number count: %u\r\n", nonprimecount + primecount);
}