#ifndef CHIP8KEYBOARD_H
#define CHIP8KEYBOARD_H

#include "./config.h"
#include <stdbool.h>
#include <SDL2/SDL.h>

struct chip8_keyboard{   
    bool keyboard[TOTAL_KEYS];
    char keymap[TOTAL_KEYS];
};

int chip8_keyboard_map(const char* map, char key);
void chip8_keyboard_down(struct chip8_keyboard* keyboard, int key);
void chip8_keyboard_up(struct chip8_keyboard* keyboard, int key);
bool chip8_keyboard_is_down(struct chip8_keyboard *keyboard, int key);

#endif