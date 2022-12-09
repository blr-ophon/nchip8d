#ifndef DEBUGGERMAIN_H
#define DEBUGGERMAIN_H
#include "./chip8.h"
#include "./debuggermenus.h"

void debugger_input(struct chip8 *chip8, struct DisplaySettings *display); 

void debugger_main(struct chip8 *chip8, struct DisplaySettings *display);

#endif
