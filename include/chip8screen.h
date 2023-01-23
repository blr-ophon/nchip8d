#ifndef CHIP8SCREEN_H
#define CHIP8SCREEN_H

#include <stdbool.h>
#include "./config.h"

struct chip8_screen{
    bool pixels[CHIP8_HEIGHT][CHIP8_WIDTH];
};

void screen_clear(struct chip8_screen *screen);
//blank screen

void screen_set(struct chip8_screen *screen, int x, int y);
//draws a pixel in screen on (x,y)

bool screen_is_set(struct chip8_screen *screen, int x, int y);
//verify if a pixel in screen on (x,y) is set

bool draw_sprite(struct chip8_screen* screen, int x, int y, unsigned char *sprite, int num);
/* receives sprite adress, the number of bytes (num) and x,y position in screen
 * main function is to draw 1 bytes of sprite in screen in (x,y)
 * returns true if the sprite collides with anything drawn on the screen
*/

#endif
