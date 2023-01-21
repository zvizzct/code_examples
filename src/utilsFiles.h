
#include <stdio.h>
#include <stdlib.h> //

/*
The function takes in a char* which represents the name of the file to be opened. If the provided file name
is NULL, the function will print a message and return NULL. If the file could not be opened, the function will
print a message and return NULL. If the file is successfully opened, the function will return a pointer to the
opened file.
*/
/**
 * @brief Open a file with a provided name
 *
 * @param fileName The name of the file to open
 * @return FILE* Pointer to the opened file, or NULL if the file does not exist or no file name was provided
 */
FILE *openFile(char *fileName)
{
    if (fileName == NULL)
    {
        printf("No file provided, usage: ./preprocesor filename.c");
        return NULL;
    }
    FILE *fptr = fopen(fileName, "r");

    if (fptr == NULL)
    {
        printf("File does not exist %s", fileName);
        return NULL;
    }
    return fptr;
}

/*
The function takes in a FILE* which represents the file to be read. If the provided file is
NULL, the function will print a message and return NULL. The function uses fseek, ftell
and rewind to get the size of the file, then it uses malloc to allocate memory to store
the file content. The function reads the file using fread and adds a null character at the
end of the content. It returns the content of the file as a string.
 */

/**
 * @brief Read the content of a file and return it as a string
 *
 * @param file The file to read
 * @return char* The content of the file as a string, or NULL if no file was provided
 */
char *readFile(FILE *file)
{
    if (file == NULL)
    {
        printf("No file provided, usage: ./preprocesor filename.c");
        return NULL;
    }
    // Get the file size
    fseek(file, 0, SEEK_END);
    long fileSize = ftell(file);
    rewind(file);

    // Allocate memory to store the file contents
    char *fileContent = (char *)malloc((fileSize + 1) * sizeof(char));

    // Read the file into memory
    fread(fileContent, sizeof(char), fileSize, file);
    fileContent[fileSize] = '\0';
    return fileContent;
}

/*
The function takes in a char* which represents the name of the file. It checks if the provided
file name is NULL. It then uses strrchr to search for the last occurrence of '/' or '' in the
file name, if either are found it returns a pointer to the character after the last occurrence,
otherwise it returns the original file name.
*/
/**
 * @brief  Extract the base name of a file from a provided file name
 *
 * @param fileName The name of the file
 * @return char* The base name of the file, or the original file name if no '/' or '' is present
 */
char *baseName(const char *fileName)
{
    char *base = NULL;

    if (fileName != NULL)
    {
        base = strrchr(fileName, '/');
        if (base == NULL)
        {
            base = strrchr(fileName, '\\');
        }
    }

    if (base == NULL)
    {
        return (char *)fileName;
    }
    else
    {
        return base + 1;
    }
}

/*
 The function takes in a char* which represents the original file name. It uses malloc to
 allocate memory to store the new file name. It uses strrchr to find the last occurrence
 of '.' in the file name, and it checks if it's a ".c" or ".h" extension. If the extension is ".c"
 or ".h" it creates a new file name by copying the original file name up to the '.',
 appending "-pre" and then the extension. If it doesn't find the extension or it's not .c or
 .h it will return the original file name. It returns the new file name.
 */
/**
 * @brief Generate a new file name by appending "-pre" to the original file name before its extension
 *
 * @param fileName  fileName The original file name
 * @return char*  The new file name
 */
char *getNewFileName(const char *fileName)
{
    char *newFileName = malloc(sizeof(char) * 256);
    char *dot = strrchr(fileName, '.');
    if (dot && (!strcmp(dot, ".c") || !strcmp(dot, ".h")))
    {
        strncpy(newFileName, fileName, dot - fileName);
        newFileName[dot - fileName] = 0;
        strcat(newFileName, "-pre");
        strcat(newFileName, dot);
    }
    else
    {
        strcpy(newFileName, fileName);
    }
    return newFileName;
}

/*
The function takes in two char* which represents the name of the file to create/write
to and the content to write to the file. It checks if the provided file name or content is
NULL, if it is the function will print an error message and return 1. The function creates
a new file name by appending "-pre.c" or "-pre-h" to the original file name if the original
file name is a .c or .h file, otherwise the function will use the original file name.
The function uses fopen to create the file with "w" mode. It uses fwrite to write the
content to the file. If fwrite returns a negative value, the function will print an error
message, close the file, and return the filename with the "-pre" prefix.
*/

/**
 * @brief Write a string to a file with a provided name
 *
 * @param fileName The name of the file to create/write to
 * @param fileContent The content to write to the file
 * @return  char * The new file name
 */
char *writeFile(char *fileName, char *fileContent)
{
    if (fileName == NULL || fileContent == NULL)
    {
        printf("No file name or content provided, usage: ./preprocesor filename.c");
        return 1;
    }
    char *base = baseName(fileName);
    char *newFileName = getNewFileName(base);

    char *outputFolder = "output/";
    char *newFileNameWithFolder = malloc(sizeof(char) * (strlen(outputFolder) + strlen(newFileName) + 1));

    strcpy(newFileNameWithFolder, outputFolder);
    strcat(newFileNameWithFolder, newFileName);

    FILE *fptr = fopen(newFileNameWithFolder, "w");
    if (fwrite(fileContent, sizeof(char), strlen(fileContent), fptr) < 0)
    {
        printf("Error writing to file %s", newFileNameWithFolder);
    }
    fclose(fptr);
    return newFileNameWithFolder;
}
