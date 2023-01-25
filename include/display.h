#ifndef DISPLAY_H
#define DISPLAY_H

#include "chip8.h"
#include "gameinput.h" 
#include "debuggermain.h" 
#include "gamemain.h"

void init_window(struct DisplaySettings *displayPtr);

void destroy_window(struct DisplaySettings *display);

void display_window(struct DisplaySettings *display, struct chip8 *chip8);

#endif
