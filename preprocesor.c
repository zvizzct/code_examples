#include <stdio.h>
#include <stdlib.h>
#include "src/utilsFiles.h"
#include "src/directives.h"

int main(int argc, char **argv)
{
    // Variables
    FILE *file;
    char *fileName, *outFileName;
    char *fileContent, *preprocesedInclude, *preprocesedDefines, *preprocesedIfdef, *preprocesedComments;
    int fd;

    // Get file name from command line argument
    fileName = argv[1];

    // Open file
    file = openFile(fileName);

    // Check if file was successfully opened
    if (file == NULL)
    {
        return 1;
    }

    // Read file
    fileContent = readFile(file);

    // preproces defines
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
