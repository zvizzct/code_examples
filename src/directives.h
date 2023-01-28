#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <unistd.h>

// #include "utilsFiles.h"

#define MAX_DEFINES 100
#define MAX_NAME_LEN 100
/*
1. Directives
    a. #include
    b. #define
    c. #ifdef - #endif
2. Parametrized macros: A macro is like a function but at the preprocessing level. It is a substitution
function that has parameters to provide different situations or values to the substitutions.
3. Operator backslash “\”
4. Eliminate comments and replace each of them by a space (empty lines are not eliminated)
*/

struct DefineDirective
{
    char name[100];
    char value[100];
};

// ---------------------------------------------------------------------------------------
// START OF 1.A) #include
// ---------------------------------------------------------------------------------------

/**
 * @brief replaces the include directive with the content of the file
 *
 * @param fileContent  the content of the file
 * @param newFileContent the content of the file to include
 * @param fileName the name of the file to include
 * @return char*
 */
char *replaceInclude(char *fileContent, char *newFileContent, char *fileName)
{
    // Declare includeLine string
    char *includeLine = "#include";

    // Allocate memory for includeFile with quotes
    char *includeFile = malloc(strlen(fileName) + 3); // +3 for quotes and null char
    sprintf(includeFile, "\"%s\"", fileName);

    // Allocate memory for full include line
    char *include = malloc(strlen(includeLine) + strlen(includeFile) + 3); // +3 for whitespace and null char
    sprintf(include, "%s %s", includeLine, includeFile);

    // Declare pointers for start and end of include line in fileContent
    char *start, *end;
    start = strstr(fileContent, include);
    end = start + strlen(include);

    // Allocate memory for final result
    char *result = malloc(strlen(fileContent) + strlen(newFileContent) + 1);

    if (start != NULL)
    {
        // Copy fileContent up to the match
        strncpy(result, fileContent, start - fileContent);

        // Copy newFileContent into result
        strcpy(result + (start - fileContent), newFileContent);

        // Copy remaining content of fileContent after the match
        strcpy(result + (start - fileContent) + strlen(newFileContent), end);
    }
    else
    {
        // If no match, copy fileContent into result
        strcpy(result, fileContent);
    }

    // Free allocated memory
    free(include);
    free(includeFile);
    return result;
}

/**
 * @brief Processes the file name to include by adding the "examples" prefix
 *
 * @param fileName the name of the file to include
 * @return char* the processed file name
 */
char *processFileNameInclude(char *fileName)
{
    // Get length of fileName
    int len = strlen(fileName);

    // Allocate memory for newFileName with "examples" prefix
    char *newFileName = malloc(len + 9);
    strcpy(newFileName, "examples");

    if (fileName[0] == '.')
    {
        // If fileName starts with ".", remove it and concatenate with "examples"
        strcat(newFileName, fileName + 1);
    }
    else
    {
        // Concatenate fileName to "examples"
        strcat(newFileName, fileName);
    }
    return newFileName;
}

/**
 * @brief Processes the file content by replacing all include directives with the content of the included file
 *
 * @param fileContent the content of the file
 * @return char* the updated file content
 */
char *directivesInclude(char *fileContent)
{
    // Initialize updatedFileContent with fileContent
    char *updatedFileContent = fileContent;

    // Find the first occurrence of "#include" in fileContent
    char *includeStart = strstr(fileContent, "#include");

    while (includeStart != NULL)
    {
        // Initialize newFileContent
        char *newFileContent;

        // Find the first occurrence of '"' after includeStart
        char *fileStart = strchr(includeStart, '"');
        if (fileStart == NULL)
        {
            break;
        }
        // Find the second occurrence of '"' after fileStart
        char *fileEnd = strchr(fileStart + 1, '"');
        if (fileEnd == NULL)
        {
            break;
        }
        // Calculate the length of fileName
        int len = fileEnd - fileStart - 1;

        // Allocate memory for fileName and copy the contents
        char *fileName = (char *)malloc(sizeof(char) * (len + 1));
        memcpy(fileName, fileStart + 1, len);
        fileName[len] = '\0';

        // Get the full name of the file
        char *fullName = processFileNameInclude(fileName);

        // Open the file
        FILE *fp = fopen(fullName, "r");
        if (fp != NULL)
        {
            // Read the contents of the file
            newFileContent = readFile(fp);
            // Replace the include statement with the contents of the included file
            updatedFileContent = replaceInclude(updatedFileContent, newFileContent, fileName);
            fclose(fp);
        }

        // Free the memory allocated for fileName
        free(fileName);

        // Find the next occurrence of "#include"
        includeStart = strstr(fileEnd, "#include");
    }
    return updatedFileContent;
}

