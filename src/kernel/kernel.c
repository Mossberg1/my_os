#include <kernel.h>
#include <kstring.h>
#include <ktypes.h>
#include <console.h>
#include <hal.h>

// https://operating-system-in-1000-lines.vercel.app/en/08-exception

extern char __bss[], __bss_end[], __stack_top[]; // RISCV specific?

void kernel_main(void) 
{
    kmemset(__bss, 0, (size_t) __bss_end - (size_t) __bss); // RISCV specific? 

    kprintf("Hello, World!\n");

    // kernel loop
    for (;;) 
    {
        hal_cpu_idle();
    }
}

// This is RISCV specific, will add a bootloader later.
__attribute__((section(".text.boot")))
__attribute__((naked))
void boot(void) {
    __asm__ __volatile__(
        "mv sp, %[stack_top]\n" // Set the stack pointer
        "j kernel_main\n"       // Jump to the kernel main function
        :
        : [stack_top] "r" (__stack_top) // Pass the stack top address as %[stack_top]
    );
}
