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

// ------------------------------
// START OF 1.A) #include
// ------------------------------
// TODO: 1.A) #include
char *replaceInclude(char *fileContent, char *newFileContent, char *fileName)
{
    char *includeLine = "#include";
    char *includeFile = malloc(strlen(fileName) + 3);
    sprintf(includeFile, "\"%s\"", fileName);
    char *include = malloc(strlen(includeLine) + strlen(includeFile) + 3); // +3 for quotes and whitespace and null char
    sprintf(include, "%s %s", includeLine, includeFile);
    char *start, *end;
    start = strstr(fileContent, include);
    end = start + strlen(include);
    char *result = malloc(strlen(fileContent) + strlen(newFileContent) + 1);
    if (start != NULL)
    {
        strncpy(result, fileContent, start - fileContent);
        strcpy(result + (start - fileContent), newFileContent);
        strcpy(result + (start - fileContent) + strlen(newFileContent), end);
    }
    else
    {
        strcpy(result, fileContent);
    }
    free(include);
    free(includeFile);
    return result;
}

char *processFileNameInclude(char *fileName)
{
    int len = strlen(fileName);
    char *newFileName = malloc(len + 9);
    strcpy(newFileName, "examples");
    if (fileName[0] == '.')
    {
        strcat(newFileName, fileName + 1);
    }
    else
    {
        strcat(newFileName, fileName);
    }
    return newFileName;
}

char *directivesInclude(char *fileContent)
{
    char *updatedFileContent = fileContent;
    char *includeStart = strstr(fileContent, "#include");
    while (includeStart != NULL)
    {
        char *newFileContent;
        char *fileStart = strchr(includeStart, '"');
        if (fileStart == NULL)
        {
            break;
        }
        char *fileEnd = strchr(fileStart + 1, '"');
        if (fileEnd == NULL)
        {
            break;
        }
        int len = fileEnd - fileStart - 1;
        char *fileName = (char *)malloc(sizeof(char) * (len + 1));
        memcpy(fileName, fileStart + 1, len);
        fileName[len] = '\0';
        char *fullName = processFileNameInclude(fileName);

        // Open the file here
        FILE *fp = fopen(fullName, "r");
        if (fp != NULL)
        {
            newFileContent = readFile(fp);
            updatedFileContent = replaceInclude(updatedFileContent, newFileContent, fileName);
            fclose(fp);
        }

        free(fileName);
        includeStart = strstr(fileEnd, "#include");
    }
    return updatedFileContent;
}

// ------------------------------

// ------------------------------
// START OF 1.B) #define
// ------------------------------

/*
This function takes in a char* fileContent representing the string to be modified,
an array of DefineDirective structs defines, and an int defineCount representing the number of
DefineDirective structs in the array.
The function iterates through the array of DefineDirective structs, and for each struct, it uses
the strstr function to find all occurrences of the struct's name field in the fileContent string.
If an occurrence is found, the function checks if the character before or after the occurrence is
alphanumeric, if so it continues to the next occurrence, otherwise it replaces the occurrence with
the corresponding value of the value field of the DefineDirective struct.
The function then returns the modified fileContent string.
*/

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
    for (int i = 0; i < defineCount; i++)
    {
        char *defineName = defines[i].name;
        char *defineValue = defines[i].value;
        char *occurrence = strstr(fileContent, defineName);
        while (occurrence != NULL)
        {
            if (isalnum(*(occurrence - 1)) || isalnum(*(occurrence + strlen(defineName))))
            {
                occurrence = strstr(occurrence + strlen(defineName), defineName);
                continue;
            }
            int remainingLen = strlen(occurrence) - strlen(defineName);
            char *newString = malloc(strlen(fileContent) - strlen(defineName) + strlen(defineValue) + 1);
            memcpy(newString, fileContent, occurrence - fileContent);
            strcat(newString, defineValue);
            strcat(newString, occurrence + strlen(defineName));
            fileContent = newString;
            occurrence = strstr(fileContent, defineName);
        }
    }
    return fileContent;
}