// ---------------------------------------------------------------------------------------
// START OF 1.B) #define
// ---------------------------------------------------------------------------------------

/**
 * @brief Replaces all occurences of a defined directive in a string with its corresponding value.
 *
 * @param fileContent The string to be modified
 * @param defines An array of DefineDirective structs
 * @param defineCount Number of DefineDirective structs in the array
 * @return char* The modified string
 */
char *replaceDefine(char *fileContent, struct DefineDirective defines[], int defineCount)
{
    // Iterate over the defined defines
    for (int i = 0; i < defineCount; i++)
    {
        // Get the current define's name and value
        char *defineName = defines[i].name;
        char *defineValue = defines[i].value;

        // Find the first occurrence of the define name in the file content
        char *occurrence = strstr(fileContent, defineName);

        // Iterate over all occurrences of the define name in the file content
        while (occurrence != NULL)
        {
            // Check if the occurrence is not part of another word
            if (isalnum(*(occurrence - 1)) || isalnum(*(occurrence + strlen(defineName))))
            {
                // Move to the next occurrence if it is part of another word
                occurrence = strstr(occurrence + strlen(defineName), defineName);
                continue;
            }

            // Create new string with the replacement value
            int remainingLen = strlen(occurrence) - strlen(defineName);
            char *newString = malloc(strlen(fileContent) - strlen(defineName) + strlen(defineValue) + 1);
            memcpy(newString, fileContent, occurrence - fileContent);
            strcat(newString, defineValue);
            strcat(newString, occurrence + strlen(defineName));

            // Update the file content and move to the next occurrence
            fileContent = newString;
            occurrence = strstr(fileContent, defineName);
        }
    }
    return fileContent;
}

/**
 * @brief Modify the value of DefineDirective structs if the name of one struct
 * is equal to the value of another struct
 *
 * @param defines Pointer to an array of DefineDirective structs
 * @param defineCount The number of DefineDirective structs in the array
 */
void changeStructDirectivesDefine(struct DefineDirective *defines, int *defineCount)
{
    // Iterate through all define directives
    for (int i = 0; i < *defineCount; i++)
    {
        // Compare current directive with all other directives
        for (int j = 0; j < *defineCount; j++)
        {
            // Check if current directive is not the same as the one being compared
            if (i != j && strcmp(defines[i].name, defines[j].value) == 0)
            {
                // Copy value of current directive to the directive being compared
                strcpy(defines[j].value, defines[i].value);
            }
        }
    }
}

/**
 * @brief Removes all DefineDirective structs whose value is enclosed in parentheses.
 *
 * @param defines Pointer to an array of DefineDirective structs
 * @param defineCount Pointer to an integer representing the number of DefineDirective structs in the array
 */
void removeParenthesisDefine(struct DefineDirective *defines, int *defineCount)
{
    // Iterate through defines array
    for (int i = 0; i < *defineCount; i++)
    {
        // Check if the first and last character of the value is '(' and ')' respectively
        if (defines[i].value[0] == '(' && defines[i].value[strlen(defines[i].value) - 1] == ')')
        {
            // Shift all elements from i+1 to the left by 1 to remove the current element
            for (int j = i; j < *defineCount - 1; j++)
            {
                defines[j] = defines[j + 1];
            }
            // Decrement the defineCount by 1
            (*defineCount)--;
            // Decrement the index by 1 to check the same index again
            i--;
        }
    }
}

/**
 * @brief Removes all DefineDirective structs whose value is enclosed in parentheses.
 *
 * @param defines Pointer to an array of DefineDirective structs
 * @param defineCount Pointer to an integer representing the number of DefineDirective structs in the array
 */
void removeAfterLastStringDefine(struct DefineDirective *defines, int *defineCount)
{
    // iterate over all the elements of defines
    for (int i = 0; i < *defineCount; i++)
    {
        // iterate over the chars of the value of the define
        for (int j = 0; j < strlen(defines[i].value); j++)
        {
            // if the current char is a space
            if (defines[i].value[j] == ' ')
            {
                // replace it by null char
                defines[i].value[j] = '\0';
            }
        }
    }
}

/**
 * @brief Removes all #define directives from a string.
 *
 * @param fileContent The file content to be modified
 */
