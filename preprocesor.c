#include <stdio.h>
#include <stdlib.h>
#include "src/utilsFiles.h"
#include "src/directives.h"

int main(int argc, char **argv)
{
    // Variables
    FILE *file;
    char *fileName, *outFileName;
    char *flag;
    char *fileContent, *preprocesedInclude, *preprocesedDefines, *preprocesedIfdef, *preprocesedComments;
    int fd;

    // Get file name from command line argument
    fileName = argv[1];

    // Get flag from command line argument
    flag = argv[2];

    // Open file
    file = openFile(fileName);

    // Check if file was successfully opened
    if (file == NULL)
    {
        return 1;
    }

    // Read file
    fileContent = readFile(file);

    if (strcmp(flag, "-c") == 0)
    {
        // Remove comments
    }
    else if (strcmp(flag, "-d") == 0)
    {
        // Remove directives
    }
    else if (strcmp(flag, "-all") == 0)
    {
        // Remove comments and directives
    }
    else if (strcmp(flag, "-help") == 0)
    {
        // Print help
    }
    else
    {
        printf("Invalid flag, please use -c, -d, -all or -help");
    }

    preprocesedInclude = directivesInclude(fileContent);
    preprocesedDefines = directivesDefine(preprocesedInclude);
    preprocesedIfdef = directivesIfdef(preprocesedDefines);
    preprocesedComments = removeComments(preprocesedIfdef);

    // write prepcocesed content to file
    outFileName = writeFile(fileName, preprocesedComments);
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
