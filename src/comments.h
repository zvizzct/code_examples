/*
 * @file comments.h
 * @brief Removes comments from a file content
 */

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <unistd.h>

// ---------------------------------------------------------------------------------------
// START OF 4) Eliminate comments
// ---------------------------------------------------------------------------------------

/**
 * @brief Removes comments from a string
 *
 * @param fileContent The fileContent to be processed
 */
char *removeComments(char *fileContent)
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
    return fileContent;
}