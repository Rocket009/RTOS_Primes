#ifndef _TASKS_H
#define _TASKS_H


#include "definitions.h"
#include "queue.h"

// Task 1 gets higher prioritiy so it can handle inputs 
// also so it does not get starved for processor time from the
// processing task (task 2)
#define TASK1_PRIORITY 3
#define TASK2_PRIORITY 2

#define QUEUE_LEN 10
#define QUEUE_DATATYPE uint32_t

// Queue to transfer prime numbers from task 1 
// to task 2 for processing
// holds the handle for the queue for the static queue
QueueHandle_t prime_queue;

void Task1_Loop(void);
void Task2_Loop(void);

#endif
