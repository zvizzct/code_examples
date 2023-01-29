#include <stdio.h>
#include <stdlib.h>
#include "src/utilsFiles.h"
#include "src/directives.h"

int main(int argc, char **argv)
{
    // Variables
    FILE *file;
    char *fileName, *outFileName;
    char *flag1 = NULL, *flag2 = NULL , *flag3 = NULL;
    char *fileContent, *preprocesedContent;
    int fd;

    // Get file name from command line argument
    fileName = argv[1];

    // Get flag from command line argument
    if (argc == 3) flag1 = argv[2];
    if (argc == 4) flag1 = argv[2], flag2 = argv[3];
    if (argc == 5) flag1 = argv[2], flag2 = argv[3], flag3 = argv[4];

    // Open file
    file = openFile(fileName);

    // Check if file was successfully opened
    if (file == NULL)
    {
        return 1;
    }

    // Read file
    fileContent = readFile(file);

    if (flag1 == NULL || (strcmp(flag1, "-c") == 0 && flag2 == NULL && flag3 == NULL))
    {
        // Remove comments
        preprocesedContent = removeComments(fileContent);
    }
    else if (strcmp(flag1, "-d") == 0 && flag2 == NULL && flag3 == NULL)
    {
        // Remove directives
        preprocesedContent = directivesInclude(fileContent);
        preprocesedContent = directivesDefine(preprocesedContent);
        preprocesedContent = directivesIfdef(preprocesedContent);
    }
    else if (strcmp(flag1, "-all") == 0 || (strcmp(flag1, "-c") == 0 && strcmp(flag2, "-d") == 0)
            ||  (strcmp(flag1, "-d") == 0 && strcmp(flag2, "-c") == 0) || strcmp(flag2, "-all") == 0 || strcmp(flag3, "-all") == 0)
    {
        // Remove comments and directives
        preprocesedContent = directivesInclude(fileContent);
        preprocesedContent = directivesDefine(preprocesedContent);
        preprocesedContent = directivesIfdef(preprocesedContent);
        preprocesedContent = removeComments(preprocesedContent);
    }
    else if (strcmp(flag1, "-help") == 0)
    {
        // Print help
    }
    else
    {
        printf("Invalid flag, please use -c, -d, -all or -help");
    }

    // write prepcocesed content to file
    outFileName = writeFile(fileName, preprocesedContent);
    printf("\n");
    printf("-------------------------------------------------------------\n");
    printf("-------- Preprocesed file saved in %s --------\n", outFileName);
    printf("-------------------------------------------------------------\n");

    // Free memory and close file
    free(fileContent);

    // Close file
    fclose(file);

    return 0;
}
