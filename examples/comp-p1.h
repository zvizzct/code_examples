/*
 * Compilers
 * Practice 1: c pre-processor
 * Example files: comp-p1.h, comp-p1.c
 */

#include <stdio.h>

#define ON 1
#define OFF 0

#define PRINTDESTFILE "out.txt"     // file destination of normal program print: stdout/out.txt
#define PRINTERRORFILE "errmsg.txt" // file destination of normal program print: errmsg.txt
#define ERRORMSG "This is a large long message as example"

#define N 2
#define PRINTWARNING ON // ON = Yes OFF / NO
#define PRINTERROR ON   // ON = Yes OFF / NO

// MACROS used for the printouts instead of using f/printfs so that all prints
// in the program are treated the same way.
// Use ERROR when the print out informs of a ERROR/problem in the program and it must finish the program
// Use WARNING when the print out informs of a ERROR/problem in the program but the preprocessor can continue
// You have to define the format of your errors, this is just an example to test,
// but your code can do a different version of this to treat errors
/* usage: ERROR(("Warning: Note the two brackets\n")) */
FILE *errfile; // File where to write error messages
FILE *ofile;   // File where to write program information