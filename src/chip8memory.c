#include "../include/chip8memory.h"
#include <assert.h>


static void chip8_is_memory_in_bound(int index){ 
    assert(index >= 0 && index < CHIP8_MEMORY_SIZE);
}

void chip8_memory_write(struct chip8_memory *memory,int index, unsigned char val){
    //WRITE
    chip8_is_memory_in_bound(index);
    memory->memory[index] = val;
}

unsigned char chip8_memory_read(struct chip8_memory *memory, int index){
    //READ a byte;
    chip8_is_memory_in_bound(index);
    return memory->memory[index];
}

unsigned short chip8_memory_read16(struct chip8_memory *memory, int index){
    //READ a 16 bit word;
    chip8_is_memory_in_bound(index);
    unsigned char byte1 = memory->memory[index];
    unsigned char byte2 = memory->memory[index+1];
    return (byte1 << 8) | byte2;
}
