#ifndef CHIP8SCREEN_H
#define CHIP8SCREEN_H

#include <stdbool.h>
#include "./config.h"

struct chip8_screen{
    bool pixels[CHIP8_HEIGHT][CHIP8_WIDTH];
};

void screen_set(struct chip8_screen *screen, int x, int y);
bool screen_is_set(struct chip8_screen *screen, int x, int y);
bool draw_sprite(struct chip8_screen* screen, int x, int y, unsigned char *sprite, int num);
void screen_clear(struct chip8_screen *screen);

#endif
