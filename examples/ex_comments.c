/*
 * Compilers
 * Practice 1: c pre-processor
 * Example file containing only comments
 */

int main(int argc, char **argv)
{
    // blaaaablaa
    // blaaaba
    // blaaaba
    int i;

    ofile = stdout; // default is stdout
    ofile = fopen(PRINTDESTFILE, "w");
    if (ofile == NULL)
        WARNING(0, (ofile, "Problem creating %s", PRINTDESTFILE));
    /* blablaaaaaa
    blabaaa
    baaaaa */
    errfile = stdout; // default is stdout
    errfile = fopen(PRINTERRORFILE, "w");
    if (errfile != NULL)
        WARNING(0, (ofile, "Problem creating %s", PRINTERRORFILE));

    // Prints arguments
    fprintf(ofile, "Arguments:\n");
    for (i = 0; i < argc; i++)
    {
        fprintf(ofile, "%i: %s\n", i, argv[i]);
        /* blaaaaaaaa
        blaaaaaaaaabla
        blaaa
        baa
        blaa */
        fclose(ofile);
        fclose(errfile);

        return 0;
    }
}