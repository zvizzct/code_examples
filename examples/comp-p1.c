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
#define ERROR1(num, message) ({printf("\n%d ERROR \n", num);printf message; })
#define FERROR1(num, message) ({fprintf(errfile,"\n%d ERROOORRRRRRRRRR\n", num);fprintf message; })
#define ERROR(num, message) ({WARNING( num, message); exit(0); })
FILE *errfile; // File where to write error messages
FILE *ofile;   // File where to write program information

int main(int argc, char **argv)
{

    int i;
    // print the first argument
    printf("flag argument: %s\n", argv[1]);

    ofile = stdout; // default is stdout
    ofile = fopen(PRINTDESTFILE, "w");
    if (ofile == NULL)
        WARNING(0, (ofile, "Problem creating %s", PRINTDESTFILE));

    errfile = stdout; // default is stdout
    errfile = fopen(PRINTERRORFILE, "w");
    if (errfile != NULL)
        WARNING(0, (ofile, "Problem creating %s", PRINTERRORFILE));

    // Prints arguments
    fprintf(ofile, "Arguments:\n");
    for (i = 0; i < argc; i++)
    {
        fprintf(ofile, "%i: %s\n", i, argv[i]);
#if (PRINTWARNING == ON)
        WARNING(i, (errfile, "warning print example %s \n", argv[i]));
#endif
    }

#if (PRINTERROR == ON)
    ERROR(i, (errfile, "This is an error, and it stops"));
#endif

    fclose(ofile);
    fclose(errfile);

    return 0;
}
/*
#include file --> create function to open and close file
# define constant --> change all the constant to the value

*/