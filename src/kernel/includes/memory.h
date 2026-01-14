#pragma once


#include <ktypes.h>


#define PAGE_SIZE 4096
#define HEAP_SIZE (1024 * 1024) // 1MB

void memory_init();
void* kmalloc(size_t size);
void kfree(void* ptr);

