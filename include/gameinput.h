#ifndef GAMEINPUT_H
#define GAMEINPUT_H
#include <SDL2/SDL.h>
#include "chip8.h"

void game_input(struct chip8 *chip8, struct DisplaySettings *display);

#endif
