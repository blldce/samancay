#ifndef PAGING_H
#define PAGING_H

#include <stdint.h>
#include <stddef.h>

// Reference (https://wiki.osdev.org/Paging)

// Bit Masks
#define PAGING_CACHE_DISABLED       0b00010000
#define PAGING_WRITE                0b00001000
#define PAGING_ACCESS_FROM_ALL      0b00000100
#define PAGING_IS_WRITABLE          0b00000010
#define PAGING_IS_PRESENT           0b00000001

// Page table
#define TOTAL_ENTRIES_PER_TABLE     1024
#define ENTRY_SIZE_IN_BYTES         4096


struct paging_4gb
{
    uint32_t (*directory_entry);
};

extern struct paging_4gb *init_paging_4gb(uint8_t);
extern uint32_t* get_page_directory(struct paging_4gb(*chunk));
extern void switch_page_table(uint32_t (*));
extern void enable_paging();

#endif