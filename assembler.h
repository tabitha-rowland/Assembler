/*
 * This file includes common system header files, several local header
 * files widely used in the assembler program, and signatures for other
 * commonly used functions.
 */

#ifndef _ASSEMBLER_H
#define _ASSEMBLER_H

#include <stdio.h>
#include <stdlib.h>     /* May need to be _stdlib.h on some machines. */
#include <string.h>	/* Might be memory.h on some machines. */
#include <ctype.h>

#include "LabelTableArrayList.h"
#include "getToken.h"
#include "printFuncs.h"
#include "process_arguments.h"
#include "same.h"

LabelTableArrayList pass1 (FILE * fp);
void pass2 (FILE * fp, LabelTableArrayList * table);

int getNTokens (char * instructionBuffer, int N, char * results[]);

void getInstName(char * input, char ** instrName, char **restOfLine);

int getOpCode(char * instrName);
int getFunctCode(char * instrName);

void processIorJ(int lineNum, LabelTableArrayList * table,
                 int opcode, char * restOfInstruction, int PC);
void processR(int lineNum, int functCode, char * restOfInstruction);

void printInt(int value, int length);
void printReg(char * regName, int lineNum);
void printIntInString(char * intInString, int numBits, int lineNum);
void printJumpTarget(char * targetLabel, LabelTableArrayList * table,
                     int lineNum);
void printBranchOffset(char * targetLabel, LabelTableArrayList * table,
                       int PC, int lineNum);

#endif
