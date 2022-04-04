#include "assembler.h"

/*
 * The functions in this file print pseudo-binary output for:
 *    - integer values, e.g., 23
 *    - integer values represented as strings, e.g., "23"
 *    - registers, e.g., $zero ==> "00000"
 *    - jump targets
 *    - branch offsets
 * The pseudo-binary output actually consists of character 0's and 1's,
 * with the length of the binary output specified by the `numBits`
 * parameter.  The `lineNum` parameter is used when printing error
 * messages.
 *
 * Author(s): Alyce Brady, Tabitha Rowland
 * Date: 3/8/2022
 *      with assistance from:
 *      working side-by-side with:
 * 
 * Modification Log:
 *    - AB, 3/25/2020 - implement printIntInString, stub printInt,
 *                      provide skeletons for others
 *    - TR, 3/2/2022  - Implement printInt, printReg, printJumpTarget, and printBranchOffset.
 */

/* Print integer value in pseudo-binary (made up of character '0's and '1's).
 *      @param value   value to print in pseudo-binary
 *      @param length  length of binary code needed, in bits
 *      @pre           value can be represented in `length` number of bits
 *      @pre           value >= 0
 *   (You can decide whether or not to require that `value` be non-negative.)
 */
void printInt(int value, int length)
{
    /* Print the value passed as a parameter in "character binary" format.
     */

    printDebug("\n (%d)", value); //to see decimal value
    int binaryCheck = length-1; //decrease it by 1 because you are comparing if the value is bigger not smaller
    binaryCheck = 1 << binaryCheck; //shift that value i.e do 2^(length-1)
    printDebug("binary check! = %d, length = %d. value %d.\n", binaryCheck, length, value);

    printDebug("binary val: ");
    for (int i = (length-1) ; i >= 0; i = i-1) //read/check bin in left to right
        if (value >= binaryCheck)
            {printf("1");
            value = (value - binaryCheck);
            binaryCheck = (binaryCheck - (binaryCheck/2)); //go down a product of 2/ move on to next bit
             }
        else 
            {printf("0");
            binaryCheck = (binaryCheck - (binaryCheck/2));} 
    printDebug(" \n"); //it will all print on the same line until the for loops stops


}


/* Print register in pseudo-binary (made up of character '0's and '1's).
 *      @param regName   name of register to print in pseudo-binary
 *      @param lineNum   line number (for error messages)
 * If the register name passed as a parameter is an invalid register name,
 * this function prints "<invalid reg>" instead of the register number,
 * allowing the rest of the instruction to be parsed and printed.
 */
void printReg(char * regName, int lineNum)
{
    int regNum; 
    if ( strcmp(regName, "$zero") == SAME )
        regNum = 0;
    else if ( strcmp(regName, "$at") == SAME )
        regNum = 1;
    else if ( strcmp(regName, "$v0") == SAME )
        regNum = 2;
    else if ( strcmp(regName, "$v1") == SAME )
        regNum = 3;
    else if ( strcmp(regName, "$a0") == SAME )
        regNum = 4;
    else if ( strcmp(regName, "$a1") == SAME )
        regNum = 5;
    else if ( strcmp(regName, "$a2") == SAME )
        regNum = 6;
    else if ( strcmp(regName, "$a3") == SAME )
        regNum = 7;
    else if ( strcmp(regName, "$t0") == SAME )
        regNum = 8;
    else if ( strcmp(regName, "$t1") == SAME )
        regNum = 9;
    else if ( strcmp(regName, "$t2") == SAME )
        regNum = 10;
    else if ( strcmp(regName, "$t3") == SAME )
        regNum = 11;
    else if ( strcmp(regName, "$t4") == SAME )
        regNum = 12;
    else if ( strcmp(regName, "$t5") == SAME )
        regNum = 13;
    else if ( strcmp(regName, "$t6") == SAME )
        regNum = 14;
    else if ( strcmp(regName, "$t7") == SAME )
        regNum = 15;
    else if ( strcmp(regName, "$s0") == SAME )
        regNum = 16;
    else if ( strcmp(regName, "$s1") == SAME )
        regNum = 17;
    else if ( strcmp(regName, "$s2") == SAME )
        regNum = 18;
    else if ( strcmp(regName, "$s3") == SAME )
        regNum = 19;
    else if ( strcmp(regName, "$s4") == SAME )
        regNum = 20;
    else if ( strcmp(regName, "$s5") == SAME )
        regNum = 21;
    else if ( strcmp(regName, "$s6") == SAME )
        regNum = 22;
    else if ( strcmp(regName, "$s7") == SAME )
        regNum = 23;
    else if ( strcmp(regName, "$t8") == SAME )
        regNum = 24;
    else if ( strcmp(regName, "$t9") == SAME )
        regNum = 25;
    else if ( strcmp(regName, "$k0") == SAME )
        regNum = 26;
    else if ( strcmp(regName, "$k1") == SAME )
        regNum = 27;
    else if ( strcmp(regName, "$gp") == SAME )
        regNum = 28;
    else if ( strcmp(regName, "$sp") == SAME )
        regNum = 29;
    else if ( strcmp(regName, "$fp") == SAME )
        regNum = 30;
    else if ( strcmp(regName, "$ra") == SAME )
        regNum = 31;
    else 
        {printError("Line: %d. This register %s is invalid.\n", lineNum, regName);
        regNum = -1;}


    if (regNum != -1)
        printInt(regNum, 5);


}


/* Print value in `intInString` as pseudo-binary (made up of character
 * '0's and '1's). Only works for non-negative integers.
 *      @param intInString   string containing integer, e.g., "23"
 *      @param length  length of binary code needed, in bits
 *      @param lineNum line number (for error messages)
 *      @pre           integer can be represented in `length` number of bits
 *      @pre           integer >= 0
 *   (You can decide whether or not to require that integer be non-negative.)
 */
void printIntInString(char * intInString, int numBits, int lineNum)
{
    char * endPtr;

    /* Convert string to decimal (base 10) value. */
    int decimal = (int) strtol(intInString, &endPtr, 10);

    /* If the string contained a valid int, print it;
     * otherwise print an error message.
     */
    if ( *intInString != '\0' && *endPtr == '\0' )
    {
        /* entire string was valid */
        printInt(decimal, numBits);
    }
    else
    {
        printError("Line %d: trying to print %s as an int (%s).\n",
                lineNum, intInString, "not a valid integer");
    }
}


/* Print address to jump to.
 * This function calls findLabel to get the address associated
 * with the target label in the label table, calculates the portion of
 * the address to store in the instruction, and then prints that value
 * with the appropriate number of bits.
 *
 *      @param targetLabel   label being branched to
 *      @param table         label table
 *      @param lineNum       line number (for error messages)
 */
void printJumpTarget(char * targetLabel, LabelTableArrayList * table,
                     int lineNum)
{
    
    int address = findLabelAddr(table, targetLabel);
    address = address/4; //shift it down by 2 or divide by 4 to account for int size

    printDebug("\n jump address: %d. on line %d.\n", address, lineNum);
    printInt(address, 26);

}

/* Print branch offset to branch to the target label.
 *      @param targetLabel   label being branched to
 *      @param table         label table
 *      @param PC            Program Counter (could use lineNum instead)
 *      @param lineNum       line number (for error messages)
 */
void printBranchOffset(char * targetLabel, LabelTableArrayList * table,
                       int PC, int lineNum)
{

    int address = findLabelAddr(table, targetLabel);
    address = (address-PC)/4;

    printDebug("\n branch address: %d. PC: %d. on line %d.\n", address, PC, lineNum);

    printInt(address, 16);

}
