#include <assert.h>
#include "chip8screen.h"

static void check_screen_bounds(int x, int y){
    //Prevents the program from writing or reading beyond the buffer
    assert(x >=0 && x < CHIP8_WIDTH && y >= 0 && y < CHIP8_HEIGHT);
}

void screen_clear(struct chip8_screen *screen){
    //clears buffer
    memset(screen->pixels, 0, sizeof(screen->pixels));
}

void screen_set(struct chip8_screen* screen, int x, int y){
    //draws a pixel in screen buffer on (x,y)
    check_screen_bounds(x,y);
    screen->pixels[y][x] = true;
}


bool screen_is_set(struct chip8_screen *screen, int x, int y){
    //verify if a pixel in screen buffer on (x,y) is set
    check_screen_bounds(x,y);
    return screen->pixels[y][x];
}

bool draw_sprite(struct chip8_screen* screen, int x, int y, uint8_t *sprite, int num){
    /* receives sprite adress, the number of bytes (num) and x,y position in screen
     * main function is to draw 1 bytes of sprite in screen in (x,y)
     * returns true if the sprite collides with anything drawn on the screen
    */

    check_screen_bounds(x,y);
    bool collision = false;

    for(int ly = 0; ly < num; ly++){
        char c = sprite[ly];
        for(int lx = 0; lx < 8; lx++){
            //check if there is any bit set in c
            if((c & (0x80 >> lx)) == 0){
                continue; //if bit not set
            }

            if(screen->pixels[(y + ly) % CHIP8_HEIGHT][(x + lx) % CHIP8_WIDTH]){
                //check if bit is set on screen 
                collision = true;
            }
            //set bit as a pixel in screen if it is set in c,  a XOR true = a'
            screen->pixels[(y + ly) % CHIP8_HEIGHT][(x + lx) % CHIP8_WIDTH] ^= true; // ^= : XOR
        }
    }

    return collision;
}
