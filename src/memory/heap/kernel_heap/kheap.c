#include "kheap.h"
#include "../heap_core.h"
#include "../../../memory/memory.h"
#include "../../../config/config.h"

static struct heap k_heap;
static struct heap_info k_heap_info;

// Set base addresses both heap & heap info
void init_kheap()
{
    k_heap_info.heap_info_base_addr = (unsigned char(*))HEAP_INFO_BASE_ADDRESS;
    k_heap_info.total_heap_entries = TOTAL_HEAP_ENTRIES;
    init_heap(&k_heap, (void(*))HEAP_BASE_ADDRESS, &k_heap_info);
}

void *kmalloc(size_t size)
{
    return heap_malloc(&k_heap, size);
}

void *kzalloc(size_t size)
{
    void(*ptr) = kmalloc(size);
    if (!ptr)
        return 0;
    memset(ptr, 0x00, size);
    return ptr;
}

void kfree(void(*ptr))
{
    heap_free(&k_heap, ptr);
}