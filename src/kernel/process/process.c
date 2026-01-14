#include <hal.h>
#include <process.h>
#include <kernel.h>


struct process procs[PROCS_MAX]; // All PCBs

struct process* curr_proc;
struct process* idle_proc;


static void idle(void) 
{
    for (;;) 
    {
        hal_cpu_idle();
    }
} 


void scheduler_init(void) 
{
    idle_proc = create_process((uint32_t)idle);
    idle_proc->pid = -1;
    curr_proc = idle_proc;
}


struct process* create_process(uint32_t pc) 
{
    // Find a unused PCB
    struct process *proc = NULL;
    int i;
    for (i = 0; i < PROCS_MAX; i++) 
    {
        if (procs[i].state == PROC_UNUSED) 
        {
            proc = &procs[i];
            break;
        }
    }

    if (!proc) 
    {
        PANIC("No free process slots");
    }


    uint32_t* sp = (uint32_t*)&proc->stack[sizeof(proc->stack)];

    // TODO: RISCV specific code, should be moved out to arch/riscv
    *--sp = 0;                      // s11
    *--sp = 0;                      // s10
    *--sp = 0;                      // s9
    *--sp = 0;                      // s8
    *--sp = 0;                      // s7
    *--sp = 0;                      // s6
    *--sp = 0;                      // s5
    *--sp = 0;                      // s4
    *--sp = 0;                      // s3
    *--sp = 0;                      // s2
    *--sp = 0;                      // s1
    *--sp = 0;                      // s0
    *--sp = (uint32_t) pc;          // ra

    // Initialize 
    proc->pid = i+1;
    proc->state = PROC_RUNNABLE;
    proc->sp = (uint32_t)sp;

    return proc;
}


void yield(void) 
{
    struct process* next = idle_proc;
    for (int i = 0; i < PROCS_MAX; i++) 
    {
        struct process* proc = &procs[(curr_proc->pid + i) % PROCS_MAX];
        if (proc->state == PROC_RUNNABLE && proc->pid > 0) 
        {
            next = proc;
            break;
        }
    }

    if (next == curr_proc) 
    {
        return;
    }

    // TODO: RISCV specific move to arch/riscv later
    __asm__ __volatile__(
        "csrw sscratch, %[sscratch]\n"
        :
        : [sscratch] "r" ((uint32_t) &next->stack[sizeof(next->stack)])
    );

    struct process* prev = curr_proc;
    curr_proc = next;
    switch_context(&prev->sp, &next->sp);
}

