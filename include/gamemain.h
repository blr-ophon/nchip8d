#ifndef GAMEMAIN_H
#define GAMEMAIN_H
#include "chip8.h"
#include "gameinput.h"

void clock_delay();
//ensures fetch-execute frequency of 500hz by
//delaying program execution until 2ms have passed

void render_new_frame(struct DisplaySettings *display, struct chip8 *chip8);

void game_main(struct DisplaySettings *display, struct chip8 *chip8);

#endif
