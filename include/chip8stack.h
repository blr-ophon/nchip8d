#ifndef CHIP8STACK_H
#define CHIP8STACK_H
#include "config.h"
#include <stdint.h>

struct chip8; //need to redeclare to declare functions
              //struct chip8 is in chip8.h which is included in main
struct chip8_stack{
    uint16_t stack[SIZE_OF_STACK];
};

void chip8_stack_push(struct chip8* chip8, uint16_t val);
uint16_t chip8_stack_pop(struct chip8* chip8);

#endif
