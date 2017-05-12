
#include <stdio.h>
#include <stdlib.h>
#include "my_cpu.h"
#define TEST 3

static void copy_to_rom(FILE* to_rom);
static void cpu_run_loop(); /*the main loop*/
static void emulate_cycle(unsigned long); /*emulates a single cycle of the cpu*/

CPU cpu;
ROM rom;

/*
	TODO:
	1) Make seperate CPU FILE (kinda done)
	2) Add more registers
	3) jump
	4) beq bne
	5) make assembler in java
	6) make stack pointer (not in register array)
*/

int main(int argc, char const *argv[]) {
	/*PC will just be the index for the ROM*/
	FILE* input = fopen(argv[1], "r");

	if(input){
		copy_to_rom(input); /*getting the instructions in ROM*/
		cpu_run_loop();
	} else {
		fprintf(stderr, "%s\n", "FILE COULD NOT OPEN");
		return 1;
	}

	/*// word split_ins[3];
	//
	// int i;
	// for(i=0; i<TEST; i++){
	// 	splitter(rom.instructions[i], split_ins);
	// 	alu(0, split_ins[1], split_ins[2], split_ins[0]);
	// }
	//
	// printf("A: %d\n", cpu.V[0]);
	// printf("B: %d\n", cpu.V[1]);*/

	fclose(input);
    return 0;
}

static void cpu_run_loop()
{
	cpu.pc 		= 0;
	cpu._clock 	= 0;
	cpu.opcode	= 0;
	unsigned long tick_tock = 0;

	while(1){
		if(!cpu._clock) emulate_cycle(tick_tock); /*where shit goes down*/
		//printf("%li\n", tick_tock);
		tick_tock++;
	}
}/*cpu_run_loop*/

static void emulate_cycle(unsigned long tick_tock)
{
	/*get opcode*/
	word operate = ((word)tick_tock % 20000);
	word split[3];
	//printf("%d\n", operate);
	if(operate==0){
		cpu.opcode = rom.instructions[cpu.pc];
		cpu.pc++;
		/*decode opcode*/
		printf("%x\n", cpu.opcode);
		splitter(cpu.opcode, split);
	}
	/*execute opcode*/

	if(split[0] == 0xF) exit(0); /*everything ran successfully*/

	//printf("%d\n", split[0]);

	if(split[0] == 0x8 || split[0] == 0x9)
		load_or_store(operate, split[1], split[2], split[3],/*opcode*/split[0], &cpu);
	else
		alu(operate, split[1], split[2], split[3], /*opcode*/split[0], &cpu);
	/*update clock*/
}/*emulate_cycle*/


static void copy_to_rom(FILE* ins_file)
{
	char c_ins[32];
	int size = 0;
	int temp = 0;

	while(fgets(c_ins, sizeof(c_ins), ins_file)){
		/*strtok to get rid of \n and sscanf to make it an integer
		  since it's exsitence is temporary anyways I dont care about it
		  I let it die in sscanf. What a cruel god I am.*/
		strtok(c_ins, "\n");
		sscanf(c_ins, "%x", &temp);
		rom.instructions[size] = temp;
		size++;
	}//while

	/*Test loop*/
	// int i;
	// for(i=0; i<size; i++){
	// 	printf("%x\n", rom.instructions[i]);
	// }
}//copy_to_rom
