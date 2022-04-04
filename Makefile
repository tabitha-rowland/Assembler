# A simple makefile

GCC=gcc -Wall -Wextra -Wpedantic -Wformat -Wshadow -Wredundant-decls \
    -Wstrict-prototypes
# Can also use -Wtraditional or -Wmissing-prototypes

#  Switch to alternative versions of the all target as you're ready for them.
all:	assembler
# all:	testLabelTable assembler
# all:	testLabelTable testGetNTokens testPass1 testPrintAsBinary assembler

testLabelTable: assembler.h \
    	process_arguments.h \
	LabelTableArrayList.c \
    	process_arguments.c \
	printDebug.c \
	printError.c \
	same.c \
    	testLabelTable.c
	$(GCC) -g process_arguments.c same.c \
		LabelTableArrayList.c printDebug.c printError.c \
	    	testLabelTable.c -o testLabelTable

testGetNTokens: 	assembler.h \
    	process_arguments.h \
	getToken.c \
	getNTokens.c \
	printDebug.c \
	printError.c \
	same.c \
    	testGetNTokens.c
	$(GCC) -g testGetNTokens.c getNTokens.c getToken.c \
	    printDebug.c printError.c same.c -o testGetNTokens

testPass1: 	assembler.h \
    	process_arguments.h \
    	LabelTableArrayList.c \
    	process_arguments.c \
	getToken.c \
	getNTokens.c \
	pass1.c \
	printDebug.c \
	printError.c \
	same.c \
	testPass1.c
	$(GCC) -g LabelTableArrayList.c process_arguments.c \
	    getNTokens.c getToken.c pass1.c \
	    printDebug.c printError.c same.c testPass1.c -o testPass1

assembler: 	assembler.h \
    	process_arguments.h \
    	LabelTableArrayList.c \
    	process_arguments.c \
	getInstName.c \
	getToken.c \
	getNTokens.c \
	pass1.c \
	pass2.c \
	printAsBinary.c \
	printDebug.c \
	printError.c \
	same.c \
	assembler.c
	$(GCC) -g LabelTableArrayList.c process_arguments.c \
	    getInstName.c getNTokens.c getToken.c pass1.c pass2.c \
	    printAsBinary.c printDebug.c printError.c \
	    same.c assembler.c -o assembler

testPrintAsBinary: 	assembler.h \
	printAsBinary.c \
	LabelTableArrayList.c \
	printDebug.c \
	printError.c \
	same.c \
	testPrintAsBinary.c
	$(GCC) -g LabelTableArrayList.c printDebug.c printError.c same.c \
	    printAsBinary.c testPrintAsBinary.c -o testPrintAsBinary

stripCR:	assembler.h \
    	process_arguments.h \
	printDebug.c \
	printError.c \
    	process_arguments.c \
	same.c \
    	stripCR.c
	$(GCC) -g printDebug.c printError.c process_arguments.c same.c \
	    stripCR.c -o stripCR

assembler.h: LabelTableArrayList.h getToken.h \
	printFuncs.h process_arguments.h same.h
	touch assembler.h

clean: 
	rm -rf testLabelTable assembler testGetNTokens testPass1 \
	    testPrintAsBinary stripCR
