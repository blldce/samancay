#ifndef VGA_H
#define VGA_H

typedef enum
{
    BLACK = 1,
    GREEN = 2,
    RED = 5,
    WHITE = 15
} color_t;

extern void init_vga();
extern void println(char(*));
extern void panic(char(*));


#endif // VGA_H