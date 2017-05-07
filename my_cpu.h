#ifndef CHIP8
#define CHIP8
#define word unsigned short     /*Because I use it a lot and I'm tired of typing
                                  all of the words :p*/

typedef struct {
    unsigned short  opcode;             /*the current opcode*/
    unsigned char   memory[4096];       /*ram 4k...I don't really use this yet*/
    unsigned char   V[2];               /*registers*/
    unsigned short  pc;                 /*program counter*/
    unsigned char   _clock;             /*clock triggered at 0, runs at 1mhz*/
} CPU;

typedef struct {
    unsigned short instructions[1000];      /*ROM for holding instructions. 16-bit instruction set*/
} ROM;

void register_file(word tick, word reg_write, word input);
void alu(word, word, word, word);
void splitter(word, word*);
void load_or_store(word, word, word, word);

#endif
