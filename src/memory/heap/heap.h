#ifndef HEAP_H
#define HEAP_H

#include <stdint.h>
#include <stddef.h>
#include "heap.h"


#define HEAP_BLOCK_ARRAY_ENTRY_FREE  0x00
#define HEAP_BLOCK_ARRAY_ENTRY_TAKEN 0x01

// Bit Masks
#define HEAP_BLOCK_HAS_NEXT 0b10000000
#define HEAP_BLOCK_IS_FREE  0b01000000

struct heap_table
{
    unsigned char (*entry_array_base_addr);
    size_t total_entries;
};





#endif