/*
This function uses nested loops to iterate through the array of DefineDirective structs.
For each struct, it compares its name to the value of all other structs.
If the name of one struct is equal to the value of another struct, the function copies
the value of the first struct to the second struct.
*/

/**
 * @brief Modify the value of DefineDirective structs if the name of one struct
 * is equal to the value of another struct
 *
 * @param defines Pointer to an array of DefineDirective structs
 * @param defineCount The number of DefineDirective structs in the array
 */
void changeStructDirectivesDefine(struct DefineDirective *defines, int *defineCount)
{
    for (int i = 0; i < *defineCount; i++)
    {
        for (int j = 0; j < *defineCount; j++)
        {
            if (i != j && strcmp(defines[i].name, defines[j].value) == 0)
            {
                strcpy(defines[j].value, defines[i].value);
            }
        }
    }
}
/*
This function takes in a pointer to an array of DefineDirective structs defines
and a pointer to an int defineCount, representing the number of DefineDirective
structs in the array.
The function iterates through the array of DefineDirective structs, and for each
struct, it checks if the first and last characters of the struct's value field
are '(' and ')' respectively.
If the condition is true, the function removes that struct from the array by
shifting all the following elements one position back and decreasing the defineCount.
*/

/**
 * @brief Removes all DefineDirective structs whose value is enclosed in parentheses.
 *
 * @param defines Pointer to an array of DefineDirective structs
 * @param defineCount Pointer to an integer representing the number of DefineDirective structs in the array
 */
void removeParenthesisDefine(struct DefineDirective *defines, int *defineCount)
{
    for (int i = 0; i < *defineCount; i++)
    {
        if (defines[i].value[0] == '(' && defines[i].value[strlen(defines[i].value) - 1] == ')')
        {
            for (int j = i; j < *defineCount - 1; j++)
            {
                defines[j] = defines[j + 1];
            }
            (*defineCount)--;
            i--;
        }
    }
}

/*
This function takes in a pointer to an array of DefineDirective structs defines and a
pointer to an int defineCount, representing the number of DefineDirective structs in the array.
The function iterates through the array of DefineDirective structs, and for each struct,
it checks if the first and last characters of the struct's value field are '(' and ')' respectively.
If the condition is true, the function removes that struct from the array by shifting
all the following elements one position back and decreasing the defineCount.
*/

/**
 * @brief Removes all DefineDirective structs whose value is enclosed in parentheses.
 *
 * @param defines Pointer to an array of DefineDirective structs
 * @param defineCount Pointer to an integer representing the number of DefineDirective structs in the array
 */
void removeAfterLastStringDefine(struct DefineDirective *defines, int *defineCount)
{
    for (int i = 0; i < *defineCount; i++)
    {
        for (int j = 0; j < strlen(defines[i].value); j++)
        {
            if (defines[i].value[j] == ' ')
            {
                defines[i].value[j] = '\0';
            }
        }
    }
}

/*
The function takes in a char* fileContent representing the string to be
processed. It initializes a pointer "lineStart" to the beginning of the fileContent
string and a pointer "defineStart". It uses a while loop to search for occurrences of
"#define " in the fileContent string using the strstr function. If an occurrence is found,
the function uses the strchr function to find the start of the next line after the
define directive. It then uses the memmove function to remove the define directive
from the fileContent string by moving the characters after the directive to the location
of the directive. The loop continues until there are no more occurrences of "#define"
found in the fileContent string.
*/

/**
 * @brief Removes all #define directives from a string.
 *
 * @param fileContent The file content to be modified
 */
