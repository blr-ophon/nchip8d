#include "chip8stack.h"
#include "chip8.h"
#include <assert.h>

static void chip8_stack_in_bounds(struct chip8* chip8){
   assert(chip8->registers.SP < SIZE_OF_STACK);
}

void chip8_stack_push(struct chip8* chip8, uint16_t val){
    chip8_stack_in_bounds(chip8);
    chip8->stack.stack[chip8->registers.SP] = val;
    chip8->registers.SP ++;
}

uint16_t chip8_stack_pop(struct chip8* chip8){
    chip8->registers.SP --;
    chip8_stack_in_bounds(chip8);
    uint16_t popped_address;
    popped_address = chip8->stack.stack[chip8->registers.SP];
    return popped_address; 
}
