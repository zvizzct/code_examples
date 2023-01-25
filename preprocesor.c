#include <stdio.h>
#include <stdlib.h>
#include "src/utilsFiles.h"
#include "src/directives.h"

int main(int argc, char **argv)
{
    // Variables
    FILE *file;
    char *fileName, *preprocesedFileContent, *fileContent, c, *outFileName;
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
    // preprocesedFileContent = directivesDefine(fileContent);
    preprocesedFileContent = directivesInclude(fileContent);

    // write prepcocesed content to file
    outFileName = writeFile(fileName, preprocesedFileContent);
    printf("Preprocesed file is in %s\n", outFileName);

    // Free memory and close file
    free(fileContent);

    // Close file
    fclose(file);

    return 0;
}
