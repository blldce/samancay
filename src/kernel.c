#include "kernel.h"
#include "vga/vga.h"
#include "memory/paging/paging.h"
#include "memory/heap/kernel_heap/kheap.h"


void kernel_main()
{
    init_vga();

    init_kheap();

    println("Samancay Kernel");
}
