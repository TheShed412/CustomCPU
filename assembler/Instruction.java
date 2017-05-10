
public class Instruction
{
	int opcode;
	int register;
	int immediate;

	/*
		The instructions will be similar to x86
	*/

	public Instruction (int op, int reg,+++++ int imm)
	{
		opcode 		= op;
		register	= reg;
		immediate	= imm;
	}//constructor

	public String toHex()
	{
		int machineInt = opcode+register+immediate;

		return String.format("0x%04X", machineInt);
	}
}//Instruction
