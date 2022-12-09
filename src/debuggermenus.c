#include "../include/debuggermenus.h"

void debugger_miniature(SDL_Renderer *renderer, struct chip8 *chip8, int width){
    int window_multiplier = width/CHIP8_WIDTH;
    SDL_Rect miniature_border = {
        0,
        0,
        width/3,
        width/6
    };
    SDL_RenderDrawRect(renderer, &miniature_border);

    for(int y = 0; y < CHIP8_HEIGHT; y++){
        for(int x = 0; x < CHIP8_WIDTH; x++){
            if(screen_is_set(&chip8->screen, x, y)){
                SDL_Rect pixel = { 
                    //put 3 as a constant on config.h
                    x * window_multiplier/3,
                    y * window_multiplier/3,
                    PIXEL_SIZE * window_multiplier/3,
                    PIXEL_SIZE * window_multiplier/3
                };
                SDL_RenderFillRect(renderer, &pixel);
            }
        }
    }
}

void RenderTextSurface(SDL_Renderer *renderer, SDL_Surface *surfaceText, int x, int y){
        //create a rectangle with surface size and copy surface to it
        //rectangle has size and position (x,y)
        SDL_Rect text_block;
        text_block.x = x;
        text_block.y = y;
        text_block.w = surfaceText->w;
        text_block.h = surfaceText->h;

        //create texture from surface
        SDL_Texture *textureText = SDL_CreateTextureFromSurface(renderer, surfaceText);

        SDL_RenderCopy(renderer, textureText, NULL, &text_block);
        SDL_DestroyTexture(textureText);

}



void show_chip8_registers(SDL_Renderer *renderer, struct chip8 *chip8, TTF_Font *font, int width){

    int window_multiplier = width/CHIP8_WIDTH;

    SDL_Color fg = {255,255,255};

    int x = (CHIP8_WIDTH+1)*window_multiplier/3;
    int y = 0;

    //REGISTERS V0 TO VF
    for(int i = 0; i < NUMBER_OF_REGISTERS ; i++){
        char s[30];
        sprintf(s, " V%x: %#x", i, chip8->registers.V[i]);
        SDL_Surface *surfaceText = TTF_RenderText_Solid(font, s, fg);
        RenderTextSurface(renderer, surfaceText, x, y);
        y += (surfaceText->h); 
        SDL_FreeSurface(surfaceText);

    }
    
    //reposition on screen
    y = 0;
    x += (CHIP8_WIDTH+1)*window_multiplier/12;

    char s[30];

    //PC, SP, I, DT and ST 
    sprintf(s, "PC: %#x", chip8->registers.PC);
    SDL_Surface *surfaceText = TTF_RenderText_Solid(font, s, fg);
    RenderTextSurface(renderer, surfaceText, x, y);
    y += (surfaceText->h);
    
    sprintf(s, "SP: [%d]", chip8->registers.SP);
    surfaceText = TTF_RenderText_Solid(font, s, fg);
    RenderTextSurface(renderer, surfaceText, x, y);
    y += (surfaceText->h);

    sprintf(s, "    %#x", chip8->stack.stack[chip8->registers.SP - 1]);
    surfaceText = TTF_RenderText_Solid(font, s, fg);
    RenderTextSurface(renderer, surfaceText, x, y);
    y += (surfaceText->h);
    
    sprintf(s, " I: %#x", chip8->registers.I);
    surfaceText = TTF_RenderText_Solid(font, s, fg);
    RenderTextSurface(renderer, surfaceText, x, y);
    y += (surfaceText->h);
    
    sprintf(s, "DT: %#x", chip8->registers.DT);
    surfaceText = TTF_RenderText_Solid(font, s, fg);
    RenderTextSurface(renderer, surfaceText, x, y);
    y += (surfaceText->h);
    
    sprintf(s, "ST: %#x", chip8->registers.ST);
    surfaceText = TTF_RenderText_Solid(font, s, fg);
    RenderTextSurface(renderer, surfaceText, x, y);
    y += (surfaceText->h);

    SDL_FreeSurface(surfaceText);
}



