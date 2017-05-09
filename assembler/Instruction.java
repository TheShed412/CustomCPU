
public class Instruction
{
	int opcode;
	int register;
	int immediate;

	/*
	*/

	public Instruction(String strOp, String strReg, String strImm)
	{
		opcode = Integer.parseInt(strOp);
	}
}//Instruction
