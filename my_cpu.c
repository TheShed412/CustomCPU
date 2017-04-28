#include <stdio.h>
#include <stdlib.h>
#include "my_cpu.h"
#define TEST 3

static void copy_to_rom(word* to_rom, int size);

CPU cpu;
ROM rom;

/*
	This will take a file for the input that has the ROM instructions on it.
	At the top of the file should be the number of instructions in the
	file.
*/

int main(int argc, char const *argv[]) {
	/*PC will just be the index for the ROM*/
	FILE* input = fopen(argv[1], "r");
	int size = 0;

	if(input){
		size = (fgetc(input)-48);
		printf("%d\n", size);
	} else {
		fprintf(stderr, "%s\n", "FILE COULD NOT OPEN");
		return 1;
	}

	// word split_ins[3];
	//
	// int i;
	// for(i=0; i<TEST; i++){
	// 	splitter(rom.instructions[i], split_ins);
	// 	alu(0, split_ins[1], split_ins[2], split_ins[0]);
	// }
	//
	// printf("A: %d\n", cpu.V[0]);
	// printf("B: %d\n", cpu.V[1]);

	fclose(input);
    return 0;
}


static void copy_to_rom(word* to_rom, int size)
{
	int i;
	for(i=0; i< size; i++)
		rom.instructions[i] = to_rom[i];
}


/*
	This will split the instructions in to the right parts
	then put it in an array and return it
*/
void splitter(word curr_instruct, word* parts)
{
	/*
		TODO: split the thing into:
		parts[0]: opcode (bits 15-12)
		parts[1]: register (bit 11)
		parts[2]: immediate (bits 7-0)
	*/

	word opcode = curr_instruct & 0xF000;
	word reg	= curr_instruct & 0x800;
	word imm 	= curr_instruct & 0xFF;

	parts[0] = opcode >> 12;
	parts[1] = reg >> 11;
	parts[2] = imm;
}/*splitter*/

/*
Decided to emmulate the alu from my old lab exactly.

Takes three args:
result_register - the register the result will be put in.
                  It will just take the array value of the
                  register.

immediate - if the operation takes an immediate value,
            this will be that. 0 otherwise.

opcode - what the operation will be
*/
void alu(word tick, word result_register, word immediate, word opcode)
{

    switch (opcode) {
        /*Set operation. reg_2 will be an immediate*/
        case 0x0:
			register_file(tick, result_register, immediate);
            break;

        /*Add operation*/
        case 0x2:
			register_file(tick, result_register, (cpu.V[0]+cpu.V[1]));
            break;

        /*Subtraction operation*/
        case 0x3:
			register_file(tick, result_register, (cpu.V[0]-cpu.V[1]));
            break;

        /*or operation*/
        case 0x4:
			register_file(tick, result_register, (cpu.V[0]|cpu.V[1]));
            break;

        /*and operation*/
        case 0x5:
			register_file(tick, result_register, (cpu.V[0]&cpu.V[1]));
            break;

        /*wtf happened*/
        default:
            printf("%s\n", "not supported operation");
    }/*switch*/

}/*alu*/

void register_file(word tick, word reg_write, word input)
{
    if(!tick){
        cpu.V[reg_write] = input;
    }/*checks for the down tick ie tick = 0*/

}/*register_file*/
