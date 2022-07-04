#include <stdint.h>
#include "vga.h"

#define VGA_MAX_ROW 20
#define VGA_MAX_COL 80

static uint16_t(*vga_base_addr) = 0x0;

static uint16_t vga_row_index = 0;
static uint16_t vga_col_index = 0;

static void println_internal(char(*), color_t);
static uint16_t make_char(char, color_t);
static void new_line();

static uint16_t make_char(char character, color_t color)
{
    return (color << 8) | character;
}

// clear VGA rows colums
void init_vga()
{
    vga_base_addr = (uint16_t(*))0xB8000;
    vga_row_index = 0;
    vga_col_index = 0;

    int row_index = 0;
    while (row_index < VGA_MAX_ROW)
    {
        int col_index = 0;
        while (col_index < VGA_MAX_COL)
        {
            vga_base_addr[row_index * VGA_MAX_COL + col_index] = make_char(' ', BLACK);

            col_index++;
        }
        row_index++;
    }
}

void println(char(*char_buff))
{
    println_internal(char_buff, WHITE);
}

void panic(char(*char_buff))
{
    println_internal(char_buff, RED);
    while (1)
    {
    }
}

static void new_line()
{
    vga_col_index = 0; // reset column
    vga_row_index++;   // new row
}

static void println_internal(char(*char_buff), color_t color)
{
    if (vga_row_index >= VGA_MAX_ROW) // recycle vga
        init_vga();

    int index = 0;
    while (char_buff[index]) // check null terminator ('\0')
    {
        if (vga_col_index >= VGA_MAX_COL) // check end of max column
            new_line();

        if (char_buff[index] == '\n') // check new line
        {
            new_line();
            index++;
        }

        vga_base_addr[vga_row_index * VGA_MAX_COL + vga_col_index] = make_char(char_buff[index], color);
        index++;
        vga_col_index++;
    }
    new_line();
}
