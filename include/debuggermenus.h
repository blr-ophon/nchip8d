#ifndef DEBUGGERMENUS_H
#define DEBUGGERMENUS_H
#include "./chip8.h"

void debugger_miniature(SDL_Renderer *renderer, struct chip8 *chip8, int width);

void RenderTextSurface(SDL_Renderer *renderer, SDL_Surface *surfaceText, int x, int y);

void show_chip8_registers(SDL_Renderer *renderer, struct chip8 *chip8, TTF_Font *font, int width);

void debugger_display_keyboard(SDL_Renderer *renderer, struct chip8 *chip8, int width, TTF_Font *font);

void debugger_hexdump(SDL_Renderer *renderer, struct chip8 *chip8, int width, TTF_Font *font, int start_address);

void debugger_current_opcodes(SDL_Renderer *renderer, struct chip8 *chip8, int width, TTF_Font *font);

#endif
