
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
void removeDirectivesDefine(char *fileContent, int position)
{
    int i, j;
    for (i = position; fileContent[i] != '\n'; i++)
    {
        fileContent[i] = ' ';
    }
}
void directivesDefine(char *fileContent)
{

    int i = 0;
    int match = 0;
    int contentLen = strlen(fileContent);
    int nameIndex = 0;
    int valueIndex = 0;
    char *targetString = "#define ";
    struct DefineDirective defines[100];
    int defineCount = 0;

    for (int pos = 0; pos < contentLen; pos++)
    {
        i = (fileContent[pos] == targetString[i]) ? i += 1 : 0;

        if (i == strlen(targetString))
        {
            match = 1;
            // Iterate over the next characters to find the name of the constant
            int namePos = pos + 1;

            while (fileContent[namePos] != ' ' && fileContent[namePos] != '\t' && fileContent[namePos] != '\n')
            {
                defines[defineCount].name[nameIndex] = fileContent[namePos];
                namePos++;
                nameIndex++;
            }
            defines[defineCount].name[nameIndex] = '\0';
            // Iterate over the next characters to find the value of the constant
            int valuePos = namePos;
            while (fileContent[valuePos] != '\n')
            {
                if (fileContent[valuePos] == ' ' || fileContent[valuePos] == '\t')
                {
                    valuePos++;
                    continue;
                }
                defines[defineCount].value[valueIndex] = fileContent[valuePos];
                valuePos++;
                valueIndex++;
            }
            defines[defineCount].value[valueIndex] = '\0';
            defineCount++;
            removeDirectivesDefine(fileContent, pos - strlen(targetString) + 1);
            i = 0;
            nameIndex = 0;
            valueIndex = 0;
        }
    }
    if (!match)
        printf("No matches found");
    else
    {
        replaceDirectivesDefine(fileContent, defines, defineCount);
    }
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
