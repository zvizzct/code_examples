#include <stdio.h>
#include <stdlib.h>
#include "src/utilsFiles.h"
#include "src/directives.h"

FILE *file;
char *fileContent;

/**
 * @brief Set the Upfile Content object
 *
 * @param fileName The name of the file to open
 * @return char* The content of the file as a string, or NULL if no file was provided
 */
char *setUpfileContent(char *fileName)
{

    // Open file
    file = openFile(fileName);

    // Check if file was successfully opened
    if (file == NULL)
    {
        return "error";
    }

    // Read file
    fileContent = readFile(file);

    return fileContent;
}

/**
 * @brief Prints a message with the name of the output file
 *
 * @param outFileName The name of the output file
 */
void outputMessage(char *outFileName)
{

    printf("\n");
    printf("-------------------------------------------------------------\n");
    printf("-------- Preprocesed file saved in %s --------\n", outFileName);
    printf("-------------------------------------------------------------\n");
}

/**
 * @brief Prints the help message for the preprocessor app
 *
 */
void flagHelp()
{
    printf("\nPreprocessor app usage:\n");
    printf("\t./preprocessor [flags] [filename]\n");
    printf("Available flags:\n");
    printf("\t-c : Eliminates comments (default)\n");
    printf("\t-d : Replaces all directives starting with #\n");
    printf("\t-all : Does all processing implemented\n");
    printf("\t-help : Prints this help message\n");
}

int main(int argc, char **argv)
{
    // Variables
    char *fileName, *outFileName;
    char *flag1 = NULL, *flag2 = NULL, *flag3 = NULL;
    char *preprocesedContent;
    int fd;

    // Get file name from command line argument
    fileName = argv[1];
    // if (argc == 1)
    //     fileName = argv[1];
    // if (argc == 2)
    //     flag1 = argv[1], fileName = argv[2];
    // if (argc == 3)
    //     flag1 = argv[1], flag2 = argv[2], fileName = argv[3];
    // if (argc == 4)
    //     flag1 = argv[1], flag2 = argv[2], flag3 = argv[3], fileName = argv[4];
    // if (argc == 5)
    //     flag1 = argv[1], flag2 = argv[2], flag3 = argv[3], fileName = argv[4];

    if (strcmp(setUpfileContent(fileName), "error") == 0)
    {
        flagHelp();
        return 1;
    }
    fileContent = setUpfileContent(fileName);

    // Remove comments

    preprocesedContent = operatorBackslash(fileContent);
    // printf("%s", preprocesedContent);

    // write prepcocesed content to file
    outFileName = writeFile(fileName, preprocesedContent);

    // Print output message
    outputMessage(outFileName);

    // Free memory and close file
    free(fileContent);

    // Close file
    fclose(file);

    // if (flag1 == NULL || (strcmp(flag1, "-c") == 0 && flag2 == NULL && flag3 == NULL))
    // {
    //     // set up fileContent
    //     if (strcmp(setUpfileContent(fileName), "error") == 0)
    //     {
    //         flagHelp();
    //         return 1;
    //     }
    //     fileContent = setUpfileContent(fileName);

    //     // Remove comments
    //     preprocesedContent = removeComments(fileContent);

    //     // write prepcocesed content to file
    //     outFileName = writeFile(fileName, preprocesedContent);

    //     // Print output message
    //     outputMessage(outFileName);

    //     // Free memory and close file
    //     free(fileContent);

    //     // Close file
    //     fclose(file);
    // }
    // else if (strcmp(flag1, "-d") == 0 && flag2 == NULL && flag3 == NULL)
    // {

    //     // set up fileContent
    //     fileContent = setUpfileContent(fileName);

    //     // Remove directives
    //     preprocesedContent = directivesInclude(fileContent);
    //     preprocesedContent = directivesDefine(preprocesedContent);
    //     preprocesedContent = directivesIfdef(preprocesedContent);

    //     // write prepcocesed content to file
    //     outFileName = writeFile(fileName, preprocesedContent);

    //     // Print output message
    //     outputMessage(outFileName);

    //     // Free memory and close file
    //     free(fileContent);

    //     // Close file
    //     fclose(file);
    // }
    // else if (strcmp(flag1, "-all") == 0 || (strcmp(flag1, "-c") == 0 && strcmp(flag2, "-d") == 0) || (strcmp(flag1, "-d") == 0 && strcmp(flag2, "-c") == 0) || strcmp(flag2, "-all") == 0 || strcmp(flag3, "-all") == 0)
    // {

    //     // set up fileContent
    //     fileContent = setUpfileContent(fileName);

    //     // Remove all directives
    //     preprocesedContent = directivesInclude(fileContent);
    //     preprocesedContent = directivesDefine(preprocesedContent);
    //     preprocesedContent = directivesIfdef(preprocesedContent);
    //     preprocesedContent = removeComments(preprocesedContent);

    //     // write prepcocesed content to file
    //     outFileName = writeFile(fileName, preprocesedContent);

    //     // Print output message
    //     outputMessage(outFileName);

    //     // Free memory and close file
    //     free(fileContent);

    //     // Close file
    //     fclose(file);
    // }
    // else if (strcmp(flag1, "-help") == 0)
    // {
    //     flagHelp();
    // }
    // else
    // {
    //     printf("Invalid flag\n\n");
    //     flagHelp();
    // }

    return 0;
}
