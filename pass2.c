/**
 * void pass2 (FILE * fp, LabelTableArrayList * table)
 *      @param  fp  pointer to an open file (stdin or other file pointer)
 *                  from which to read lines of assembly source code
 *      @param  table  a pointer to an existing Label Table
 *
 * This program goes through the MIPS code a second time, looking for arguments i.e. 
 * register numbers, instruction name, constants, and shift amounts. It then finds these 
 * and converts the given argument into its pseudo-binary code version. It prints out 
 * full, 32 bit, binary instructions. 
 *
 * Author: Tabitha Rowland
 * Date:   3/8/2022
 *
 * Modified by:  
 *      Why?
 *
 */

#include "assembler.h"
#include <stdlib.h>
#include <ctype.h>

void pass2 (FILE * fp, LabelTableArrayList * table)
{
    int    lineNum;            /* line number */
    int    PC = 0;             /* program counter */
    char   inst[BUFSIZ];       /* will hold instruction; BUFSIZ is max size
                                    of I/O buffer (defined in stdio.h) */
    char * instrName;          /* instruction name (e.g., "add") */
    char * restOfInstruction;  /* rest of instruction (e.g., "$t0, $t1, $t2") */

    /* Continuously read next line of input until EOF is encountered.
     */
    for (lineNum = 1; fgets (inst, BUFSIZ, fp); lineNum++)
    {
        PC += 4;

        /* Separate the instruction name from the rest of the statement.
         * If the line does not have an instruction, move on to next line.
         */
        getInstName(inst, &instrName, &restOfInstruction);
        if ( instrName == NULL )
            continue; /* Go to top of loop to read next line of input. */

        printDebug ("First non-label token is: %s\n", instrName);

        /* Determine whether this is an R-format, I-format, or J-format
         * instruction based on the opcode.  If it is an R-format
         * instruction, get the funct code also.  Then process the
         * instruction.
         */
        int opcode = getOpCode(instrName);
        printDebug("%s instruction has opcode %d.\n", instrName, opcode);
        if ( opcode == 0 )
        {
            int functCode = getFunctCode(instrName);
            printDebug("%s instruction has funct code %d.\n",
                    instrName, functCode);
            if ( functCode == -1 )
            {
                /* Print error message - this is not a valid instruction!  */
                printf("Invalid instruction %s on line %d.\n", instrName,
                        lineNum);
                continue; /* Go to top of loop to read next line of input. */
            }

            processR(lineNum, functCode, restOfInstruction);
        }
        else
        {
            processIorJ(lineNum, table, opcode, restOfInstruction, PC);
        }
    }

    return;
}


/* Checks the opcode name with the I, J, and R formats, and
 *  returns the corresponding opcode. If the instrName is
 *  not one of those, it returns -1.
 *    @param instrName      name of instruction (input)
 *    @return  the opCode if instrName is a valid I or J format instruction,
 *             or 0 (i.e., if instrName is a valid R format instruction). -1 
 *              is not a valid opcode at all. 
 */
int getOpCode(char * instrName)
{
    
    int opcode = 0;
    if ( strcmp(instrName, "beq") == SAME ) //
        opcode = 4;
    else if (strcmp(instrName, "bne") == SAME)
        opcode = 5;
    else if (strcmp(instrName, "addi") == SAME)
        opcode = 8;
    else if (strcmp(instrName, "addiu") == SAME)
        opcode = 9;
    else if (strcmp(instrName, "slti") == SAME)
        opcode = 10;
    else if (strcmp(instrName, "sltiu") == SAME)
        opcode = 11;
    else if (strcmp(instrName, "andi") == SAME)
        opcode = 12;
    else if (strcmp(instrName, "ori") == SAME)
        opcode = 13;
    else if (strcmp(instrName, "lui") == SAME)
        opcode = 15;
    else if (strcmp(instrName, "lw") == SAME)
        opcode = 35;
    else if (strcmp(instrName, "sw") == SAME) //end of I format instructions
        opcode = 43;
    else if (strcmp(instrName, "j") == SAME) //beginning of J format
        opcode = 2;
    else if (strcmp(instrName, "jal") == SAME) //end of J instruct
        opcode = 3;
    else if (strcmp(instrName, "jal") == SAME) //beginning of R
        opcode = 3;
    else if (strcmp(instrName, "sll") == SAME)
        opcode = 0;
    else if (strcmp(instrName, "srl") == SAME)
        opcode = 0;
    else if (strcmp(instrName, "jr") == SAME)
        opcode = 0;
    else if (strcmp(instrName, "add") == SAME)
        opcode = 0;
    else if (strcmp(instrName, "addu") == SAME)
        opcode = 0;
    else if (strcmp(instrName, "sub") == SAME)
        opcode = 0;
    else if (strcmp(instrName, "subu") == SAME)
        opcode = 0;
    else if (strcmp(instrName, "and") == SAME)
        opcode = 0;
    else if (strcmp(instrName, "or") == SAME)
        opcode = 0;
    else if (strcmp(instrName, "nor") == SAME)
        opcode = 0;
    else if (strcmp(instrName, "slt") == SAME)
        opcode = 0;
    else if (strcmp(instrName, "sltu") == SAME)
        opcode = 0;
    else //if its not these, then it is not a valid MIPS instruction. 
    {
        printDebug("This is an invaid opcode: %s \n", instrName);
        return -1;
        }
    
    return opcode;
}

