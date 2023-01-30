#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <unistd.h>

// ---------------------------------------------------------------------------------------
// START OF 2) Parametrized macros
// ---------------------------------------------------------------------------------------
// void replaceMacroWithValue(struct ParametrizedMacro macro, char *macroName, char *args[], char *fileContent)
// {
//     char newString[strlen(fileContent)];
//     strcpy(newString, fileContent);

//     char *macroCall = strstr(fileContent, macroName);
//     while (macroCall != NULL)
//     {
//         char *macroCallEnd = macroCall + strlen(macroName);
//         if (isalnum(*(macroCall - 1)) || isalnum(*macroCallEnd))
//         {
//             macroCall = strstr(macroCallEnd, macroName);
//             continue;
//         }

//         // Check if the macro call has the correct number of arguments
//         int openParenCount = 0;
//         int closeParenCount = 0;
//         while (*macroCallEnd != '\0')
//         {
//             if (*macroCallEnd == '(')
//             {
//                 openParenCount++;
//             }
//             else if (*macroCallEnd == ')')
//             {
//                 closeParenCount++;
//             }
//             if (openParenCount == closeParenCount)
//             {
//                 break;
//             }
//             macroCallEnd++;
//         }
//         if (openParenCount != closeParenCount)
//         {
//             macroCall = strstr(macroCallEnd, macroName);
//             continue;
//         }

//         // Replace the macro call with the macro's body and arguments
//         char replacement[strlen(macro.body)];
//         strcpy(replacement, macro.body);
//         for (int i = 0; i < macro.paramCount; i++)
//         {
//             char param[strlen(macro.params[i]) + 2];
//             sprintf(param, "%c%s%c", '{', macro.params[i], '}');
//             char *paramPlaceholder = strstr(replacement, param);
//             if (paramPlaceholder == NULL)
//             {
//                 continue;
//             }
//             char newReplacement[strlen(replacement) - strlen(param) + strlen(args[i])];
//             memcpy(newReplacement, replacement, paramPlaceholder - replacement);
//             strcat(newReplacement, args[i]);
//             strcat(newReplacement, paramPlaceholder + strlen(param));
//             strcpy(replacement, newReplacement);
//         }

//         // Copy the replacement into the new string
//         int lenToCopy = macroCall - fileContent;
//         strncpy(newString, fileContent, lenToCopy);
//         int lenOfReplacement = strlen(replacement);
//         strncpy(newString + lenToCopy, replacement, lenOfReplacement);
//         strcpy(newString + lenToCopy + lenOfReplacement, macroCallEnd);
//         fileContent = newString;
//         macroCall = strstr(fileContent, macroName);
//     }
// }

// char *replaceParametrizedMacros(char *fileContent, struct ParametrizedMacro *macros, int macroCount)
// {
//     // Iterate over the parametrized macros
//     for (int i = 0; i < macroCount; i++)
//     {
//         // Get the current macro's name and value
//         char *macroName = macros[i].name;
//         char *macroBody = macros[i].body;

//         // Find the first occurrence of the macro name in the file content
//         char *occurrence = strstr(fileContent, macroName);

//         // Iterate over all occurrences of the macro name in the file content
//         while (occurrence != NULL)
//         {
//             // Check if the occurrence is not part of another word
//             if (isalnum(*(occurrence - 1)) || isalnum(*(occurrence + strlen(macroName))))
//             {
//                 // Move to the next occurrence if it is part of another word
//                 occurrence = strstr(occurrence + strlen(macroName), macroName);
//                 continue;
//             }

//             // Replace the macro with its value, including the parameter values
//             char *newString = replaceMacroWithValue(fileContent, occurrence, macroBody, macros[i].params, macros[i].paramCount);

//             // Update the file content and move to the next occurrence
//             fileContent = newString;
//             occurrence = strstr(fileContent, macroName);
//         }
//     }
//     return fileContent;
// }
// char *parametrizedMacros(char *fileContent)
// {
//     struct ParametrizedMacro macro[100] = {0}; // Initialize an array of ParametrizedMacro structs
//     int macroCount = 0;                        // Initialize the count of macros
//     int paramCount = 0;                        // Initialize the count of parameters
//     char *lineStart = fileContent;             // Set lineStart to the start of fileContent
//     // Iterate through the fileContent
//     while (lineStart != NULL)
//     {
//         // Search for "#define " in the fileContent
//         lineStart = strstr(lineStart, "#define ");
//         // If no more "#define" statements, break
//         if (lineStart == NULL)
//         {
//             break;
//         }
//         // Get the start of the name of the macro
//         char *nameStart = lineStart + strlen("#define ");
//         // Get the end of the name of the macro
//         char *nameEnd = nameStart;
//         // Iterate through the name, while it's alphanumeric or an underscore
//         while (isalnum(*nameEnd) || *nameEnd == '_')
//         {
//             nameEnd++;
//         }
//         // If the name is empty, continue to the next line
//         if (nameStart == nameEnd)
//         {
//             lineStart = nameEnd;
//             continue;
//         }
//         // Get the start of the parameters of the macro
//         char *paramsStart = strchr(nameStart, '(');
//         // If paramsStart is NULL, continue to the next line
//         if (paramsStart == NULL)
//         {
//             lineStart = nameEnd;
//             continue;
//         }
//         // Get the end of the parameters of the macro
//         char *paramsEnd = strchr(paramsStart, ')');
//         // If paramsEnd is null, there are no parameters
//         if (paramsEnd == NULL)
//         {
//             // Save the macro name and an empty string for the parameters
//             strncpy(macro[macroCount].name, nameStart, nameEnd - nameStart);
//             macro[macroCount].name[nameEnd - nameStart] = '\0';
//             macro[macroCount].params[0][0] = '\0';
//         }
//         else
//         {
//             // Get the length of the parameters
//             int paramsLen = paramsEnd - paramsStart - 1;
//             // Save the macro name
//             strncpy(macro[macroCount].name, nameStart, nameEnd - nameStart);
//             macro[macroCount].name[nameEnd - nameStart] = '\0';
//             // create a temporary char array to hold the parameters
//             char tempParams[paramsLen + 1];
//             strncpy(tempParams, paramsStart + 1, paramsLen);
//             tempParams[paramsLen] = '\0';
//             // Split the parameters using the comma+space separator
//             char *token = strtok(tempParams, ", ");
//             paramCount = 0;
//             while (token != NULL && paramCount < 100)
//             {
//                 strncpy(macro[macroCount].params[paramCount], token, strlen(token));
//                 macro[macroCount].params[paramCount][strlen(token)] = '\0';
//                 macro[macroCount].paramCount = paramCount + 1;
//                 token = strtok(NULL, ", ");
//                 paramCount++;
//             }
//             // Save the number of parameters in the struct
//             // Get the start of the function body
//             char *bodyStart = strchr(paramsEnd, '{') + 1;
//             // Get the end of the function body
//             char *bodyEnd = strchr(bodyStart, '}');
//             if (bodyEnd == NULL)
//             {
//                 lineStart = nameEnd;
//                 continue;
//             }
//             // Get the length of the function body
//             int bodyLen = bodyEnd - bodyStart - 1;
//             // Save the function body
//             strncpy(macro[macroCount].body, bodyStart, bodyLen);
//             macro[macroCount].body[bodyLen] = '\0';
//             macroCount++;
//             // Update lineStart to the end of the macro
//             lineStart = bodyEnd;
//         }
//     }
//     removeDefine(fileContent);
//     // char *newFileContent = printParametrizedMacro(fileContent, macro, macroCount);
//     return fileContent;
// }
