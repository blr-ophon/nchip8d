#include "../include/chip8keyboard.h"
#include <assert.h>

static void keyboard_in_bounds(int key){
    assert(key >= 0 && key < TOTAL_KEYS);
}


int chip8_keyboard_map(const char* map, char key){
    //return the index in a char array of the one containing key
    //will receive a keyboard event and return which key it means in the CHIP8 from 0 to F
    for(int i = 0; i < TOTAL_KEYS; i++){
        if(map[i] == key){
            return i;
        }
    }
    return -1;
}

void chip8_keyboard_down(struct chip8_keyboard* keyboard, int key){
    keyboard_in_bounds(key);
    keyboard->keyboard[key] = true; 
}

void chip8_keyboard_up(struct chip8_keyboard* keyboard, int key){
    keyboard_in_bounds(key);
    keyboard->keyboard[key] = false; 
}

bool chip8_keyboard_is_down(struct chip8_keyboard *keyboard, int key){
    keyboard_in_bounds(key);
    return keyboard->keyboard[key];
}
