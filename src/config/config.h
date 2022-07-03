#ifndef CONFIH_H
#define CONFIH_H

#define KERNEL_CODE_SELECTOR 0x08 // from kernel.S
#define KERNEL_DATA_SELECTOR 0x10 // from kernel.S

#define TOTAL_INTERRUPTS 512



/*
Heap Info Base Address  .......
                        .  1  . Heap Info Entry 1
                        ....... 
                        .  1  . Heap Info Entry 2
                        ....... 
                          ... 


Heap Base Address ........
                  . 4096 . Entry 1
                  ........
                  . 4096 . Entry 2
                  ........
                  . 4096 . Entry 3
                  ........
                    ... 
*/

// RAM -- free for use (https://wiki.osdev.org/Memory_Map_(x86))
#define HEAP_BASE_ADDRESS 0x01000000

// 1024 bytes * 1024 = 1048576 (1MB), => 1048576 * 100 = 104857600 (100 MB)
// Kernel requires at least 100MB for heap usage
#define TOTAL_HEAP_SIZE_IN_BYTES 104857600

// Each heap entry is 4096 bytes aligned. For example: malloc(5000), => 8192 bytes allocated (2 entries)
#define HEAP_ENTRY_SIZE_IN_BYTES 4096

// Total heap info entries (104857600/4096 = 25600 entries in total. Each entry 4096 bytes)
#define TOTAL_HEAP_ENTRIES (TOTAL_HEAP_SIZE_IN_BYTES / HEAP_ENTRY_SIZE_IN_BYTES)


//  480.5 KiB avaiable (https://wiki.osdev.org/Memory_Map_(x86))
#define HEAP_INFO_BASE_ADDRESS 0x00007E00

#endif