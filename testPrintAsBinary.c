#include "assembler.h"
int main()
{
    printf("About to partially test printInt:\n");
    printf("\t 5 = "); printInt(5, 3); printf(" (3 characters) \n");
    printf("\t 5 = "); printInt(5, 4); printf(" (4 characters) \n");

    printf("About to partially test printIntInString:\n");
    printf("\t 5 = "); printIntInString("5", 3, 12); printf(" (3 characters) \n");
    printf("\t 5 = "); printIntInString("5", 4, 12); printf(" (4 characters) \n");

    printf("About to test invalid int sent to printIntInString:\n");
    printf("\t q = "); printIntInString("q", 4, 12); printf(" (4 characters) \n");

    printf("About to partially test printReg:\n");
    printf("\t $zero = "); printReg("$zero", 12); printf("\n");
    printf("\t $t0 = "); printReg("$t0", 12); printf("\n");
    printf("\t $ra = "); printReg("$ra", 12); printf("\n");

    printf("About to test invalid register sent to printReg:\n");
    printf("\t $rq = "); printReg("$rq", 12); printf("\n");
}
