#include "kernel.h"
#include "vga/vga.h"
#include "memory/heap/kheap.h"

void kernel_main()
{
    init_vga();

    init_kheap();
    
}
