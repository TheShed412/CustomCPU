import java.io.BufferedReader;
import java.io.File;
import java.io.FileReader;
import java.io.IOException;
import java.io.PrintWriter;

public class Assembler
{
	/*
		I want the instructions to be similar to x86:
		memory operations:
		op r1 r2 imm
			r1 will be the register I save in/load from
			r2 will be the memory address
			imm will be the offset
		
		alu operations:
		op r1 r2/imm
			r1 will be the register the result is stored in
			r2 will be the thing that is added, can also be immediate

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
			//just setting up file stuff...
			String fileName = args[0];
			File assFile = new File(fileName);
			FileReader assFileReader = new FileReader(assFile);
			BufferedReader buffAss = new BufferedReader(assFileReader);
			//don't mind...it's just java being java...

			String machineFile = fileName.substring(0, (fileName.length()-3) ) + "tan";
			PrintWriter writeMach = new PrintWriter(machineFile, "UTF-8");

			String instruction;
			while ((instruction = buffAss.readLine()) != null){
				//stuff happens
				String[] parts = instruction.split(" ");// get the parts that will translate to machine code
				Instruction ins = translate(parts);

				writeMach.println(ins.toHex());
			}//while

			writeMach.println("0xF000");//command to stop cpu. Should be at the end of each file
			assFileReader.close();
			writeMach.close();
		} catch(Exception e){e.printStackTrace();}
	}//main

	private static Instruction translate(String[] assembly)
	{
		// 0000 00 00 00000000
		// op   r1 r2 imm
		// registers will be prefaced with an r
		int op 	= getOpcode(assembly[0]);
		int r2	= 0;
		int r1 = 0;
		int imm = 0;

		String r1Str 	= assembly[1];
		String r2imm 	= "";	// Can be immediate or the second register
		String immStr	= "";

		if(assembly.length > 2) r2imm = assembly[2];


		boolean aluOp  = (op == 0x0000 || op == 0x2000 || op == 0x3000 || op == 0x4000 || op == 0x5000);
		boolean memOp  = (op == 0x8000 || op == 0x9000);
		boolean jumpOP = (op == 0xB000 || op == 0xF000 || op == 0x7000 || op == 0x6000);

		if(!jumpOP){
			r1Str = r1Str.substring(1);
			r1 = Integer.parseInt(r1Str);
		}

		if(aluOp){ //if it's an alu operation
			if (r2imm.substring(0,1).equals("r")){	// if the first char is r, tis a register
				r2imm = r2imm.substring(1);
				r2 = Integer.parseInt(r2imm);
				//System.out.println(r2);
			} else { //else its an immediate

				imm = Integer.parseInt(r2imm);
			}//if else

		} else if (memOp) { // else it's a memory operation
			immStr = assembly[3];
			r2imm = r2imm.substring(1);
			r2 = Integer.parseInt(r2imm);
			imm = Integer.parseInt(immStr);
		} else if (jumpOP) { //else it's a jump operation
			// format:
			// jmp 12		(jumps to line 12)
			// beq r1 r2 12	(jumps to line 12 if r1 == r2)
			if (op == 0xB000){
				imm = Integer.parseInt(assembly[1]);
				r1 = 0;
				r2 = 0;
			} else {
				r2imm = r2imm.substring(1);
				r2 = Integer.parseInt(r2imm);
				imm = Integer.parseInt(immStr);
			}
		}//else if
		
		return new Instruction(op, r1, r2, imm);
	}//translate

	private static int getOpcode(String assOp)
	{
		int machineOp = -1;
		switch(assOp){
			case "set":
				machineOp = 0x0000;
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

			case "jmp":
				machineOp = 0xB000;
			break;

			case "beq":
				machineOp = 0xF000;
			break;

			case "bne":
				machineOp = 0x7000;
			break;

			case "fnc":
				machineOp = 0x6000;
			break;
		}//switch
		return machineOp;
	}//getOpCode
}//classs
