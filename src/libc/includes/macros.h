#pragma once

#include <stdint.h>

typedef uint32_t paddr_t;
typedef uint32_t vaddr_t;

#define align_up(value, align)   __builtin_align_up(value, align)
#define is_aligned(value, align) __builtin_is_aligned(value, align)