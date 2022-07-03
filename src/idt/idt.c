#include "idt.h"
#include "memory.h"
#include "../vga/vga.h"
#include "../config/config.h"

static struct idt_desc idt_descriptors[TOTAL_INTERRUPTS];
static struct idtr_desc idtr_descriptor;

static void idt_set(int, void(*));
static void idt_zero();

extern void idt_load(struct idtr_desc(*)); // from idt.S

static void idt_zero()
{
    println("Divide by zero error");
}

// init idt_descriptors memory
void init_idt()
{
    memset(idt_descriptors, 0, sizeof(idt_descriptors));
    idtr_descriptor.base = *(uint32_t(*)) idt_descriptors;
    idtr_descriptor.limit = sizeof(idt_descriptors) - 1;

    idt_set(0, idt_zero);

    // load interrupt descriptor table
    idt_load(&idtr_descriptor);
}

// from https://wiki.osdev.org/Interrupt_Descriptor_Table
static void idt_set(int interrupt_no, void(*address))
{
    struct idt_desc(*desc) = &idt_descriptors[interrupt_no];
    desc->offset_1 = *((uint32_t(*))address) & 0x0000ffff;
    desc->selector = KERNEL_CODE_SELECTOR;
    desc->zero = 0x00;
    desc->type_attr = 0xEE;
    desc->offset_2 = *((uint32_t(*))address) >> 16;
}