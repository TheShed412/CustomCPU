#include <stdio.h>
#include "my_cpu.h"

CPU cpu;

int main(int argc, char const *argv[]) {

    cpu.opcode = 0x00ff;

    return 0;
}

/*takes in tbe two registers and does the operation specified*/

unsigned short alu(unsigned short reg_1, unsigned short reg_2, unsigned short opcode){

}
