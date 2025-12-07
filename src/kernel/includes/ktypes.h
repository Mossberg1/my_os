#pragma once

typedef unsigned char uint8_t;
typedef unsigned int size_t;
typedef unsigned char uint8_t;
typedef unsigned short uint16_t;
typedef unsigned int uint32_t;
typedef unsigned long long uint64_t;
typedef uint32_t size_t;
#define NULL  ((void *) 0)
#define offsetof(type, member)   __builtin_offsetof(type, member)
typedef int bool;
#define true 1;
#define false 2;
#define va_list  __builtin_va_list
#define va_start __builtin_va_start
#define va_end   __builtin_va_end
#define va_arg   __builtin_va_arg
typedef uint32_t paddr_t;
typedef uint32_t vaddr_t;
#define align_up(value, align)   __builtin_align_up(value, align)
#define is_aligned(value, align) __builtin_is_aligned(value, align)