void removeDefine(char *fileContent)
{
    char *lineStart = fileContent;
    char *defineStart;
    while (lineStart != NULL)
    {
        defineStart = strstr(lineStart, "#define ");
        if (defineStart == NULL)
        {
            break;
        }
        char *nextLineStart = strchr(defineStart, '\n');
        if (nextLineStart == NULL)
        {
            *defineStart = '\0';
            break;
        }
        int len = nextLineStart - defineStart + 1;
        memmove(defineStart, nextLineStart + 1, strlen(nextLineStart));
        lineStart = defineStart;
    }
}

/*
The function takes in a char* fileContent representing the string to be processed.
It initializes an array of DefineDirective structs defines and an int defineCount to 0.
It then uses the strstr function to find all occurrences of "#define" in the fileContent string.
If an occurrence is found, the function uses the strlen function to find the start of the name
and the value of the define directive.
It then copies the name and value of the define directive to the corresponding fields of the
DefineDirective struct and increments the defineCount.
The function then calls the removeParenthesisDefine(), removeAfterLastStringDefine() and
changeStructDirectivesDefine() function to process the extracted define directives, and the
replaceDirectives() function to replace all occurrences of the define directive names with
their corresponding values in the fileContent string.
*/

/**
 * @brief Processes a string to find and extract "#define" directives and their corresponding values
 *
 * @param fileContent The string to be processed
 * @return char* The modified string
 */
char *directivesDefine(char *fileContent)
{
    struct DefineDirective defines[MAX_DEFINES] = {0};
    int defineCount = 0;
    char *lineStart = fileContent;
    char *newFileContent;
    while (lineStart != NULL)
    { // coment
        lineStart = strstr(lineStart, "#define ");
        if (lineStart == NULL)
        {
            break;
        }
        char *nameStart = lineStart + strlen("#define ");
        char *nameEnd = nameStart;
        while (isalnum(*nameEnd) || *nameEnd == '_')
        {
            nameEnd++;
        }
        if (nameStart == nameEnd)
        {
            lineStart = nameEnd;
            continue;
        }
        char *valueStart = nameEnd;
        while (isspace(*valueStart))
        {
            valueStart++;
        }
        char *valueEnd = strchr(valueStart, '\n');
        if (valueEnd == NULL)
        {
            lineStart = valueStart;
            continue;
        }
        int nameLen = nameEnd - nameStart;
        int valueLen = valueEnd - valueStart;
        if (nameLen >= MAX_NAME_LEN || valueLen >= MAX_NAME_LEN)
        {
            lineStart = valueEnd;
            continue;
        }
        memcpy(defines[defineCount].name, nameStart, nameLen);
        memcpy(defines[defineCount].value, valueStart, valueLen);
        defines[defineCount].name[nameLen] = '\0';
        defines[defineCount].value[valueLen] = '\0';
        defineCount++;
        lineStart = valueEnd;
    }
    if (defineCount == 0)
    {
        printf("No matches found");
        return;
    }
    else
    {
        removeDefine(fileContent);
        removeParenthesisDefine(defines, &defineCount);
        removeAfterLastStringDefine(defines, &defineCount);
        changeStructDirectivesDefine(defines, &defineCount);
        newFileContent = replaceDefine(fileContent, defines, defineCount);
    }
    return newFileContent;
}

// ------------------------------

// ------------------------------
// START OF 1.C) #ifndef - #endif
// ------------------------------
// TODO: 1.C) #ifdef - #endif
void directivesIfdef()
{
}
// ------------------------------

// ------------------------------
// START OF 2) Parametrized macros
// ------------------------------
// TODO: 2) Parametrized macros
void parametrizedMacros()
{
}
// ------------------------------

// ------------------------------
// START OF 3) Operator backslash “\”
// ------------------------------
// TODO: 3) Operator backslash “\”
void operatorBackslash()
{
}
// ------------------------------

// ------------------------------
// START OF 4) Eliminate comments
// ------------------------------

// TODO: 4) Eliminate comments and replace each of them by a space (empty lines are not eliminated)
void eliminateComments()
{
}
// ------------------------------
