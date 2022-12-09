#ifndef CHIP8REGISTERS_H
#define CHIP8REGISTERS_H
#include "./config.h"

struct chip8_registers{
    unsigned char V[NUMBER_OF_REGISTERS];
    unsigned short I;
    unsigned char DT; 
    unsigned char ST; 
    unsigned short PC;
    unsigned char SP;
};

#endif

