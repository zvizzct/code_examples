/*
 * Compilers
 * Practice 1: c pre-processor
 * Example files: comp-p1.h, comp-p1.c
 */
#include "./comp-p1.h"

int main(int argc, char **argv)
{

    int i;

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