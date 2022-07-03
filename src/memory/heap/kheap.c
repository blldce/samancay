#include "kheap.h"
#include "heap.h"
#include "../../vga/vga.h"
#include "../../config/config.h"

static struct heap kernel_heap;

static struct heap_info kernel_heap_info;

void init_kheap()
{
    kernel_heap_info.heap_info_base_addr = (unsigned char(*))HEAP_INFO_BUFFER_BASE_ADDRESS;
    kernel_heap_info.total_entries = TOTAL_HEAP_ENTRIES;

    void(*heap_end_addr) = (void(*))(HEAP_BASE_ADDRESS + TOTAL_HEAP_SIZE_IN_BYTES);

    int res = init_heap(&kernel_heap, (void(*))HEAP_BASE_ADDRESS, heap_end_addr, &kernel_heap_info);

    if (res < 0)
    {
        panic("Failed to create heap!!!");
    }
}