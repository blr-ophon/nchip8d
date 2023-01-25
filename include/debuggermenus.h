#ifndef DEBUGGERMENUS_H
#define DEBUGGERMENUS_H
#include "chip8.h"

void debugger_miniature(SDL_Renderer *renderer, struct chip8 *chip8, int width);
//renders miniature of the emulation

void RenderTextSurface(SDL_Renderer *renderer, SDL_Surface *surfaceText, int x, int y);
//create a rectangle with surface size and copy surface to it
//rectangle has position (x,y) and the size of the surface

void show_chip8_registers(SDL_Renderer *renderer, struct chip8 *chip8, int width, TTF_Font *font);
//display all chip8 register contents

void debugger_display_keyboard(SDL_Renderer *renderer, struct chip8 *chip8, int width, TTF_Font *font);
//display chip8 buttons currently pressed

void debugger_hexdump(SDL_Renderer *renderer, struct chip8 *chip8, int width, TTF_Font *font, int start_address);
//shows page of 512 memory contents starting at start_address

void debugger_current_opcodes(SDL_Renderer *renderer, struct chip8 *chip8, int width, TTF_Font *font);
//display 12 previous and 12 instructions ahead of current one pointed by PC 

#endif
