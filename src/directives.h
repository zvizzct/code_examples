
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

// TODO: 1.A) #include
void directivesInclude()
{
}

// TODO: 1.B) #define

void directivesDefine(char *fileContent)
{

    int i = 0;
    int match = 0;
    int contentLen = strlen(fileContent);
    int nameIndex = 0;
    int valueIndex = 0;
    char *targetString = "#define";
    struct DefineDirective defines[100];
    int defineCount = 0;

    for (int pos = 0; pos < contentLen; pos++)
    {
        i = (fileContent[pos] == targetString[i]) ? i += 1 : 0;

        if (i == strlen(targetString))
        {
            match = 1;
            // Iterate over the next characters to find the name of the constant
            int namePos = pos + 2;

            while (fileContent[namePos] != ' ' && fileContent[namePos] != '\t' && fileContent[namePos] != '\n')
            {
                defines[defineCount].name[nameIndex] = fileContent[namePos];
                namePos++;
                nameIndex++;
            }
            // Iterate over the next characters to find the value of the constant
            int valuePos = namePos;
            printf("%c", fileContent[valuePos]);
            while (fileContent[valuePos] != '\n')
            {
                defines[defineCount].value[valueIndex] = fileContent[valuePos];
                valuePos++;
                valueIndex++;
            }
            printf("\n%d\n", defineCount);
            printf("Found match at position %d!\n", pos - strlen(targetString) + 1);
            printf("Constant name: %s\n", defines[defineCount].name);
            printf("Constant value: %s\n", defines[defineCount].value);
            // Reemplazar o procesar el buffer o lo que sea que necesites hacer
            defineCount++;
            i = 0;
        }
    }

    if (!match)
        printf("No matches found");
}

// TODO: 1.C) #ifdef - #endif
void directivesIfdef()
{
}

// TODO: 2) Parametrized macros
void parametrizedMacros()
{
}

// TODO: 3) Operator backslash “\”
void operatorBackslash()
{
}

// TODO: 4) Eliminate comments and replace each of them by a space (empty lines are not eliminated)
void eliminateComments()
{
}
