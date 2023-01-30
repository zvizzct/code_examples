                                                                                           

int main(int argc, char **argv)
{
                 
              
              
    int i;

    ofile = stdout;                     
    ofile = fopen(PRINTDESTFILE, "w");
    if (ofile == NULL)
        WARNING(0, (ofile, "Problem creating %s", PRINTDESTFILE));
                                            
    errfile = stdout;                     
    errfile = fopen(PRINTERRORFILE, "w");
    if (errfile != NULL)
        WARNING(0, (ofile, "Problem creating %s", PRINTERRORFILE));

                       
    fprintf(ofile, "Arguments:\n");
    for (i = 0; i < argc; i++)
    {
        fprintf(ofile, "%i: %s\n", i, argv[i]);
                                                                  
    fclose(ofile);
    fclose(errfile);

    return 0;
}
