
public class Instruction
{
	int opcode;
	int registerResult;
	int registerFrom;
	int immediate;

	/*
		The instructions will be similar to x86
	*/

	public Instruction (String strOp, String strReg1, String strReg2, String strImm)
	{
		opcode 			= Integer.parseInt(strOp);
		registerResult 	= Integer.parseInt(strReg1);
		registerFrom	= Integer.parseInt(strReg2);
		immediate		= Integer.parseInt(strImm);
	}//constructor
}//Instruction
