#include "../include/main.h"
#include <time.h>

void setup(struct chip8 *chip8, const char *filename){
    //load keymap and program to chip8 memory
    //TODO: custom keymap
    chip8_init(chip8);
    chip8->running_state = true;

    char keymap[TOTAL_KEYS] = {
        SDLK_0, SDLK_1, SDLK_2, SDLK_3,
        SDLK_4, SDLK_5, SDLK_6, SDLK_7,
        SDLK_8, SDLK_9, SDLK_a, SDLK_b,
        SDLK_c, SDLK_d, SDLK_e, SDLK_f
    };
    memcpy(&chip8->keyboard.keymap, keymap, sizeof(keymap)); 

    FILE *f = fopen(filename, "rb");
    if(!f){
	    fprintf(stderr, "Failed to open the file / Empty file\n");
        exit(1);
    }
    fseek(f, 0, SEEK_END); 
    long size = ftell(f); 
    fseek(f, 0, SEEK_SET);
                        
    char buf[size];
    int res = fread(buf, size, 1, f);
    if(res != 1){
        fprintf(stderr, "Failed to read from file\n");
        exit(1);
    }

    chip8_load(chip8, buf, size);
}



int main(int argc, char *argv[]){
    struct chip8 chip8;
    SDL_Init(SDL_INIT_EVERYTHING);
    struct DisplaySettings display;
    display.window = NULL;
    display.renderer = NULL;

    srand(time(NULL)); 

    if(argc < 2){
        fprintf(stderr, "Must provide a file\n");
        exit(1);
        return -1;
    }
    const char* filename = argv[1];
    printf(" Loading file: %s\n", filename);

    setup(&chip8, filename);

    init_window(&display);

    display_window(&display, &chip8);

    destroy_window(&display);

    return 0;
}
