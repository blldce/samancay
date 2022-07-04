#include "memory.h"

void *memset(void(*addr), int value, size_t size)
{
    char(*c_ptr) = (char(*))addr;

    int index = 0;
    while (index < size)
    {
        c_ptr[index] = (char)value;
        index++;
    }

    return addr;
}

/*
void* memset(void* ptr, int c, size_t size)
{
    char* c_ptr = (char*) ptr;
    for (int i = 0; i < size; i++)
    {
        c_ptr[i] = (char) c;
    }
    return ptr;
} 
*/
