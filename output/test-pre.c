
                                                                                             

#include <stdio.h>




                                                                               
                                            
                                                                                                         
                                                                                                              
                                                                                  
                                                                    
                                                        
FILE *errfile;                                       
FILE *ofile;                                             
#include <string.h>
int main(int argc, char **argv)
{

    int i;
                               
    printf("flag argument: %s\n", argv[1]);

    ofile = stdout;                     
    ofile = fopen("out.txt", "w");
    if (ofile == NULL)
        WARNING(0, (ofile, "Problem creating %s", "out.txt"));

    errfile = stdout;                     
    errfile = fopen("errmsg.txt", "w");
    if (errfile != NULL)
        WARNING(0, (ofile, "Problem creating %s", "errmsg.txt"));

                       
    fprintf(ofile, "Arguments:\n");
    for (i = 0; i < argc; i++)
    {
        fprintf(ofile, "%i: %s\n", i, argv[i]);
        WARNING(i, (errfile, "warning print example %s \n", argv[i]));
    }

    ERROR(i, (errfile, "This is an error, and it stops"));

    fclose(ofile);
    fclose(errfile);

    return 0;
}
