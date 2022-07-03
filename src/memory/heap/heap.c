#include <stdbool.h>
#include "heap.h"
#include "../memory.h"
#include "../../config/config.h"
#include "../../vga/vga.h"

static int validate_heap_aligment(void(*base_addr));
static int validate_heap_info(void(*base_addr), void(*end_addr), struct heap_info(*heap_info));
static uint32_t align_size_to_upper(uint32_t);

int init_heap(struct heap(*heap), void(*heap_base_addr), void(*heap_end_addr), struct heap_info(*heap_info))
{
    int res = 0;
    if (!validate_heap_aligment(heap_base_addr) || !validate_heap_aligment(heap_end_addr))
    {
        res = -1;
        goto out;
    }
    // zeroed heap struct base address
    memset(heap, 0, sizeof(struct heap));

    heap->heap_base_addr = heap_base_addr;
    heap->heap_info = heap_info;

    size_t total_heap_info_entries = sizeof(unsigned char) * heap_info->total_heap_entries;

    // zeroed heap info base address
    memset(heap_info->heap_info_base_addr, HEAP_INFO_ENTRY_FREE, total_heap_info_entries);

out:
    return res;
}

// Check address is 4096 bytes aligment
static int validate_heap_aligment(void(*base_addr))
{
    return (*((unsigned int(*))base_addr) % HEAP_ENTRY_SIZE_IN_BYTES) == 0;
}

void *heap_malloc(struct heap(*heap),size_t size_in_bytes)
{
    size_t aligned_size = align_size_to_upper(size_in_bytes);
    uint32_t total_entries = aligned_size / HEAP_ENTRY_SIZE_IN_BYTES; // we need to find X free entries in heap info
    return 0;
}

void heap_free(struct heap(*heap),void(*ptr))
{
}

/*
50   => upper to 4096
4097 => upper to 8192
*/
static uint32_t align_size_to_upper(uint32_t size_in_bytes)
{
    if (size_in_bytes <= HEAP_ENTRY_SIZE_IN_BYTES)
        return HEAP_ENTRY_SIZE_IN_BYTES;

    int remain_bytes = size_in_bytes % HEAP_ENTRY_SIZE_IN_BYTES;
    size_in_bytes -= remain_bytes;             // lower aligment
    size_in_bytes += HEAP_ENTRY_SIZE_IN_BYTES; // add 1 more entry (Caution : FRAGMENTATION!!!)
    return size_in_bytes;
}