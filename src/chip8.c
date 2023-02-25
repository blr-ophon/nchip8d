#include "chip8.h"
#include <assert.h>

const uint8_t character_sprites[] = {
    0xf0, 0x90, 0x90, 0x90, 0xf0,   //0
    0x20, 0x60, 0x20, 0x20, 0x70,   //1
    0xf0, 0x10, 0xf0, 0x80, 0xf0,   //2
    0xf0, 0x10, 0xf0, 0x10, 0xf0,   //3
    0x90, 0x90, 0xf0, 0x10, 0x10,   //4
    0xf0, 0x80, 0xf0, 0x10, 0xf0,   //5
    0xf0, 0x80, 0xf0, 0x90, 0xf0,   //6
    0xf0, 0x10, 0x20, 0x40, 0x40,   //7
    0xf0, 0x90, 0xf0, 0x90, 0xf0,   //8
    0xf0, 0x90, 0xf0, 0x10, 0xf0,   //9
    0xf0, 0x90, 0xf0, 0x90, 0x90,   //A
    0xe0, 0x90, 0xe0, 0x90, 0xe0,   //B
    0xf0, 0x80, 0x80, 0x80, 0xf0,   //C
    0xe0, 0x90, 0x90, 0x90, 0xe0,   //D
    0xf0, 0x80, 0xf0, 0x80, 0xf0,   //E
    0xf0, 0x80, 0xf0, 0x80, 0x80   //F
};



void chip8_init(struct chip8 *chip8){
    //initialize memory, screen and all registers to 0
    memset(chip8, 0, sizeof(struct chip8));
    //store character set in 0x000 to 0x1FF
    memcpy(&chip8->memory.memory, character_sprites, sizeof(character_sprites));
}

void chip8_load(struct chip8 *chip8, const char *buf, size_t size){
    //load contents of buffer to 0x200 in virtual memory
    //program start at 0x200 and must not overflow memory
   assert(size + PROGRAM_LOAD_ADDRESS  < CHIP8_MEMORY_SIZE);
   //copy contents of buffer to 0x200 in virtual memory
   memcpy(&chip8->memory.memory[PROGRAM_LOAD_ADDRESS], buf, size);
   chip8->registers.PC = PROGRAM_LOAD_ADDRESS;
}

static char chip8_wait_for_key_press(struct chip8* chip8)
{
    //TODO: Substitute this for gameinput
    //used by instruction 0xfx02 to stop execution until key is pressed
    SDL_Event event;
    while(SDL_WaitEvent(&event)){
        if(event.type != SDL_KEYDOWN){
            continue;
        }

        char c = event.key.keysym.sym;
        char chip8_key = chip8_keyboard_map(&chip8->keyboard.keymap, c);
        if (chip8_key != -1){
            return chip8_key;
        }
    }
    return -1;
}

void fetch_execute(struct chip8 *chip8){
    //fetch instruction, execute and increment program counter
    uint16_t opcode = chip8_memory_read16(&chip8->memory, chip8->registers.PC);
    chip8->registers.PC += 2;
    chip8_exec(chip8, opcode);
    chip8->opcode_counter++;
}



