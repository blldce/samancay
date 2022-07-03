#include <stdbool.h>
#include "heap.h"
#include "../memory.h"
#include "../../config/config.h"
#include "../../vga/vga.h"

static int validate_heap_aligment(void(*base_addr));
static int validate_heap_info(void(*base_addr), void(*end_addr), struct heap_info(*heap_info));



int init_heap(struct heap(*heap), void(*base_addr), void(*heap_end_addr), struct heap_info(*heap_info))
{
    int res = 0;
    if (!validate_heap_aligment(base_addr) || !validate_heap_aligment(heap_end_addr)) // check base address is 4094 bytes aligment
    {
        res = -1;
        goto out;
    }
    memset(heap, 0, sizeof(struct heap)); // zeroed heap struct address
    heap->heap_base_addr = base_addr;
    heap->heap_info = heap_info;

    res = validate_heap_info(base_addr, heap_end_addr, heap_info);
    if (res < 0)
        goto out;

out:
    return res;
}

// check address is 4096 bytes aligment
static int validate_heap_aligment(void(*base_addr))
{
    return (*((unsigned int(*))base_addr) % HEAP_ENTRY_SIZE_IN_BYTES) == 0;
}

static int validate_heap_info(void(*base_addr), void(*end_addr), struct heap_info(*heap_info))
{
    int res = 0;
    size_t entry_size = (size_t)(end_addr - base_addr);
    size_t total_entries = entry_size / HEAP_ENTRY_SIZE_IN_BYTES;

    if (heap_info->total_entries != total_entries)
    {
        res = -1;
        goto out;
    }

out:
    return res;
}
