#include "gameinput.h"

void game_input(struct chip8 *chip8, struct DisplaySettings *display){
    struct chip8_keyboard *keyboard = &chip8->keyboard;
    SDL_Event event;
    SDL_PollEvent(&event);
    switch(event.type){
        case SDL_QUIT:
            chip8->running_state = false;
            break;
        case SDL_KEYDOWN:
            if(event.key.keysym.sym == SDLK_ESCAPE){
                chip8->running_state = false;
            }
            if(event.key.keysym.sym == SDLK_TAB){
                display->debugger_mode = true;
                //debugger mode
                //set running state to enum{idle, running, debug}
            }
            {
            char key = event.key.keysym.sym; //takes real key
            char vkey = chip8_keyboard_map(&keyboard->keymap, key); //convert to virtual key
            if(vkey != -1){
                chip8_keyboard_down(keyboard, vkey);
            }
            }
            break;
        case SDL_KEYUP:
            {
            char key = event.key.keysym.sym;
            char vkey = chip8_keyboard_map(&keyboard->keymap, key); 
            if(vkey != -1){
                chip8_keyboard_up(keyboard, vkey);
            }
            }
            break;
    }
}
