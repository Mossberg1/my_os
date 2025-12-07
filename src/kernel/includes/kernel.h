#pragma once

#include <console.h>

__attribute__((noreturn))
static inline void panic(const char* file, int line, const char* fmt, ...) {
    kprintf("PANIC: %s:%d: ", file, line);
    while (1) {
        __asm__ __volatile__("wfi");
    }
}

#define PANIC(fmt, ...) panic(__FILE__, __LINE__, fmt, ##__VA_ARGS__)

struct sbiret {
    long error;
    long value;
};

struct sbiret sbi_call(long arg0, long arg1, long arg2, long arg3, long arg4, long arg5, long fid, long eid);