void debugger_display_keyboard(SDL_Renderer *renderer, struct chip8 *chip8, int width, TTF_Font *font){
    SDL_Color fg = {255,255,255};
    SDL_Surface *surfaceText = TTF_RenderText_Solid(font, "INPUT:", fg);
    RenderTextSurface(renderer, surfaceText, (width/54), 3*(width/16));

    SDL_Rect keys_borders = {
        width/54,
        5*(width/24),
        width/54,
        width/48
    };


    char key[2];
    for(int i = 0; i < TOTAL_KEYS; i++){
        SDL_Color keys_fg = {255,255,255};
        if(chip8_keyboard_is_down(&chip8->keyboard, i)){
            SDL_RenderFillRect(renderer, &keys_borders);
            keys_fg.r = 150;
            keys_fg.g = 0;
            keys_fg.b = 0;
        }

        SDL_RenderDrawRect(renderer, &keys_borders);
        
        sprintf(key, "%X", i);
        SDL_Surface *surfaceText = TTF_RenderText_Solid(font, key, keys_fg);
        //create texture from surface
        SDL_Texture *textureText = SDL_CreateTextureFromSurface(renderer, surfaceText);
        
        SDL_RenderCopy(renderer, textureText, NULL, &keys_borders);
        SDL_DestroyTexture(textureText);

        keys_borders.x += width/54;
    }
    
    SDL_FreeSurface(surfaceText);
}



void debugger_hexdump(SDL_Renderer *renderer, struct chip8 *chip8, int width, TTF_Font *font, int start_address){
    SDL_Color fg = {0,150,0};

    int x = 5*(width)/9;
    int y = width/18;

    //title
    SDL_Surface *hexd_title = TTF_RenderText_Solid(font, "HEX DUMP:", fg);
    RenderTextSurface(renderer, hexd_title, x, y - 3*hexd_title->h);
    SDL_FreeSurface(hexd_title);

    SDL_Surface *surfaceText;
    for(int i = -1; i < 32; i++){ 
        //add 16 and 32 to config.h
        for(int j = -1; j < 16; j++){
            char s[10];
            if(j == -1 && i == -1){
                sprintf(s, "        "); 
            }
            else if(i == -1){
                sprintf(s, " %01X ", j);
            }
            else if(j == -1){
                sprintf(s, "%#05x  ", (start_address + 16*i) & 0xff0);
            }else{
                sprintf(s, " %02x", chip8->memory.memory[start_address + 16*i + j]);
            }

            

            surfaceText = TTF_RenderText_Solid(font, s, fg);
            RenderTextSurface(renderer, surfaceText, x, y);

            //memory contents border
            if(j == 0 && i ==0){
                SDL_Rect contents_border = {
                    x,
                    y,
                    16*surfaceText->w + (surfaceText->w)/3,
                    32*surfaceText->h
                };
                SDL_RenderDrawRect(renderer, &contents_border);
            }

            x += surfaceText->w;
        }
        x = 5*(width)/9; //return x to original position
        y += surfaceText->h;
        if(i == -1){
            y += surfaceText->h;
        }
    }

    SDL_FreeSurface(surfaceText);
}


void debugger_current_opcodes(SDL_Renderer *renderer, struct chip8 *chip8, int width, TTF_Font *font){
    int x = (width)/3;
    int y = width/6;

    SDL_Surface *surfaceText;
    char s[25];
    for(int i = -12; i < 13; i++){
        SDL_Color fg = {255,152,152};
        if(chip8->registers.PC + i < 0x200){
            sprintf(s, "        ");
        }

        unsigned short address =chip8->registers.PC + 2*i;
        unsigned short opcode = chip8_memory_read16(&chip8->memory, address);
        if(i == 0){ //current opcode and center of list
            fg.r = 255;
            fg.g = 41;
            fg.b = 41;
            sprintf(s, "  %#05x:   %04x <--", address, opcode);
        }else{
            sprintf(s, "  %#05x:   %04x", address, opcode);
        }


        surfaceText = TTF_RenderText_Solid(font, s, fg);

        if(i == -12){ // space after top of border
            y+= 2*(surfaceText->h);
        }

        RenderTextSurface(renderer, surfaceText, x, y);
        y += (surfaceText->h);
    }
    SDL_FreeSurface(surfaceText);

}






