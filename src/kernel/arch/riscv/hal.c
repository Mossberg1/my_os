#include <hal.h>
#include <sbi.h>

void hal_putchar(char ch) 
{
    sbi_call(ch, 0, 0, 0, 0, 0, 0, 1 /* Console Putchar */);
}


void hal_cpu_idle() 
{
    __asm__ __volatile__("wfi");
}