/* Checks the functcode name with the R formats, and
 *  returns the corresponding functcode. If the instrName is
 *  not one of those, it returns -1.
 *    @param instrName      name of instruction (input)
 *    @return  the funct code if instrName is a valid R format instruction, 
 *             or -1 if instrName is not a valid R format instruction
 */
int getFunctCode(char * instrName)
{
    int functCode = 0;
    if ( strcmp(instrName, "sll") == SAME )
        functCode = 0;
    else if ( strcmp(instrName, "srl") == SAME )
        functCode = 2;
    else if ( strcmp(instrName, "jr") == SAME )
        functCode = 8;
    else if ( strcmp(instrName, "add") == SAME )
        functCode = 32;
    else if ( strcmp(instrName, "addu") == SAME )
        functCode = 33;
    else if ( strcmp(instrName, "sub") == SAME )
        functCode = 34;
    else if ( strcmp(instrName, "subu") == SAME )
        functCode = 35;
    else if ( strcmp(instrName, "and") == SAME )
        functCode = 36;
    else if ( strcmp(instrName, "or") == SAME )
        functCode = 37;
    else if ( strcmp(instrName, "nor") == SAME )
        functCode = 39;
    else if ( strcmp(instrName, "slt") == SAME )
        functCode = 42;
    else if ( strcmp(instrName, "sltu") == SAME )
        functCode = 43;
    else /* instrName not recognized */
        {printDebug("This is an invaid functcode: %s \n", instrName);
        functCode = -1;}
    
    return functCode;
}


/* Takes the functcode and checks for how many arguments there are, then looks for them.
 * Formats them in the correct order, and returns it.
 *
 * When getNTokens encounters an error, it puts a pointer to the error
 * message in arguments[0].
 */
void processR(int lineNum, int functCode, char * restOfInstruction)
{
    char * arguments[3];      /* registers or values after name; max of 3 */
    int numOperands;

    if (functCode == -1) //if functcode is invalid
    {
        printError("Functcode is invalid on line %d.\n", lineNum);
        return;
    }

    /* JR only has 1 operand; all other R-format instructions have 3. */
    if ( functCode == 8 )
    {
        numOperands = 1;
    }
    else
    {
        numOperands = 3;
    }
    
    /* Get arguments.  (Depending on instruction, should be 1, 2, or 3.) */
    if ( ! getNTokens(restOfInstruction, numOperands, arguments) )
    {
        printError("Error on line %d: %s\n", lineNum, arguments[0]);
        return;
    }

    /* Process arguments and print machine code version of instruction. */
    if ( functCode == 8 )       /* Handle jr instruction */
    {
        printDebug("jr \"%s\" on line %d. \n", arguments[0], lineNum);


        printInt(0, 6); //opcode
        printReg(arguments[0], lineNum); 
        printInt(0, 15); //zeros, empty space after the one and only reg num
        printInt(functCode, 6);
        printf(" \n");


    }
    else if ( functCode == 0 || functCode == 2 )     // Handle sll and srl
      {
            // Shift amount is a number in a string, not an int
            printDebug("This is an sll or an srl. funct: %d. reg1: %s. reg2: %s. shift amount = %s. On line %d. \n", functCode, arguments[0], arguments[1], arguments[2], lineNum);
            printInt(0, 6); //opcode
            printInt(0, 5); //zero for 5 bits
            printReg(arguments[1], lineNum);
            printReg(arguments[0], lineNum); //check with mips instruction table, the format is wonky for lots of them
            printIntInString(arguments[2], 5, lineNum);
            printInt(0, 6);
            printf(" \n");
      }
    
    else            /* Handle common format for add, etc. */
    {
        printDebug("funct %d \"%s\", \"%s\", and \"%s\" on line %d.\n", functCode,
                            arguments[1], arguments[2], arguments[0], lineNum);

        /* Print binary for the opcode, registers, shift amount,
         * and funct code.
         */
        
        printInt(0, 6);
        printReg(arguments[1], lineNum);
        printReg(arguments[2], lineNum);
        printReg(arguments[0], lineNum);
        printInt(0, 5);
        printInt(functCode, 6);
        printf(" \n");
    }

}

