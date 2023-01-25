#ifndef CHIP8MEMORY_H
#define CHIP8MEMORY_H
#include "config.h"

struct chip8_memory{
    unsigned char memory[CHIP8_MEMORY_SIZE];

};

void chip8_memory_write(struct chip8_memory *memory,int index, unsigned char val);
//write a byte in memory

unsigned char chip8_memory_read(struct chip8_memory *memory, int index);
//read a byte from memory

unsigned short chip8_memory_read16(struct chip8_memory *memory, int index);
//read a word from memory

#endif
