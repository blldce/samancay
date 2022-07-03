#ifndef HEAP_H
#define HEAP_H

#include <stdint.h>
#include <stddef.h>
#include "heap.h"

// Bit fields of Heap Info
#define HEAP_INFO_ENTRY_FREE 0x00
#define HEAP_INFO_ENTRY_TAKEN 0x01

// Bit Masks of Heap Info
#define HEAP_INFO_ENTRY_HAS_NEXT 0b10000000
#define HEAP_INFO_ENTRY_IS_FREE 0b01000000

struct heap_info
{
    unsigned char(*heap_info_base_addr);
    size_t total_entries;
};

struct heap
{
    struct heap_info(*heap_info);
    void(*heap_base_addr);
};

#endif