/* Takes the opcode and checks for how many arguments there are, then looks for them.
 * Formats them in the correct order along with their opcodes, and returns it.
 *
 * When getNTokens encounters an error, it puts a pointer to the error
 * message in arguments[0].
 */
void processIorJ(int lineNum, LabelTableArrayList * table,
                 int opcode, char * restOfInstruction, int PC)
{
    char * arguments[3];      /* registers or values after name; max of 3 */
    int numOperands;

    if (opcode == -1) //if opcode is invalid
    {
        printError("Opcode is invalid on line %d.\n", lineNum);
        return;
    }

    if ( opcode == 15 ) //lui has 2 only
    {
        numOperands = 2;
    }
    else if ( opcode == 2 || opcode == 3 ) //j or jal has 1 arg
    {
        numOperands = 1;
    }
    else
    {
        numOperands = 3;
    }


    /* Get arguments.  (Depending on instruction, should be 1, 2, or 3.) */
    if ( ! getNTokens(restOfInstruction, numOperands, arguments) )
    {
        printError("Error on line %d: %s\n", lineNum, arguments[0]);
        return;
    }

    if ( opcode == 15 )       /* Handle lui instruction */
    {
        printDebug("lui \"%s\", \"%s\"\n", arguments[0], arguments[1]);


        printInt(opcode, 6); //opcode
        printInt(0, 5);
        printReg(arguments[0], lineNum); 
        printIntInString(arguments[1], 16, lineNum); //constant, takes up 16 bits
        printf("\n");

    }
    else if ( opcode == 35 || opcode == 43) //lw or sw
    {
        printDebug("This is a lw or sw, reg1 is %s, constant is %s, reg2 is %s.\n",arguments[0],arguments[1],arguments[2]);
        printInt(opcode, 6); //opcode
        printReg(arguments[2], lineNum);
        printReg(arguments[0], lineNum);
        printIntInString(arguments[1], 16, lineNum);
        printf("\n");
    }
    else if ( opcode == 4 || opcode == 5) //beq, bne
    {
        int intConstant = atoi(arguments[2]);
        char * targetLabel;

        printDebug("opcode: %d, reg1: %s, reg2: %s, constant: %s. On line %d. \n", opcode, arguments[0], arguments[1], arguments[2], lineNum);
        printInt(opcode, 6); //opcode
        printReg(arguments[0], lineNum);
        printReg(arguments[1], lineNum);
        if (atoi(arguments[2]) == 0) //if the string contains letters, it returns 0. 
        {
            targetLabel = arguments[2];
            printBranchOffset(targetLabel, table, PC, lineNum);
            }
        else {
            intConstant = atoi(arguments[2]);
            printInt(intConstant, 16); } //constant
        printf("\n");

    }
    else if (opcode == 2 || opcode == 3 ) //j or jal
    {
        char * targetLabel;
        int intConstant;
        
        printDebug("opcode: %d, constant: %s, On line %d. \n", opcode, arguments[0], lineNum);
        printInt(opcode, 6); //opcode
        if (atoi(arguments[0]) == 0) //if the string contains letters, it returns 0. 
        {
            targetLabel = arguments[0];
            printJumpTarget(arguments[0], table, lineNum); //constant
            }
        else {
            intConstant = atoi(arguments[0]);
            printInt(intConstant, 26); } //constant
         
        printf("\n");
    }
    
    else //this is the format for all other I and J 
    {   printDebug("opcode: %d, reg1: %s, reg2: %s, constant: %s. On line %d. \n", opcode, arguments[0], arguments[1], arguments[2], lineNum);
        printInt(opcode, 6); //opcode
        printReg(arguments[1], lineNum);
        printReg(arguments[0], lineNum);
        printIntInString(arguments[2], 16, lineNum); //constant
        printf("\n");
    }

}

