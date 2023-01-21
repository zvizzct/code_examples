
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
This function uses the "memset" function to set the memory of the "name" and
"value" fields of the DefineDirective struct at the specified position to zero.
This "removes" or clears the values stored in these fields of the struct.
*/
/**
 * @brief Remove the DefineDirective struct at a specified position
 *
 * @param defines Pointer to an array of DefineDirective structs
 * @param pos The position of the struct to remove
 */
void removeStructDirectivesDefine(struct DefineDirective *defines, int pos)
{
    memset(defines[pos].name, 0, sizeof(defines[pos].name));
    memset(defines[pos].value, 0, sizeof(defines[pos].value));
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
void changeStructDirectivesDefine(struct DefineDirective *defines, int defineCount)
{
    for (int i = 0; i < defineCount; i++)
    {
        for (int j = 0; j < defineCount; j++)
        {
            if (i != j && strcmp(defines[i].name, defines[j].value) == 0)
            {
                strcpy(defines[j].value, defines[i].value);
            }
        }
    }
}

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
This function uses a for loop to iterate through the characters of the file
content starting from the given position.
The loop continues until it reaches a newline character, at which point the loop breaks.
For each character in the loop, the function replaces it with a space character,
effectively removing the define directive from the string.
*/
/**
 * @brief Remove a define directive from a file content
 *
 * @param fileContent A pointer to the file content which will be modified
 * @param position The starting position of the define directive in the string
 *
 */
void removeDirectivesDefine(char *fileContent, int position)
{
    int i, j;
    for (i = position; fileContent[i] != '\n'; i++)
    {
        fileContent[i] = ' ';
    }
}

/*
This function uses a for loop to iterate through the characters of the file content.
It looks for instances of the string "#define" in the content, when found it
starts to extract the define name and value.
If the define has a () it will remove the whole define, otherwise it will extract
the name and value and store them in a struct array.
After the loop it will call to changeStructDirectivesDefine to modify the defines
if necessary, and then call to replaceDirectivesDefine to replace the names with
the values in the fileContent.
If no matches are found it will print a message.
*/
/**
 * @brief Process all #define directives in a string and modify the string
 * according to the directives
 *
 * @param fileContent A pointer to the string which will be modified
 *
 */
void directivesDefine(char *fileContent)
{
    int i = 0;
    int match = 0;
    int contentLen = strlen(fileContent);
    char *targetString = "#define ";
    struct DefineDirective defines[100];
    int defineCount = 0;
    int parOpen = 0;

    for (int pos = 0; pos < contentLen; pos++)
    {
        i = (fileContent[pos] == targetString[i]) ? i += 1 : 0;

        if (i == strlen(targetString))
        {
            match = 1;
            int namePos = pos + 1;
            parOpen = 0;
            char name[100] = {0};
            char value[100] = {0};
            int nameIndex = 0;
            int valueIndex = 0;

            while (fileContent[namePos] != ' ' && fileContent[namePos] != '\t' && fileContent[namePos] != '\n')
            {
                if (fileContent[namePos] == '(' || fileContent[namePos] == ')')
                    parOpen++;

                name[nameIndex] = fileContent[namePos];
                namePos++;
                nameIndex++;
            }

            int valuePos = namePos;
            int contSpaces = 0;
            while (fileContent[valuePos] != '\n')
            {
                if (fileContent[valuePos] == ' ' || fileContent[valuePos] == '\t')
                {
                    if (contSpaces == 0)
                    {
                        valuePos++;
                        contSpaces++;
                        continue;
                    }
                    else
                    {
                        break;
                    }
                }
                value[valueIndex] = fileContent[valuePos];
                valuePos++;
                valueIndex++;
            }

            if (parOpen == 2)
            {
                removeDirectivesDefine(fileContent, pos - strlen(targetString) + 1);
                continue;
            }

            memcpy(defines[defineCount].name, name, sizeof(name));
            memcpy(defines[defineCount].value, value, sizeof(value));
            removeDirectivesDefine(fileContent, pos - strlen(targetString) + 1);
            defineCount++;
            i = 0;
        }
    }

    if (!match)
        printf("No matches found");
    else
    {
        changeStructDirectivesDefine(defines, defineCount);
        replaceDirectivesDefine(fileContent, defines, defineCount);
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