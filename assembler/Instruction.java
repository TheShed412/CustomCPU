
public class Instruction
{
	int opcode;
	int register1;
	int register2;
	int immediate;

	/*
		The instructions will be similar to x86
	*/

	public Instruction (int op, int reg1, int reg2, int imm)
	{
		opcode 		= op;
		register1	= reg1;
		register2	= reg2;
		immediate	= imm;
	}//constructor

	public String toHex()
	{
		int machineInt = opcode+register1+register2+immediate;

		return String.format("0x%04X", machineInt);
	}
}//Instruction
