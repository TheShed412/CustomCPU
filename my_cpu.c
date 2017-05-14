#include <stdio.h>
#include <stdlib.h>
#include "my_cpu.h"

static void jump(CPU**, ROM**, word);

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
		parts[1]: register1 (bits 11-10)
		parts[2]: register2 (bits 9-8)
		parts[3]: immediate (bits 7-0)
	*/

	/*and them to get the right values*/
	word opcode = curr_instruct & 0xF000;
	word reg1	= curr_instruct & 0xC00;
	word reg2	= curr_instruct & 0x300;
	word imm 	= curr_instruct & 0xFF;

	/*shift to make it easier*/	
	parts[0] = opcode >> 12;
	parts[1] = (reg1 >> 10);
	parts[2] = (reg2 >> 8);
	parts[3] = imm;
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

void load_or_store(word tick, word reg1, word reg2, word immediate, word opcode, CPU* cpu)
{
	word reg_imm = 0; /*this will be the thing stored in the register plus the imm*/

	switch (opcode) {
		/*load*/
		case 0x8:
		reg_imm = cpu->V[reg2] + immediate;// index of the memory I want
		register_file(tick, reg1, cpu->memory[reg_imm], cpu);
		printf("load: %d\n", cpu->memory[reg_imm]);
		break;

		/*store*/
		case 0x9:
		reg_imm = cpu->V[reg2] + immediate;
		//register_file(tick, reg1, cpu->memory[reg_imm], cpu);
		cpu->memory[reg_imm] = cpu->V[reg1];
		printf("store: %d\n", cpu->V[reg1]);
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
void alu(word tick, word reg1, word reg2, word immediate, word opcode, CPU* cpu)
{
    switch (opcode) {
        /*Set operation. reg_2 will be an immediate*/
        case 0x0:
			register_file(tick, reg1, immediate, cpu);
            break;

        /*Add operation*/
        case 0x2:
			register_file(tick, reg1, (cpu->V[reg1]+cpu->V[reg2]), cpu);
            break;

        /*Subtraction operation*/
        case 0x3:
			register_file(tick, reg1, (cpu->V[reg1]-cpu->V[reg2]), cpu);
            break;

        /*or operation*/
        case 0x4:
			register_file(tick, reg1, (cpu->V[reg1]|cpu->V[reg2]), cpu);
            break;

        /*and operation*/
        case 0x5:
			register_file(tick, reg1, (cpu->V[reg1]&cpu->V[reg2]), cpu);
            break;

        /*wtf happened*/
        default:
            printf("%s\n", "not supported operation");
			printf("%x", opcode);
			exit(1);
    }/*switch*/

}/*alu*/

/*
	These will be the commands that jump:
	beq		
	bne
	jmp
	fnc
*/

void jump_ops(word reg1, word reg2, word imm, word opcode, CPU* cpu, ROM* rom)
{
	switch(opcode){
		/*jump*/
		case 0xB:
			jump(&cpu, &rom, imm);
		break;

		/*beq*/
		case 0xF:
			if(reg1 == reg2) jump(&cpu, &rom, imm);
		break;

		/*bne*/
		case 0x7:
			if(reg1 != reg2) jump(&cpu, &rom, imm);
		break;

		/*fnc*/
		/*fnc (line number?)*/
		/*ths'll be a bit complicated...*/
		case 0x6:
		break;
	}/*switch*/
}/*jumpops*/

static void jump(CPU** _cpu, ROM** _rom, word index)
{
	/*gonna do jump stuff*/
	CPU* cpu = *_cpu;
	ROM* rom = *_rom;

	cpu->pc = index;
	cpu->opcode = rom->instructions[cpu->pc];
}/*jump*/

void register_file(word tick, word reg_write, word input, CPU* cpu)
{
    if(tick==0){
		//printf("%s\n", "REG");
        cpu->V[reg_write] = input;
    }/*checks for the down tick ie tick = 0*/

}/*register_file*/
