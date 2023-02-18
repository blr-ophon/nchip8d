#include <assert.h>
#include "display.h"

void init_window(struct DisplaySettings *display){
    SDL_DisplayMode DM;
    SDL_GetCurrentDisplayMode(0, &DM);
    display->width = DM.w/4;
    int height = display->width * CHIP8_WINDOW_RATIO;
    display->window_multiplier = (display->width)/CHIP8_WIDTH;
    assert(display->width > CHIP8_WIDTH);

    display->window  = SDL_CreateWindow(
            "Emulador CHIP-8", 
            0, 
            0,
            display->width,
            height,
            SDL_WINDOW_BORDERLESS |
            SDL_WINDOW_RESIZABLE
    );
    display->renderer = SDL_CreateRenderer(display->window, -1, 0);

    if(!(display->window) || !(display->renderer)){
        fprintf(stderr, "Error creating window/renderer\n"
            "SDL Error: %s\n", SDL_GetError());
            exit(2);
    }

    display->debugger_mode = false;
}


void destroy_window(struct DisplaySettings *display){
    SDL_DestroyWindow(display->window);

    SDL_DestroyRenderer(display->renderer);

    SDL_Quit();
}


void display_window(struct DisplaySettings *display, struct chip8 *chip8){
    chip8->opcode_counter = 0;

    while(chip8->running_state){

        if(display->debugger_mode){
            debugger_main(chip8, display);

        }else{
            game_main(display, chip8);

        }

        if(chip8->opcode_counter >= EXECS_PER_DT){
            if(chip8->registers.DT > 0){
                chip8->registers.DT --;
            }
            if(chip8->registers.ST > 0){
                chip8->registers.ST --;
                //TODO: implement sound
            }
            chip8->opcode_counter = 0;
        }
    }
}



