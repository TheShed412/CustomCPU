#ifndef CHIP8
#define CHIP8

typedef struct {
    unsigned short  opcode;             /*the current opcode*/
    unsigned char   memory[4096];       /*ram 4k ;)*/
    unsigned char   V[2];               /*registers*/
    unsigned short  pc;                 /*program counter*/
    unsigned char   _clock;             /*clock triggered at 0, runs at 60hz*/
} CPU;

typedef struct {
    unsigned short instructions[1000];      /*ROM for holding instructions. 16-bit instruction set*/
} ROM;

unsigned short alu(unsigned short, unsigned short, unsigned short);

#endif
