#include <stddef.h>
#include <stdint.h>
#include "vga.h"
#include "config.h"
#include "string/string.h"

#define VGA_MAX_COL 80
#define VGA_MAX_ROW 20

static uint16_t *vga_base_addr = 0;
static uint16_t vga_row_index = 0;
static uint16_t vga_col_index = 0;

static uint16_t make_char(char c, color_t colour);
static void iterate_char(const char *str, color_t color);
static void new_line();

static uint16_t make_char(char character, color_t colour)
{
    return (colour << 8) | character;
}

void vga_write_char(char c, color_t colour)
{
    if (c == '\n')
    {
        new_line();
        return;
    }

    vga_base_addr[(vga_row_index * VGA_MAX_COL) + vga_col_index] = make_char(c, colour);
    vga_col_index++;
    if (vga_col_index >= VGA_MAX_COL)
        new_line();
}

void init_vga()
{
    vga_base_addr = (uint16_t(*))(VGA_BASE_ADDR);
    vga_row_index = 0;
    vga_col_index = 0;

    for (size_t row_index = 0; row_index < VGA_MAX_ROW; row_index++)
        for (size_t col_index = 0; col_index < VGA_MAX_COL; col_index++)
            vga_base_addr[(row_index * VGA_MAX_COL) + col_index] = make_char(' ', BLACK);
}

void println(const char *str)
{
    iterate_char(str, WHITE);
}

void panic(const char *msg)
{
    iterate_char(msg, RED);
    while (1)
    {
    }
}

static void iterate_char(const char *str, color_t color)
{
    size_t len = strlen(str);
    for (int i = 0; i < len; i++)
        vga_write_char(str[i], color);
    new_line();
}

static void new_line()
{
    vga_col_index = 0;
    vga_row_index++;
}