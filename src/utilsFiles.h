
#include <stdio.h> 
#include <stdlib.h> // 


/**
 * @brief Open a file with a provided name
 * 
 * @param fileName The name of the file to open
 * @return FILE* Pointer to the opened file, or NULL if the file does not exist or no file name was provided
 *
 * The function takes in a char* which represents the name of the file to be opened. If the provided file name
 * is NULL, the function will print a message and return NULL. If the file could not be opened, the function will
 * print a message and return NULL. If the file is successfully opened, the function will return a pointer to the 
 * opened file.
 */
FILE *openFile(char *fileName){
    if(fileName==NULL){
        printf("No file provided, usage: ./preprocesor filename.c");
        return NULL;
    }
    FILE *fptr =  fopen( fileName, "r");
    
    if(fptr == NULL) {                
        printf("File does not exist %s", fileName);
        return NULL;
    }
    return fptr;
}

/**
 * @brief Read the content of a file and return it as a string
 * 
 * @param file The file to read
 * @return char* The content of the file as a string, or NULL if no file was provided
 *
 * The function takes in a FILE* which represents the file to be read. If the provided file is 
 * NULL, the function will print a message and return NULL. The function uses fseek, ftell 
 * and rewind to get the size of the file, then it uses malloc to allocate memory to store 
 * the file content. The function reads the file using fread and adds a null character at the 
 * end of the content. It returns the content of the file as a string.
 
 */
char* readFile(FILE* file) {
    if(file == NULL){
        printf("No file provided, usage: ./preprocesor filename.c");
        return NULL;
    }
    // Get the file size
    fseek(file, 0, SEEK_END);
    long fileSize = ftell(file);
    rewind(file);

    // Allocate memory to store the file contents
    char* fileContent = (char*)malloc((fileSize + 1) * sizeof(char));

    // Read the file into memory
    fread(fileContent, sizeof(char), fileSize, file);
    fileContent[fileSize] = '\0';
    return fileContent;
}


/**
 * @brief Write a string to a file with a provided name
 * 
 * @param fileName The name of the file to create/write to
 * @param fileContent The content to write to the file
 * @return  int 0 on success, 1 on failure
 *
 * The function takes in two char* which represents the name of the file to create/write 
 * to and the content to write to the file. It checks if the provided file name or content is 
 * NULL, if it is the function will print an error message and return 1. The function creates 
 * a new file name by appending "-pre.c" or "-pre-h" to the original file name if the original
 * file name is a .c or .h file, otherwise the function will use the original file name. 
 * The function uses fopen to create/open the file with "w" mode. It uses fwrite to write the 
 * content to the file. If fwrite returns a negative value, the function will print an error 
 * message, close the file, and return 1. If fwrite is successful, the function will close the 
 * file and return 0.

 */

 //change the writefile function to output the file on the directory "output"
 
int writeFile(const char* fileName, const char* fileContent) {
    if(fileName == NULL || fileContent == NULL) {
        printf("Error: Invalid parameter, file name or content is NULL");
        return 1;
    }
    char newFileName[256];
    char outputNewFileName[256];
    char *dot = strrchr(fileName,'.');
    if (dot && !strcmp(dot, ".c")) {
        strncpy(newFileName, fileName, dot-fileName);
        newFileName[dot-fileName] = 0;
        strcat(newFileName, "-pre.c");
    }
    else if (dot && !strcmp(dot, ".h")) {
        strncpy(newFileName, fileName, dot-fileName);
        newFileName[dot-fileName] = 0;
        strcat(newFileName, "-pre.h");
    }
    else {
        strcpy(newFileName, fileName);
    }
    //TODO: change the output file name to "output/"
    strcpy(outputNewFileName, "outputs/");
    strcat(outputNewFileName, newFileName);
    FILE* newFile = fopen(outputNewFileName, "w");

    size_t result = fwrite(fileContent, 1, strlen(fileContent), newFile);
    if(result < 0) {
        printf("Error: Unable to write to file %s", outputNewFileName);
        fclose(newFile);
        return 1;
    }

    fclose(newFile);
    return 0;
}


//This is a test function to change the content of a file
void replaceString(char* fileContent, const char* searchString, const char* newString) {
    char* match = fileContent;
    int searchStringLen = strlen(searchString);

    while ((match = strstr(match, searchString)) != NULL) {
        int newStringLen = strlen(newString);
        int matchStringLen = strlen(match);
        int tailStringLen = strlen(match + searchStringLen);
        memmove(match + newStringLen, match + searchStringLen, tailStringLen + 1);
        memcpy(match, newString, newStringLen);
        match += newStringLen;
    }
}