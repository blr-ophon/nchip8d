#include "gamemain.h"

int last_frame_time = 0;

void clock_delay(){
    //ensures fetch-execute frequency of 500hz by
    //delaying program execution until 2ms have passed
    int time_passed = SDL_GetTicks() - last_frame_time;
    int time_to_wait = CLOCK_PERIOD - time_passed;

    if(time_to_wait > 0 && time_to_wait <= CLOCK_PERIOD){
        SDL_Delay(time_to_wait);
    }
    last_frame_time = SDL_GetTicks();
}



void render_new_frame(struct DisplaySettings *display, struct chip8 *chip8){
    //clears current frame and displays another by reading video memory
    game_input(chip8, display);
    int window_multiplier = display->window_multiplier;
    SDL_SetRenderDrawColor(display->renderer, 0, 0, 0, 255);
    SDL_RenderClear(display->renderer);
    SDL_SetRenderDrawColor(display->renderer, 255, 255, 255, 255);

    for(int y = 0; y < CHIP8_HEIGHT; y++){
        for(int x = 0; x < CHIP8_WIDTH; x++){
            if(screen_is_set(&chip8->screen, x, y)){
                SDL_Rect pixel = { 
                    x * window_multiplier,
                    y * window_multiplier,
                    PIXEL_SIZE * window_multiplier,
                    PIXEL_SIZE * window_multiplier
                };
                SDL_RenderFillRect(display->renderer, &pixel);
            }
        }
    }
    SDL_RenderPresent(display->renderer);
}

void game_main(struct DisplaySettings *display, struct chip8 *chip8){
    clock_delay();
    unsigned short opcode = fetch_execute(chip8);
    render_new_frame(display, chip8);
}
