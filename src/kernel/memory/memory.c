#include <memory.h>
#include <ktypes.h>
#include <kernel.h>
#include <kstring.h>


typedef struct block {
    size_t size;
    int free;
    struct block *next;
} block_t;


static block_t *free_list = NULL;
static uint8_t heap[HEAP_SIZE] __attribute__((aligned(PAGE_SIZE)));


void memory_init() 
{
    free_list = (block_t*)heap;
    free_list->size = HEAP_SIZE - sizeof(block_t);
    free_list->free = 1;
    free_list-> next = NULL;
}


void* kmalloc(size_t size) 
{
    if (size == 0) return NULL;

    // Align to 8 bytes
    size = (size + 7) & ~7;

    block_t *curr = free_list;
    while (curr != NULL) 
    {
        if (curr->free && curr->size >= size) // There is enough space to allocate the memory.
        {
            if (curr->size > size + sizeof(block_t) + 8) // Can block be split? 
            {
                // Split block
                block_t* new_block = (block_t*)((uint8_t*)curr + sizeof(block_t) + size);
                new_block->size = curr->size - size - sizeof(block_t);
                new_block->free = 1;
                new_block->next = curr->next;

                curr->size = size;
                curr->next = new_block;
            }
            
            curr->free = 0;
            return (void*)((uint8_t*)curr + sizeof(block_t));
        }
        curr = curr->next;
    }
    return NULL; // No memory
}


void kfree(void* ptr) 
{
    if (ptr == NULL) return;

    block_t *block = (block_t*)((uint8_t*)ptr - sizeof(block_t));
    block->free = 1;

    block_t *curr = free_list;
    while (curr != NULL) 
    {
        if (curr->free && curr->next && curr->next->free) 
        {
            curr->size += sizeof(block_t) + curr->next->size;
            curr->next = curr->next->next;
        }
        curr = curr->next;
    }
}