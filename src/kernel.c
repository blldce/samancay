#include "kernel.h"
#include "vga/vga.h"

void kernel_main()
{
    init_vga();

    println("Hi");
}
