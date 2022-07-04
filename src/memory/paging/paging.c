#include "paging.h"
#include "../heap/kernel_heap/kheap.h"

struct paging_4gb *new_paging_4gb(uint8_t flags)
{
    // allocate a buffer (1024) for directory entry
    uint32_t(*directory_buffer) = kzalloc(sizeof(uint32_t) * TOTAL_ENTRIES_PER_TABLE);

    // page table base address
    int page_table_offset = 0;

    // initialize buffer
    int directory_entry_index = 0;
    while (directory_entry_index < TOTAL_ENTRIES_PER_TABLE)
    {
        // allocate a buffer (1024) for page table entry
        uint32_t(*page_table_entry_buffer) = kzalloc(sizeof(uint32_t) * TOTAL_ENTRIES_PER_TABLE);
        // apply

        int page_table_entry_index = 0;
        // page table initialization
        while (page_table_entry_index < TOTAL_ENTRIES_PER_TABLE)
        {
            // page table entry address mapping to physical address 
            // Example : Physical address = (0 +(0 * 4096)) = 0, (0 +(1 * 4096)) = 4096 ... 
            page_table_entry_buffer[page_table_entry_index] = (page_table_offset + (page_table_entry_index * ENTRY_SIZE_IN_BYTES)) | flags;
            page_table_entry_index++;
        }
        // move next page table base address
        page_table_offset += (TOTAL_ENTRIES_PER_TABLE * ENTRY_SIZE_IN_BYTES);
        directory_entry_index++;
    }
}