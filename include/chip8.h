#ifndef CHIP8_H
#define CHIP8_H

#include <stddef.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "./config.h"
#include "./chip8memory.h"
#include "./chip8registers.h"
#include "./chip8stack.h"
#include "./chip8keyboard.h"
#include "./chip8screen.h"

struct chip8{
    struct chip8_memory memory;
    struct chip8_registers registers;
    struct chip8_stack stack;
    struct chip8_keyboard keyboard;
    struct chip8_screen screen;
    bool running_state;
    int opcode_counter;
};


struct DisplaySettings{
    SDL_Window *window;
    SDL_Renderer *renderer;
    bool debugger_mode;
    int width;
    int window_multiplier;
    //must start false
};

void chip8_init(struct chip8 *chip8);
//initialize memory and all registers to 0
void chip8_load(struct chip8 *chip8, const char *buf, size_t size);
//load contents of buffer to 0x200 in virtual memory
unsigned short fetch_execute(struct chip8 *chip8);

void chip8_exec(struct chip8 *chip8, unsigned short opcode);

#endif
