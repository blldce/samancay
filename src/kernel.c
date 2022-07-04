#include "kernel.h"
#include "vga/vga.h"
#include "memory/heap/kernel_heap/kheap.h"

void kernel_main()
{
    init_vga();

    init_kheap();

    void (* ptr)  = kmalloc(80000);
    if(ptr)
    {}
    println("hop 1");


    void (* ptr2)  = kmalloc(5000);
    if(ptr2)
    {}
    println("hop 2");
}
