#include <stdio.h> 
#include <stdlib.h> 
#include "src/utilsFiles.h"
#include "src/directives.h"

int main(int argc, char**argv) {
    // Variables
    FILE *file; 
    char *fileName, *fileContent, c;
    int fd;

    // Get file name from command line argument
    fileName = argv[1];

    // Open file
    file = openFile(fileName);

    // Check if file was successfully opened
    if(file == NULL) {
        return 1;
    }

    // Read file
    fileContent = readFile(file);

    // Replace "#include" with "CHANGED"
    // replaceString(fileContent, "#include", "CHANGED");
    
    // // Write changes to file
    // if(writeFile(fileName, fileContent) != 0) {
    //     return 1;
    // }

    //test
    directivesDefine(fileContent);

    // Free memory and close file
    free(fileContent);
    fclose(file);     

    return 0;
}