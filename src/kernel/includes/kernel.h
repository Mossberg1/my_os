#pragma once

#include <console.h>
#include <hal.h>

__attribute__((noreturn))
static inline void panic(const char* file, int line, const char* fmt, ...) 
{
    kprintf("PANIC: %s:%d: ", file, line);
    while (1) 
    {
        hal_cpu_idle();
    }
}

#define PANIC(fmt, ...) panic(__FILE__, __LINE__, fmt, ##__VA_ARGS__)

