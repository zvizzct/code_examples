#define ERROR1(num, message) ({printf("\n%d ERROR \n", num);printf message; })
#define FERROR1(num, message) ({fprintf(errfile,"\n%d ERROOORRRRRRRRRR\n", num);fprintf message; })
#define WARNING(num, message) ({fprintf(errfile,"%d ERROR: ", num);\
            fprintf message;printf("ERROOORRRRRRRRRR see output file\n"); })
FILE *errfile; // File where to write error messages
FILE *ofile;   // File where to write program information#include <string.h>
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
