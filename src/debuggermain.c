#include "../include/debuggermain.h"
#include <stdio.h>

int start_address = PROGRAM_LOAD_ADDRESS;

void debugger_input(struct chip8 *chip8, struct DisplaySettings *display){
    SDL_Event event;
    SDL_WaitEvent(&event);

    switch(event.type){
        case SDL_QUIT:
            chip8->running_state = false;
            break;
        case SDL_KEYDOWN:
            if(event.key.keysym.sym == SDLK_ESCAPE){
                chip8->running_state = false;
            }
            if(event.key.keysym.sym == SDLK_TAB){
                display->debugger_mode = false;
            }
            if(event.key.keysym.sym == SDLK_LEFT){
                if(start_address - 0x200 >= 0x200){
                    start_address -= 0x200;
                }
            }
            if(event.key.keysym.sym == SDLK_RIGHT){
                if(start_address + 0x200 < 0xfff){
                    start_address += 0x200;
                }
            }

            if(event.key.keysym.sym == SDLK_SPACE){
                fetch_execute(chip8);
            }
            break;
    }

    SDL_PumpEvents();
}



void debugger_main(struct chip8 *chip8, struct DisplaySettings *display){

    debugger_input(chip8, display);

    SDL_Renderer *renderer = display->renderer;
    int width = display->width;

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

////////////////////////////////////////////////////////////////////////////////
/// Miniature section
////////////////////////////////////////////////////////////////////////////////
    
    unsigned short opcode = chip8_memory_read16(&chip8->memory, chip8->registers.PC);
    if(opcode & 0xD000){
        debugger_miniature(renderer, chip8, width);
    }

    //font initialization
    TTF_Init();
    int fontsize = width/96; 
    TTF_Font* DebuggerFont = TTF_OpenFont(
            "./fonts/BigBlue TerminalPlus Nerd Font Complete.TTF",
            fontsize 
    );
    if(DebuggerFont == NULL){
        fprintf(stderr, "Font not found\n");
        //exit(1);
    }

////////////////////////////////////////////////////////////////////////////////
///Registers and Memory section
////////////////////////////////////////////////////////////////////////////////

    //border
    SDL_Rect registers_border= {
        width/3,
        0,
        width/6,
        width/6
    };
    SDL_RenderDrawRect(renderer, &registers_border);

    
    show_chip8_registers(renderer, chip8, DebuggerFont, width);


////////////////////////////////////////////////////////////////////////////////
/// Input Section
////////////////////////////////////////////////////////////////////////////////

    //border
    SDL_Rect input_border= {
        0,
        width/6,
        width/3,
        width/12
    };
    SDL_RenderDrawRect(renderer, &input_border);

    debugger_display_keyboard(renderer, chip8, width, DebuggerFont);

////////////////////////////////////////////////////////////////////////////////
/// HEX DUMP 
////////////////////////////////////////////////////////////////////////////////

    //border
    SDL_Rect hexdump_border= {
        width/2,
        0,
        width/2,
        width/2
    };
    SDL_RenderDrawRect(renderer, &hexdump_border);

    debugger_hexdump(renderer, chip8, width, DebuggerFont, start_address);

////////////////////////////////////////////////////////////////////////////////
/// current and past opcodes 
////////////////////////////////////////////////////////////////////////////////

    //border
    SDL_Rect pastopcodes_border= {
        width/3,
        width/6,
        width/6,
        2*(width/6)
    };
    SDL_RenderDrawRect(renderer, &pastopcodes_border);

    debugger_current_opcodes(renderer, chip8, width, DebuggerFont);

////////////////////////////////////////////////////////////////////////////////
/// blank area 
////////////////////////////////////////////////////////////////////////////////

    //border
    SDL_Rect blankarea_border= {
        0,
        width/4,
        width/3,
        width/4
    };
    SDL_RenderDrawRect(renderer, &blankarea_border);

    SDL_RenderPresent(renderer);
    TTF_CloseFont(DebuggerFont);
}