void chip8_exec(struct chip8 *chip8, uint16_t opcode){
    //executes machine code
    switch(opcode){
        case 0x00E0: //clear screen
            screen_clear(&chip8->screen);
            break;
        case 0x00EE: //return from subroutine
            chip8->registers.PC = chip8_stack_pop(chip8);
            break;
        default:
            break;
    }

    switch (opcode & 0xf000){
        case 0x1000: //jump to nnn    
            chip8->registers.PC = (opcode & 0x0fff);
            break;

        case 0x2000: //call subroutine at nnn
            chip8_stack_push(chip8, chip8->registers.PC);
            chip8->registers.PC = opcode & 0x0fff;
            break;

        case 0x3000: //skip next instruction if Vx = kk
        {
            uint8_t v_i = (opcode & 0x0f00) >> 8; 
            uint8_t comp_value = (opcode & 0x00ff);
            if(chip8->registers.V[v_i] == comp_value){  
                chip8->registers.PC += 2; 
            }
            break;
        }

        case 0x4000: //0x4xkk skip next if Vx != kk
        {
            uint8_t v_i = (opcode & 0x0f00) >> 8; 
            uint8_t comp_value = (opcode & 0x00ff);
            if(chip8->registers.V[v_i] != comp_value){  
                chip8->registers.PC += 2; 
            }
            break;
        }

        case 0x6000: //0x6xkk set vx = kk
            {
            uint8_t v_i = (0x0f00 & opcode) >> 8; 
            chip8->registers.V[v_i] = opcode & 0x00ff;
            }
            break;

        case 0x7000: //0x7xkk Vx = Vx+kk
            {
            uint8_t v_i = (0x0f00 & opcode) >> 8; 
            chip8->registers.V[v_i] += opcode & 0x00ff;
            break;
            }

        case 0xA000: //set I = nnn        
            chip8->registers.I = opcode & 0x0fff;
            break;

        case 0xB000: //jump to nnn + V0
            chip8->registers.PC = (opcode & 0x0fff) + chip8->registers.V[0];
            break;

        case 0xC000: //0xCxkk Vx = random byte(0 to 255) AND kk
            {
            uint8_t v_i = (opcode & 0x0f00) >> 8; 
            uint8_t val = rand()%256 & (opcode & 0x00ff);
            chip8->registers.V[v_i] = val;
            }
            break;

        //0xDxyn 
        //display sprite pointed in I of size n in x,y on screen and set Vf if there is collision
        case 0xD000: 
            {
            uint8_t x = (opcode & 0x0f00) >> 8; 
            uint8_t y = (opcode & 0x00f0) >> 4; 
            uint8_t xpos = chip8->registers.V[x];
            uint8_t ypos = chip8->registers.V[y];
            uint8_t *SpritePtr = &chip8->memory.memory[chip8->registers.I];
            uint8_t size = (opcode & 0x000f);
            chip8->registers.V[0xf] = draw_sprite(&chip8->screen, xpos, ypos, SpritePtr, size);
            break;
            }
        default:
            break;
    }

    uint8_t x = (opcode & 0x0f00) >> 8; 
    uint8_t y = (opcode & 0x00f0) >> 4; 
    switch(opcode & 0xf00f){
        case 0x5000: //0x5xy0 skip next if Vx = Vy
            { 
            if(chip8->registers.V[x] == chip8->registers.V[y]){  
                chip8->registers.PC += 2; 
            }
            break;
            }
        case 0x8000: //0x8xy0 Stores Vy in Vx
            { 
            chip8->registers.V[x] = chip8->registers.V[y];
            break;
            }
        case 0x8001: //0x8xy1 Vx |= Vy
            { 
            chip8->registers.V[x] |= chip8->registers.V[y];
            break;
            }
        case 0x8002: //0x8xy2 Vx &= Vy
            { 
            chip8->registers.V[x] &= chip8->registers.V[y];
            break;
            }
        case 0x8003: //0x8xy3 Vx ^=(xor) Vy
            { 
            chip8->registers.V[x] ^= chip8->registers.V[y];
            break;
            }
        case 0x8004: //0x8xy4 Vx = Vx+Vy, VF = carry of sum; 
            { 
            uint16_t sum = chip8->registers.V[x] + chip8->registers.V[y];
            chip8->registers.V[0xf] = sum & 0x0100? 1 : 0;
            chip8->registers.V[x] = sum;
            break;
            }
        case 0x8005: //0x8xy5 Vx= Vx-Vy, VF = !borrow of dif
            { 
            int8_t dif = chip8->registers.V[x] - chip8->registers.V[y];
            chip8->registers.V[x] = dif;
            chip8->registers.V[0xf] = dif > 0? 1 : 0;
            break;
            }

        case 0x8006: //0x8xy6 VF = Vx >> 1
            {
            uint8_t bit0 = 0x01 & chip8->registers.V[x];  
            chip8->registers.V[x] >>= 1;
            chip8->registers.V[0xf] = bit0;
            break;
            }
        case 0x8007: //0x8xy7 Vx = Vy-Vx, VF = !borrow of dif
            { 
            int8_t dif = chip8->registers.V[y] - chip8->registers.V[x];
            chip8->registers.V[x] = dif;
            chip8->registers.V[0xf] = dif > 0? 1 : 0;
            break;
            }
            
        case 0x800e: //0x8xye VF = Vx << 1
            {
            uint8_t bit7 = (chip8->registers.V[x] & 0x80) >> 7;  
            chip8->registers.V[x] <<= 1; 
            chip8->registers.V[0xf] = bit7;
            break;
            }
        case 0x9000: //0x9xy0 skip next if Vx != Vy
            if(chip8->registers.V[x] != chip8->registers.V[y]){  
                chip8->registers.PC += 2; 
            }
            break;
        default:
            break;
    }

    switch(opcode & 0xf0ff){
        case 0xE09E: //skip next if key in vx is pressed
            {
            int key = chip8->registers.V[x];
            if(chip8_keyboard_is_down(&chip8->keyboard, key)){
                chip8->registers.PC += 2;
            }
            }
            break;

        case 0xE0A1: //skip next if key in vx is not pressed
            {
            int key = chip8->registers.V[x];
            if(!chip8_keyboard_is_down(&chip8->keyboard, key)){
                chip8->registers.PC += 2;
            }
            }
            break;

        case 0xF007: // Vx = DT
            chip8->registers.V[x] = chip8->registers.DT; 
            break; 
        
        case 0xF00A: // wait for a key press, store the value of the key in Vx
                     // stop execution until key is pressed
            {
            char pressed_key = chip8_wait_for_key_press(chip8);
            chip8->registers.V[x] = pressed_key;
            }
            break; 

        case 0xF015: //DT = Vx
            chip8->registers.DT = chip8->registers.V[x]; 
            break; 
            
        case 0xF018: //ST = Vx
            chip8->registers.ST = chip8->registers.V[x]; 
            break; 

        case 0xF01E: // I = I + Vx
            chip8->registers.I += chip8->registers.V[x];
            break;

        case 0xF029: // I = location of sprite for digit[0-F] Vx
            chip8->registers.I = 5 * chip8->registers.V[x];
            break;

        case 0xF033: //store BCD representation of Vx in 
                     //memory locations I, I+1 and I+2
            {
            uint8_t hundreds = chip8->registers.V[x] / 100;
            uint8_t tens = chip8->registers.V[x] / 10 % 10;
            uint8_t units = chip8->registers.V[x] % 10;
            chip8_memory_write(&chip8->memory, chip8->registers.I, hundreds);
            chip8_memory_write(&chip8->memory, chip8->registers.I+1, tens);
            chip8_memory_write(&chip8->memory, chip8->registers.I+2, units);
            }
            break;
        
        case 0xF055: //store registers V0 through Vx in memory
                     //starting at location I
            {
            uint16_t address = chip8->registers.I;
            for(int i = 0; i <= x; i++){
                chip8->memory.memory[address+i] = chip8->registers.V[i];
            }
            }
            break;

        case 0xF065:
            {
            uint16_t address = chip8->registers.I;
            for(int i = 0; i <= x; i++){
                chip8->registers.V[i] = chip8->memory.memory[address+i];
            }
            }
            break;

        default:
            break;
    }
}
