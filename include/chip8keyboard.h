#ifndef CHIP8KEYBOARD_H
#define CHIP8KEYBOARD_H

#include <stdbool.h>
#include <SDL2/SDL.h>
#include "config.h"

struct chip8_keyboard{   
    bool keyboard[TOTAL_KEYS];
    char keymap[TOTAL_KEYS];
};

int chip8_keyboard_map(const char* map, char key);
    //return the index in a char array of the one containing key
    //will receive a keyboard event and return which key it means in the CHIP8 from 0 to F

void chip8_keyboard_down(struct chip8_keyboard* keyboard, int key);

void chip8_keyboard_up(struct chip8_keyboard* keyboard, int key);

bool chip8_keyboard_is_down(struct chip8_keyboard *keyboard, int key);

#endif
