#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <unistd.h>

/**
 * @brief Struct to store a parametrized macro
 *
 * @param fileContent The content of the file
 * @return char* The new file content
 */
char *parametrizedMacros(char *fileContent)
{
    struct ParametrizedMacro macro[100] = {0}; // Initialize an array of ParametrizedMacro structs
    int macroCount = 0;                        // Initialize the count of macros
    int paramCount = 0;                        // Initialize the count of parameters
    char *lineStart = fileContent;             // Set lineStart to the start of fileContent
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
        // Get the start of the name of the macro
        char *nameStart = lineStart + strlen("#define ");
        // Get the end of the name of the macro
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
        // Get the start of the parameters of the macro
        char *paramsStart = strchr(nameStart, '(');
        // If paramsStart is NULL, continue to the next line
        if (paramsStart == NULL)
        {
            lineStart = nameEnd;
            continue;
        }
        // Get the end of the parameters of the macro
        char *paramsEnd = strchr(paramsStart, ')');
        // If paramsEnd is null, there are no parameters
        if (paramsEnd == NULL)
        {
            // Save the macro name and an empty string for the parameters
            strncpy(macro[macroCount].name, nameStart, nameEnd - nameStart);
            macro[macroCount].name[nameEnd - nameStart] = '\0';
            macro[macroCount].params[0][0] = '\0';
        }
        else
        {
            // Get the length of the parameters
            int paramsLen = paramsEnd - paramsStart - 1;
            // Save the macro name
            strncpy(macro[macroCount].name, nameStart, nameEnd - nameStart);
            macro[macroCount].name[nameEnd - nameStart] = '\0';
            // create a temporary char array to hold the parameters
            char tempParams[paramsLen + 1];
            strncpy(tempParams, paramsStart + 1, paramsLen);
            tempParams[paramsLen] = '\0';
            // Split the parameters using the comma+space separator
            char *token = strtok(tempParams, ", ");
            paramCount = 0;
            while (token != NULL && paramCount < 100)
            {
                strncpy(macro[macroCount].params[paramCount], token, strlen(token));
                macro[macroCount].params[paramCount][strlen(token)] = '\0';
                macro[macroCount].paramCount = paramCount + 1;
                token = strtok(NULL, ", ");
                paramCount++;
            }
            // Save the number of parameters in the struct
            // Get the start of the function body
            char *bodyStart = strchr(paramsEnd, '{') + 1;
            // Get the end of the function body
            char *bodyEnd = strchr(bodyStart, '}');
            if (bodyEnd == NULL)
            {
                lineStart = nameEnd;
                continue;
            }
            // Get the length of the function body
            int bodyLen = bodyEnd - bodyStart - 1;
            // Save the function body
            strncpy(macro[macroCount].body, bodyStart, bodyLen);
            macro[macroCount].body[bodyLen] = '\0';
            macroCount++;
            // Update lineStart to the end of the macro
            lineStart = bodyEnd;
        }
    }
    // removeDefine(fileContent);

    // char *newFileContent = printParametrizedMacro(fileContent, macro, macroCount);
    return fileContent;
}
