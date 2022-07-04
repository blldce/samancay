#ifndef KHEAP_H
#define KHEAP_H

#include <stdint.h>
#include <stddef.h>

extern void init_kheap();
extern void *kmalloc(size_t);
extern void *kzalloc(size_t);
extern void kfree(void(*));

#endif