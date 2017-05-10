import java.io.BufferedReader;
import java.io.File;
import java.io.FileReader;
import java.io.IOException;

public class Assembler
{
	/*
		I want the instructions to be similar to x86:
		op r1 r2 imm*
		op r1 imm

		the imm will only be there if r2 is a memory address and imm is the offset.

		operations:
		set
		add
		sub
		or
		and
		lm (load from memory)
		sm (store to memory)
		beq (NA)
		bne (NA)
		jmp (NA)
		fnc (NA)
	*/
	public static void main(String[] args)
	{
		try{
			String fileName = args[0];
			File assFile = new File(fileName);
			FileReader assFileReader = new FileReader(assFile);
			BufferedReader buffAss = new BufferedReader(assFileReader);
			//StringBuffer strBuff = new StringBuffer();
			String instruction;
			while ((instruction = buffAss.readLine()) != null){
				//stuff happens
				String[] parts = instruction.split(" ");// get the parts that will translate to machine code
				translate(parts);
			}//while
			assFileReader.close();
		} catch(Exception e){e.printStackTrace();}
	}//main

	private static void translate(String[] assembly)
	{
		int op = getOpcode(assembly[0]);
	}//translate

	private static int getOpcode(String assOp)
	{
		return 0;
	}
}//classs
