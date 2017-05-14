#ifndef TAN_CPU
#define TAN_CPU

#define word unsigned short
#define RAM_SIZE 4096
#define STACK_BASE 4095
 /*Because I use it a lot and I'm tired of typing
                                  all of the words :p*/

typedef struct {
    unsigned short  opcode;             /*the current opcode*/
    unsigned char   memory[RAM_SIZE];   /*ram 4k*/
    unsigned char   V[4];               /*registers*/
    unsigned short  bp;                 /*base pointer*/
    unsigned short  sp;                 /*stack pointer*/
    unsigned short  pc;                 /*program counter*/
    unsigned short  ra;                 /*return address*/
    unsigned char   _clock;             /*clock triggered at 0, runs at 1mhz*/
} CPU;

typedef struct {
    unsigned short instructions[1000];      /*ROM for holding instructions. 16-bit instruction set*/
} ROM;

void register_file(word tick, word reg_write, word input, CPU*);
void alu(word, word, word, word, word, CPU*);
void splitter(word, word*);
void load_or_store(word, word, word, word, word, CPU*);
void jump_ops(word, word, word, word, CPU*, ROM*);

#endif
