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


void Task1_Loop(QueueHandle_t prime_number_queue);
void Task2_Loop(QueueHandle_t prime_number_queue);

#endif
