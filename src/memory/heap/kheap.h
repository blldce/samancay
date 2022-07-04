#ifndef KHEAP_H
#define KHEAP_H

#include <stdint.h>
#include <stddef.h>


extern void init_kheap();
extern void *kmalloc(size_t);

#endif