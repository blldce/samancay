#ifndef HEAP_CORE_H
#define HEAP_CORE_H

#include <stdint.h>
#include <stddef.h>

/*
Info Entry : 8 bit  | Has_Next | Is_First | 0 | 0 |
Heap Info Base Address  .......
                        .  1  .  Info Entry 1
                        .......
                        .  1  .  Info Entry 2
                        .......
                          ...


Heap Base Address ........
                  . 4096 . Heap Entry 1
                  ........
                  . 4096 . Heap Entry 2
                  ........
                  . 4096 . Heap Entry 3
                  ........
                    ...
*/

// Bit fields of Heap Info
#define HEAP_INFO_ENTRY_FREE 0x00
#define HEAP_INFO_ENTRY_TAKEN 0x01

// Bit Masks of Heap Info
#define HEAP_INFO_ENTRY_HAS_NEXT 0b10000000
#define HEAP_INFO_ENTRY_IS_FIRST 0b01000000

struct heap_info
{
  unsigned char(*heap_info_base_addr);
  size_t total_heap_entries;
};

struct heap
{
  struct heap_info(*heap_info);
  void(*heap_base_addr);
};

extern void init_heap(struct heap(*heap), void(*ptr), struct heap_info(*heap_info));
extern void *heap_malloc(struct heap(*), size_t);
extern void heap_free(struct heap(*), void(*ptr));
#endif