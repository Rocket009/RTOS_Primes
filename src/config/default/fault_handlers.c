/*******************************************************************************
* Copyright (C) 2019 Microchip Technology Inc. and its subsidiaries.
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
#include <stdint.h>
#include <stdbool.h>

#include "system/reset/sys_reset.h"
#include "logs/event_logger.h"

#include "definitions.h"

#define PIOB_REGS   ((pio_group_registers_t*)(&(PIO_REGS->PIO_GROUP[1])))


void undefined_instruction_irq_handler (uint32_t *regs);
void software_interrupt_irq_handler(void);
void data_abort_irq_handler(uint32_t *regs);
void prefetch_abort_irq_handler(uint32_t *regs);

uint32_t regs_empty[18] = {0};


void __attribute((weak, noreturn)) undefined_instruction_irq_handler(uint32_t *regs) {

    // Prevent function return warning
    while(1){
    }
}

void __attribute((weak, noreturn)) software_interrupt_irq_handler(void) {
    // Prevent function return warning
    while(1){
    }
}

void __attribute((weak, noreturn)) data_abort_irq_handler(uint32_t *regs) {

    // Prevent function return warning
    while(1){
    }
}

void __attribute((weak, noreturn)) prefetch_abort_irq_handler(uint32_t *regs) {

    // Prevent function return warning
    while(1){
    }
}

