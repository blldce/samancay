#include "kernel.h"
#include "vga/vga.h"
#include "idt/idt.h"

void kernel_main()
{
    init_vga();

    println("Hi");
    println("Hola, \ncoma estas?");
}
