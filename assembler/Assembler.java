public class Assembler
{
	/*
		I want the instructions to be similar to x86:
		op r1 r2 imm*
		op r1 imm

		the imm will only be there if r2 is a memory address and imm is the offset.
	*/
	public static void main(String[] args)
	{
		int op = 0x2000;
		int reg = 0x800;

		Instruction in = new Instruction(op, reg, 0);

		System.out.println(in.toHex());
	}
}//classs
