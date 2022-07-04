#include "kernel.h"
#include "vga/vga.h"
#include "memory/heap/kheap.h"

void kernel_main()
{
    init_vga();

    init_kheap();
    void (*ptr) = kmalloc(5000);
     if(ptr)
    {

    }
     println("Hop 1");
    void (*ptr2) = kmalloc(500);
    if(ptr2)
    {

    }
     println("Hop 2");
}
