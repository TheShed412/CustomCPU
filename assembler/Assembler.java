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
		System.out.println(String.format("0x%04X", op));
	}//translate

	private static int getOpcode(String assOp)
	{
		int machineOp = -1;
		switch(assOp){
			case "set":
				machineOp = 0x0;
			break;

			case "add":
				machineOp =	0x2000;
			break;

			case "sub":
				machineOp =	0x3000;
			break;

			case "or":
				machineOp =	0x4000;
			break;

			case "and":
				machineOp =	0x5000;
			break;

			case "lm":
				machineOp =	0x8000;
			break;

			case "sm":
				machineOp =	0x9000;
			break;
		}
		return machineOp;
	}
}//classs
