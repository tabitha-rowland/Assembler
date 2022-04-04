/*
 * Test Driver to test the functions to access and manipulate a label table.
 * It includes the following tests:
 *
 * For the static table, first it looks for Label1 in a table that is empty. 
 * Then, it adds 3 labels and prints them, then looks for 1 & 3 (the extremes).
 * It also searches for Label99 which doesn't exist. 
 * For the dynamic table, it begins with an empty table and prints it out. Then
 * it adds 4 labels and prints it out. It searches for 1,4, and 5 which does not exist.
 * It then adds label5 to the table and searches for 5 again, and for 99.
 *
 * Author:  Tabitha Rowland
 *        with assistance from:
 *
 * Creation Date:  2/22/2022
 *        modified: 2/22/2022        complete tests for static and dynamic tables
 *        
 * 
 */

#include "assembler.h"

static void testSearch(LabelTableArrayList * table, char * searchLabel);

int main(int argc, char * argv[])
{
    /* Process command-line argument (if provided) for
     *    debugging indicator (1 = on; 0 = off).
     */
    (void) process_arguments(argc, argv);

    /* Create 2 tables, one static and one dynamic, for testing purposes */
    printf("===== Testing with static table =====\n");

    /* Create a static array of label entries for initial testing. */
    LabelEntry staticEntries[5];
    staticEntries[0].label = "Label1";
    staticEntries[0].address = 1000;
    staticEntries[1].label = "Label2";
    staticEntries[1].address = 2000;
    staticEntries[2].label = "Label3";
    staticEntries[2].address = 3000;
    /* Initialize testTable1 to use the static array above. */
    LabelTableArrayList testTable1;      /* table with static entries */
    testTable1.capacity = 5;
    testTable1.nbrLabels = 2;
    testTable1.entries = staticEntries;

    /* Test printLabels and findLabelAddr with static testTable1.
     *  =>  DO NOT TEST tableInit, addLabel, or tableResize WITH STATIC TABLE!
     * Use testSearch to test findLabelAddr, for example:
     *      testSearch(&testTable1, "Label1");
     * Examples of basic boundary testing:
     *     Set nbrLabels to 0 and test on empty table.
     *     Put four more entries in staticEntries, set nbrLabels to 5,
     *     and test.  (Don't go beyond the max unless you want to crash the
     *     program. You can do that test with the dynamic table, not with
     *     this one.)
     */
    testTable1.nbrLabels=0;
    printLabels(&testTable1);
    testSearch(&testTable1, "Label1");
    
    testTable1.nbrLabels=3;
    printLabels(&testTable1);
    testSearch(&testTable1,"Label1");
    testSearch(&testTable1,"Label3");
    testSearch(&testTable1,"Label99");





    printf("===== Testing with dynamic table =====\n");

    /* Initialize testTable2 as a dynamic (changeable size) table. */
    LabelTableArrayList testTable2;      /* table with dynamic entries */
    tableInit(&testTable2);
    printLabels(&testTable2);


    /* Test printLabels, findLabelAddr, and addLabel with dynamic testTable2.
     * Include appropriate boundary testing.
     */
    addLabel(&testTable2, "Label1", 1000);
    addLabel(&testTable2, "Label2", 2000);
    addLabel(&testTable2, "Label3", 3000);
    addLabel(&testTable2, "Label4", 4000);
    printLabels(&testTable2);

    testSearch(&testTable2,"Label1");
    testSearch(&testTable2,"Label4");
    testSearch(&testTable2,"Label5");
    addLabel(&testTable2, "Label5", 5000);
    printLabels(&testTable2);
    testSearch(&testTable2,"Label5");
    testSearch(&testTable2,"Label99");


}


/*
 * testSearch tests the findLabelAddr function, printing out the label being
 * searched for and either the address where it was found or, if it was
 * not found, an address of -1 and a message that the label was not in
 * the table.  
 *  @param  tablePtr     a pointer to the table through which to search
 *  @param  searchLabel  the label to search for
 */
static void testSearch(LabelTableArrayList * tablePtr, char * searchLabel)
{
    int address;

    printf("Looking for %s...\n", searchLabel);

    address = findLabelAddr(tablePtr, searchLabel);         /* prints what its searching for, address it found or not */

    printf("\tthe address is %d.\n", address);
    if ( address == -1 )
        printf("\tThe label you're looking for does not exist.\n");
}
