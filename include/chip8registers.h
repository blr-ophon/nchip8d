#ifndef CHIP8REGISTERS_H
#define CHIP8REGISTERS_H
#include "config.h"
#include <stdint.h>

struct chip8_registers{
    uint8_t V[NUMBER_OF_REGISTERS];
    uint16_t I;
    uint8_t DT; 
    uint8_t ST; 
    uint16_t PC;
    uint8_t SP;
};

#endif

