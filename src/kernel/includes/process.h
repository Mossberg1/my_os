#pragma once


#include <ktypes.h>


#define PROCS_MAX     8 // Maximum number of processes
#define PROC_UNUSED   0 // Unused process control structure 
#define PROC_RUNNABLE 1 // Runnable process


// Process Control Block
struct process {         
    int pid;             // Process ID
    int state;           // Process state: PROC_UNUSED or PROC_RUNNABLE
    vaddr_t sp;          // Stack pointer
    uint8_t stack[8192]; // Kernel stack
};


void switch_context(uint32_t* prev_sp, uint32_t* next_sp);

void scheduler_init(void);
struct process* create_process(uint32_t pc);
void yield(void);