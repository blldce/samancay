#if !defined(VGA_H)
#define VGA_H

typedef enum
{
    BLACK = 0,
    GREEN = 2,
    RED = 5,
    WHITE = 15
} color_t;

extern void println(const char *str);
extern void vga_write_char(char c, color_t colour);
extern void panic(const char *msg);
extern void init_vga();

#endif // VGA_H
