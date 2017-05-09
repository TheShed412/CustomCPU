#include <stdio.h>
#include <stdlib.h>
#include "my_cpu.h"
#define TEST 3


CPU cpu;
ROM rom;

/*
	All of these need to take a ROM and/or a CPU pointer now.
*/

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
	This will be what runs when the load and store instructions are run
	the memory is 4k and just a single array of chars.

	read_register will be the register to read from, the other will be the store

	immediate will be the offset of the read_register

	lw will load whatever is in memory at used_register+immediate in to the
	other register

	sw will store whatever is in used_register at the other_register+immediate
*/

void load_or_store(word tick, word used_register, word immediate, word opcode)
{
	word reg_imm = 0; /*this will be the thing stored in the register plus the imm*/
	word other_reg = !used_register; /*the other register*/

	switch (opcode) {
		/*load*/
		case 0x8:
		reg_imm = cpu.V[used_register] + immediate;// index of the memory I want
		register_file(tick, other_reg, cpu.memory[reg_imm]);
		break;

		/*store*/
		case 0x9:
		reg_imm = cpu.V[other_reg] + immediate;
		register_file(tick, used_register, cpu.memory[reg_imm]);
		break;
	}/*switch*/
}/*load_or_store*/

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
    if(tick==0){
		//printf("%s\n", "REG");
        cpu.V[reg_write] = input;
    }/*checks for the down tick ie tick = 0*/

}/*register_file*/
