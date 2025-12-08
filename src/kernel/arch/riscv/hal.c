#include <hal.h>
#include <sbi.h>
#include <csr.h>

void riscv_kernel_entry();


void hal_putchar(char ch) 
{
    sbi_call(ch, 0, 0, 0, 0, 0, 0, 1 /* Console Putchar */);
}


void hal_cpu_idle() 
{
    __asm__ __volatile__("wfi");
}


void hal_trap_init() 
{
    WRITE_CSR(stvec, (uint32_t)riscv_kernel_entry);
}
