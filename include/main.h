#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdbool.h>
#include "SDL2/SDL.h"
#include <string.h>
#include "./chip8.h"
#include "./display.h"

void setup(struct chip8 *chip8, const char* filename);
//load keymap and program to chip8 memory

int main(int argc, char *argv[]);

#endif
