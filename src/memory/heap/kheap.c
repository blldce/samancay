#include "kheap.h"
#include "heap.h"
#include "../../vga/vga.h"
#include "../../config/config.h"

static struct heap k_heap;

static struct heap_info k_heap_info;

void init_kheap()
{
    k_heap_info.heap_info_base_addr = (unsigned char(*))HEAP_INFO_BASE_ADDRESS;
    k_heap_info.total_heap_entries = TOTAL_HEAP_ENTRIES;

    void(*heap_end_addr) = (void(*))(HEAP_BASE_ADDRESS + TOTAL_HEAP_SIZE_IN_BYTES);

    int res = init_heap(&k_heap, (void(*))HEAP_BASE_ADDRESS, heap_end_addr, &k_heap_info);

    if (res < 0)
    {
        panic("Failed to create heap!!!");
    }
}

extern void* kmalloc(size_t size)
{
    return heap_malloc(&k_heap, size);
}