void removeDefine(char *fileContent)
{
    // Initialize lineStart to the beginning of fileContent
    char *lineStart = fileContent;
    char *defineStart;
    // While there is still content in fileContent
    while (lineStart != NULL)
    {
        // Check if line starts with "#define "
        defineStart = strstr(lineStart, "#define ");
        // If no more define statements, break
        if (defineStart == NULL)
        {
            break;
        }
        // Find the start of the next line
        char *nextLineStart = strchr(defineStart, '\n');
        // If there is no next line, remove the rest of the content
        if (nextLineStart == NULL)
        {
            *defineStart = '\0';
            break;
        }
        // Get the length of the define statement
        int len = nextLineStart - defineStart + 1;
        // Move the rest of the content to the position of the define statement
        memmove(defineStart, nextLineStart + 1, strlen(nextLineStart));
        // Update lineStart to the new position
        lineStart = defineStart;
    }
}

/**
 * @brief Processes a string to find and extract "#define" directives and their corresponding values
 *
 * @param fileContent The string to be processed
 * @return char* The modified string
 */
char *directivesDefine(char *fileContent)
{
    struct DefineDirective defines[MAX_DEFINES] = {0}; // Initialize an array of DefineDirective structs
    int defineCount = 0;                               // Initialize the count of defines
    char *lineStart = fileContent;                     // Set lineStart to the start of fileContent
    char *newFileContent;                              // Initialize newFileContent

    // Iterate through the fileContent
    while (lineStart != NULL)
    {
        // Search for "#define " in the fileContent
        lineStart = strstr(lineStart, "#define ");
        // If no more "#define" statements, break
        if (lineStart == NULL)
        {
            break;
        }
        // Get the start of the name of the define
        char *nameStart = lineStart + strlen("#define ");
        // Get the end of the name of the define
        char *nameEnd = nameStart;
        // Iterate through the name, while it's alphanumeric or an underscore
        while (isalnum(*nameEnd) || *nameEnd == '_')
        {
            nameEnd++;
        }
        // If the name is empty, continue to the next line
        if (nameStart == nameEnd)
        {
            lineStart = nameEnd;
            continue;
        }
        // Get the start of the value of the define
        char *valueStart = nameEnd;
        // Iterate through the value, while it's a whitespace
        while (isspace(*valueStart))
        {
            valueStart++;
        }
        // Get the end of the value of the define
        char *valueEnd = strchr(valueStart, '\r');
        // If valueEnd is NULL, continue to the next line
        if (valueEnd == NULL)
        {
            lineStart = valueStart;
            continue;
        }
        // Get the length of the name
        int nameLen = nameEnd - nameStart;
        // Get the length of the value
        int valueLen = valueEnd - valueStart;
        // If the name or value is too long, continue to the next line
        if (nameLen >= MAX_NAME_LEN || valueLen >= MAX_NAME_LEN)
        {
            lineStart = valueEnd;
            continue;
        }
        // Copy the name to the current define in the defines array
        memcpy(defines[defineCount].name, nameStart, nameLen);
        // Copy the value to the current define in the defines array
        memcpy(defines[defineCount].value, valueStart, valueLen);
        // Add a null char to the end of the name
        defines[defineCount].name[nameLen] = '\0';
        // Add a null char to the end of the value
        defines[defineCount].value[valueLen] = '\0';
        // Increase the defineCount
        defineCount++;
        // Update the lineStart to the next line
        lineStart = valueEnd;
    }
    // If no matches are found
    if (defineCount == 0)
    {
        printf("No matches found");
        return;
    }
    else
    {
        // Remove the define statements from fileContent
        removeDefine(fileContent);
        // Remove define statements with parenthesis
        removeParenthesisDefine(defines, &defineCount);
        // Remove text after the last string in define statements
        removeAfterLastStringDefine(defines, &defineCount);
        // Change struct directives in define statements
        changeStructDirectivesDefine(defines, &defineCount);
        // Replace the define statements with their corresponding values
        newFileContent = replaceDefine(fileContent, defines, defineCount);
    }
    return newFileContent;
}

// ---------------------------------------------------------------------------------------
// START OF 1.C) #ifndef - #endif
// ---------------------------------------------------------------------------------------
// TODO: 1.C) #ifdef - #endif
/**
 * @brief Replaces all occurences of a if directive in a string with its corresponding instructions if condition is true, 
 * otherwise the if directive is just removed.
 *
 * @param fileContent The string to be modified
 * @param condition The result of the if directive condition
 * @return char* The modified string
 */
