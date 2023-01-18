/*
 * Compilers
 * Practice 1: c pre-processor
 * Example files: comp-p1.h, comp-p1.c
    */
#include <stdio.h> 
#include <stdlib.h> //
#include "src/utilsFiles.h"

int main(int argc, char**argv) {
    // Variables
    FILE *file; 
    char *fileName,*fileContent, c;
    int fd;

    fileName = argv[1];
    // Open file
    file = openFile(fileName);
    if(file == NULL) {
        return 1;
    }
    // Read file
    fileContent = readFile(file);

    // printf("%s", fileContent);

    replaceString(fileContent, "#include", "CHANGED");
    
    // Write
    if(writeFile(fileName, fileContent) != 0) {
        return 1;
    }
    free(fileContent);
    fclose(file);     

    return 0;
}

