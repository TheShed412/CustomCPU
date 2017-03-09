#include <stdio.h>
#include "my_cpu.h"

CPU cpu;

int main(int argc, char const *argv[]) {

    cpu.opcode = 0x00ff;

    return 0;
}

/*
takes in the two registers and does the operation specified
returns the result
won't worry about carry outs or ins
I might need to edit since there are only two registers.
I might have it only take one register that we will store
the result of doing the operation on the two registers.
Cause that's how the lab went, but this will make it
easier to reuse in the future.

I dunno  ¯\_(ツ)_/¯
*/

byte alu(byte reg_1, byte reg_2, byte opcode){

    switch (opcode) {
        /*Set operation. reg_2 will be an immediate*/
        case 0x0:
            reg_1 = reg_2;
            break;

        /*Add operation*/
        case 0x2:
            reg_1 += reg_2;
            break;

        /*Subtraction operation*/
        case 0x3:
            reg_1 -= reg_2;
            break;

        /*or operation*/
        case 0x4:
            reg_1 = reg_1|reg_2;
            break;

        /*and operation*/
        case 0x5:
            reg_1 = reg_1&reg_2;
            break;

        /*wtf happened*/
        default:
            printf("%s\n", "not supported operation");
    }/*switch*/

    return reg_1;
}/*alu*/