char* replaceIfdef(char *fileContent, int condition) 
{
    char *newContent;
    char *ifStart = strstr(fileContent, "#if");
    char *ifEnd = strstr(ifStart, "#endif");
    if (condition) {
        // First part of the file
        char *ifStart = strstr(fileContent, "#if");
        int firstPartEnd = ifStart - fileContent;

        // Directive part
        char *ifInstructionStart = strstr(ifStart, "\n") + 1;
        int len = ifEnd - 1 - ifInstructionStart;
        char *directive= malloc(sizeof(char) * len);
        memcpy(directive, ifInstructionStart, len);
        directive[len] = '\0';

        // Second part of the file
        char *secondPartStart = strstr(ifEnd, "\n");

        // Build new content without #if and #endif
        newContent = malloc(strlen(fileContent));
        memcpy(newContent, fileContent, firstPartEnd);
        strcat(newContent, directive);
        strcat(newContent, secondPartStart);
        free(directive);
    }
    else {
        // First part of the file
        int firstPartEnd = ifStart - fileContent-1;

        // Second part of the file
        char *secondPartStart = strstr(ifEnd, "\n");

        // Build new content without #if and #endif
        newContent = malloc(strlen(fileContent));
        memcpy(newContent, fileContent, firstPartEnd);
        strcat(newContent, secondPartStart);
    }
    return newContent;
}

/**
 * @brief Processes a string to find and extract "#if #endif" directives and their conditions expression
 *
 * @param fileContent The string to be processed
 * @return char* The modified string
 */
char* directivesIfdef(char *fileContent)
{
    char *ifStart = strstr(fileContent, "#if");
    while (ifStart != NULL)
    {
        // Recovery of the left value
        char *leftValueStart = ifStart + strlen("#if ");
        if (leftValueStart == NULL)
        {
            break;
        }
        if (*leftValueStart == '(') leftValueStart++;
        char *leftValueEnd = leftValueStart;
        while (isalnum(*leftValueEnd) || *leftValueEnd == '_')
        {
            leftValueEnd++;
        }
        if (leftValueStart == leftValueEnd)
        {
            ifStart = leftValueEnd;
        }
        int lenLeftValue = leftValueEnd - leftValueStart;

        // Recovery of the right value
        char *rightValueStart = leftValueEnd + strlen(" == ");
        if (rightValueStart == NULL)
        {
            break;
        }
        char *rightValueEnd = rightValueStart;
        while (isalnum(*rightValueEnd) || *rightValueEnd == '_')
        {
            rightValueEnd++;
        }
        if (rightValueStart == rightValueEnd)
        {
            ifStart = rightValueEnd;
        }
        int lenRightValue = rightValueEnd - rightValueStart;

        char *leftValue = malloc(sizeof(char) * lenLeftValue);
        memcpy(leftValue, leftValueStart, lenLeftValue);
        leftValue[lenLeftValue] = '\0';
        char *rightValue = malloc(sizeof(char) * lenRightValue);
        memcpy(rightValue, rightValueStart, lenRightValue);
        rightValue[lenRightValue] = '\0';
        
        // Conversion from string to int 
        int intLeftValue;
        int intRightValue;
        sscanf(leftValue, "%d", &intLeftValue);
        sscanf(rightValue, "%d", &intRightValue);

        free(leftValue);
        free(rightValue);

        // Evaluation of the condition
        int condition = intLeftValue == intRightValue;
        fileContent = replaceIfdef(fileContent, condition);

        ifStart = strstr(rightValueEnd, "#if");
    }
    return fileContent;
}

// ---------------------------------------------------------------------------------------
// START OF 2) Parametrized macros
// ---------------------------------------------------------------------------------------
// TODO: 2) Parametrized macros
void parametrizedMacros()
{
}

// ---------------------------------------------------------------------------------------
// START OF 3) Operator backslash “\”
// ---------------------------------------------------------------------------------------
// TODO: 3) Operator backslash “\”
void operatorBackslash()
{
}

// ---------------------------------------------------------------------------------------
// START OF 4) Eliminate comments
// ---------------------------------------------------------------------------------------

// TODO: 4) Eliminate comments and replace each of them by a space (empty lines are not eliminated)

/**
 * @brief Removes comments from a string
 *
 * @param fileContent The fileContent to be processed
 */
void removeComments(char *fileContent)
{
    int i, j;
    // Iterate through the file contents
    for (i = 0; fileContent[i] != '\0'; i++)
    {
        // Check for single line comments
        if (fileContent[i] == '/' && fileContent[i + 1] == '/')
        {
            // Replace the rest of the line with spaces
            for (j = i; fileContent[j] != '\n'; j++)
                fileContent[j] = ' ';
        }
        // Check for multi-line comments
        if (fileContent[i] == '/' && fileContent[i + 1] == '*')
        {
            // Replace the comment with spaces
            for (j = i; !(fileContent[j] == '*' && fileContent[j + 1] == '/'); j++)
                fileContent[j] = ' ';
            fileContent[j] = ' ';
            fileContent[j + 1] = ' ';
        }
    }
}