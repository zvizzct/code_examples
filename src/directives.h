#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <unistd.h>

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
void directivesInclude()
{
}
// ------------------------------

// ------------------------------
// START OF 1.B) #define
// ------------------------------

/*
This function uses nested loops to iterate through the array of DefineDirective
structs and the given file content.
For each struct in the array,it compares its name with a substring of the given
file content starting from the current index.
If a match is found, the function replaces the substring with the value of the struct,
and shift the rest of the file content to fill the gap.
*/

/**
 * @brief Replace all occurances of a define directive name in a file content with its
 * corresponding value
 *
 * @param fileContent A pointer to the string which will be modified
 * @param defines Pointer to an array of DefineDirective structs
 * @param defineCount The number of DefineDirective structs in the array
 *
 */
void replaceDirectivesDefine(char *fileContent, struct DefineDirective *defines, int defineCount)
{

    int i, j, k, match, nameLen, valueLen, contentLen = strlen(fileContent);
    char *name, *value;
    for (i = 0; i < contentLen; i++)
    {
        for (j = 0; j < defineCount; j++)
        {
            name = defines[j].name;
            nameLen = strlen(name);
            match = 1;
            for (k = 0; k < nameLen; k++)
            {
                if (fileContent[i + k] != name[k])
                {
                    match = 0;
                    break;
                }
            }
            if (match)
            {
                value = defines[j].value;
                valueLen = strlen(value);
                for (k = 0; k < valueLen; k++)
                {
                    fileContent[i + k] = value[k];
                }
                for (k = i + valueLen; k < contentLen; k++)
                {
                    fileContent[k] = fileContent[k + nameLen - valueLen];
                }
                break;
            }
        }
    }
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
void directivesDefine2(char *fileContent)
{
    struct DefineDirective defines[MAX_DEFINES] = {0};
    int defineCount = 0;
    char *lineStart = fileContent;
    while (lineStart != NULL)
    {
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
        // remove_define2(fileContent, defines[defineCount].name);
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
        removeParenthesisDefine(defines, &defineCount);
        removeAfterLastStringDefine(defines, &defineCount);
        changeStructDirectivesDefine(defines, &defineCount);
        for (int i = 0; i < defineCount; i++)
        {
            printf("name: %s, value: %s\n", defines[i].name, defines[i].value);
        }
    }
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

int remove_define2(char *fileContent, char *defineName)
{
    char *defineStart = strstr(fileContent, defineName);
    if (defineStart == NULL)
    {
        return 0;
    }
    char *defineEnd = strchr(defineStart, '\n');
    if (defineEnd == NULL)
    {
        return 0;
    }
    memmove(defineStart, defineEnd, strlen(defineEnd) + 1);
    return 1;
}
