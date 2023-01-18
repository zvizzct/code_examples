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

    replaceString(fileContent, "#include", "hi");
    
    // Write
    if(writeFile(fileName, fileContent) != 0) {
        return 1;
    }
    free(fileContent);
    fclose(file);     

    return 0;
}


/*
updated:

#include <stdio.h> 
#include <stdlib.h> // 
int main(int argc, char**argv) {
    // Variables
    FILE *fptr; 
    char *file, c;
    int fd;

    file = argv[1];

    // Check if file is provided
    if(file==NULL){
        printf("No file provided, usage: ./preprocesor filename.c");
        return 0;
    }
    // Open file
    fptr = fopen( file, "r");

    // Check if file is opened
    if(fptr == NULL)                 
        printf("Problem opening %s", file);
    
    // Read file
    c = fgetc(fptr); 
    while (c != EOF) 
    { 
        
        printf ("%c", c); 
        c = fgetc(fptr); 
    } 
  
    fclose(fptr);     
    

 
    return 0;
}
*/