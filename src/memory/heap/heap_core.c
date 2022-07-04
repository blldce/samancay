
#include "heap_core.h"
#include "../memory.h"
#include "../../config/config.h"
#include "../../vga/vga.h"

static int validate_heap_aligment(void(*));
static int validate_heap_info(void(*), void(*), struct heap_info(*));
static uint32_t align_size_to_upper(uint32_t);
static void *process_heap_entries(struct heap(*), uint32_t);
static int get_start_entry(struct heap(*), uint32_t);
static void mark_entries_taken(struct heap(*), int, int);
static void mark_entries_free(struct heap(*), int);

void init_heap(struct heap(*heap), void(*heap_base_addr), struct heap_info(*heap_info))
{
    // zeroed heap struct
    memset(heap, 0, sizeof(struct heap));

    heap->heap_base_addr = heap_base_addr; // set heap_base_addr
    heap->heap_info = heap_info;           // set heap_info

    size_t total_heap_info_entries = sizeof(unsigned char) * heap_info->total_heap_entries;

    // set as "free" at heap_info_base_addr (NOT heap_info struct itself)
    memset(heap_info->heap_info_base_addr, HEAP_INFO_ENTRY_FREE, total_heap_info_entries);
}

void *heap_malloc(struct heap(*heap), size_t size_in_bytes)
{
    size_t new_aligned_size = align_size_to_upper(size_in_bytes);
    uint32_t total_required_heap_entries = new_aligned_size / HEAP_ENTRY_SIZE_IN_BYTES; // we need to find X free entries in heap info
    return process_heap_entries(heap, total_required_heap_entries);
}

/*
Set size to upper alignment
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

// Finds free entries in heap info memory region
static void *process_heap_entries(struct heap(*heap), uint32_t total_required_heap_entries)
{
    void(*return_address) = 0;
    int start_entry_index = get_start_entry(heap, total_required_heap_entries);
    if (start_entry_index < 0)
        goto out;

    // calculate heap address based on : heap base address + (entry index * 4096)
    return_address = heap->heap_base_addr + (start_entry_index * HEAP_ENTRY_SIZE_IN_BYTES);

    // marks entries as taken
    mark_entries_taken(heap, start_entry_index, total_required_heap_entries);
out:
    return return_address;
}

// Get start entry from info entries.
// Iterate through info entries to find required free info entries
// Return heap_info entry index
static int get_start_entry(struct heap(*heap), uint32_t total_required_heap_entries)
{
    struct heap_info(*heap_info) = heap->heap_info;

    int start_index = -1;
    int target = 0;

    size_t index = 0;
    while (index < heap_info->total_heap_entries) // iterate entire entries to find free entries
    {
        int entry_type = heap_info->heap_info_base_addr[index] & 0b1111; // return last 4 bits of entry

        if (entry_type != HEAP_INFO_ENTRY_FREE)
        {
            // reset counters
            start_index = -1;
            target = 0;
            index++;
            continue;
        }

        if (start_index == -1)
            start_index = index;

        target++;

        if (target == total_required_heap_entries)
            break;

        index++;
    }

    if (start_index == -1)
        return -1; // NOT found entries which required

    return start_index;
}

// Set heap info entry as taken
static void mark_entries_taken(struct heap(*heap), int start_entry, int total_required_heap_entries)
{
    int end_entry = (start_entry + total_required_heap_entries) - 1;
    unsigned char entry_taken = HEAP_INFO_ENTRY_TAKEN | HEAP_INFO_ENTRY_IS_FIRST; // 0b01000000 OR 0b01000000 = 0b01000000
    if (total_required_heap_entries > 1)
        entry_taken |= HEAP_INFO_ENTRY_HAS_NEXT; //  0b01000000 OR 0b10000000 = 0b11000000

    int index = 0;
    while (index < end_entry)
    {
        heap->heap_info->heap_info_base_addr[index] = entry_taken;
        entry_taken = HEAP_INFO_ENTRY_TAKEN; // 0b01000000
        if (index != end_entry - 1)
            entry_taken |= HEAP_INFO_ENTRY_HAS_NEXT; // 0b01000000 OR 0b10000000 =  0b11000000
        index++;
    }
}

void heap_free(struct heap(*heap), void(*addr))
{
    int start_entry = (((addr - heap->heap_base_addr)) / HEAP_ENTRY_SIZE_IN_BYTES);
    mark_entries_free(heap, start_entry);
}

static void mark_entries_free(struct heap(*heap), int start_entry)
{
    struct heap_info *heap_info = heap->heap_info;
    int index = start_entry;
    while (index < heap_info->total_heap_entries)
    {
        unsigned char entry = heap_info->heap_info_base_addr[index];
        heap_info->heap_info_base_addr[index] = HEAP_INFO_ENTRY_FREE;
        if (!(entry & HEAP_INFO_ENTRY_HAS_NEXT))
        {
            break;
        }
        index++;
    }
}