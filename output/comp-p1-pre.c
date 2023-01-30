/*
 * Compilers
 * Practice 1: c pre-processor
 * Example files: comp-p1.h, comp-p1.c
 */
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
/* usage: ERROR(("Warning: Note the two brackets n")) */

FILE *errfile; // File where to write error messages
FILE *ofile;   // File where to write program information

int main(int argc, char **argv)
{

    int i;

    ofile = stdout; // default is stdout
    ofile = fopen("out.txt", "w");
    if (ofile == NULL)
        WARNING(0, (ofile, "Problem creating %s", "out.txt"));

    errfile = stdout; // default is stdout
    errfile = fopen("errmsg.txt", "w");
    if (errfile != NULL)
        WARNING(0, (ofile, "Problem creating %s", "errmsg.txt"));

    // Prints arguments
    fprintf(ofile, "Arguments: n");
    for (i = 0; i < argc; i++)
    {
        fprintf(ofile, "%i: %s n", i, argv[i]);
#if (1 == 1)
        WARNING(i, (errfile, "warning print example %s  n", argv[i]));
#endif
    }

#if (1 == 1)
    ERROR(i, (errfile, "This is an error, and it stops"));
#endif

    fclose(ofile);
    fclose(errfile);

    return 0;
}