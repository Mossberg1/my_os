#pragma once

#include <stdint.h>

typedef uint32_t size_t;

#define NULL  ((void *) 0)
#define offsetof(type, member)   __builtin_offsetof(type, member)