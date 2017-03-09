#include <stdio.h>
#include "my_cpu.h"

CPU cpu;

int main(int argc, char const *argv[]) {

    cpu.opcode = 0x00ff;

    return 0;
}

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

byte alu(byte result_register, byte immediate, byte opcode){
    byte ret_val;
    switch (opcode) {
        /*Set operation. reg_2 will be an immediate*/
        case 0x0:
            ret_val = immediate;
            break;

        /*Add operation*/
        case 0x2:
            ret_val = cpu.V[0]+cpu.V[1];
            break;

        /*Subtraction operation*/
        case 0x3:
            ret_val = cpu.V[0]-cpu.V[1];
            break;

        /*or operation*/
        case 0x4:
            ret_val = cpu.V[0]|cpu.V[1];
            break;

        /*and operation*/
        case 0x5:
            ret_val = cpu.V[0]&cpu.V[1];
            break;

        /*wtf happened*/
        default:
            printf("%s\n", "not supported operation");
    }/*switch*/
    return ret_val;
}/*alu*/

void register_file(byte tick, byte reg_write, byte input){
    if(!tick){
        cpu.V[reg_write] = input;
    }/*checks for the down tick ie tick = 0*/

}/*register_file*/
