/*
 * Compilers
 * Practice 1: c pre-processor
 * Example file containing only include directives
 * The first include with "" syntax will be replaced by the content
 * of the file comp-p1.h, the second will not be replaced with the <> syntax
 */
#include <string.h>

/*
 * Compilers
 * Practice 1: c pre-processor
 * Example files: comp-p1.h, comp-p1.c
 */

#include <stdio.h>




// MACROS used for the printouts instead of using f/printfs so that all prints
// in the program are treated the same way.
// Use ERROR when the print out informs of a ERROR/problem in the program and it must finish the program
// Use WARNING when the print out informs of a ERROR/problem in the program but the preprocessor can continue
// You have to define the format of your errors, this is just an example to test,
// but your code can do a different version of this to treat errors
/* usage: ERROR(("Warning: Note the two brackets\n")) */
FILE *errfile; // File where to write error messages
FILE *ofile;   // File where to write program information

int main(int argc, char **argv)
{
    return 0;
}