#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <unistd.h>

// ---------------------------------------------------------------------------------------
// START OF 3) Operator backslash “\”
// ---------------------------------------------------------------------------------------
/**
 * @brief Removes the backslash operator and put the next line on the same line
 *
 * @param fileContent The content of the file
 * @return char* The new file content
 */
char *operatorBackslash(char *fileContent)
{
    // get the length of the input string
    int len = strlen(fileContent);
    // flag to track whether a backslash has been encountered
    int escape = 0;

    // loop through each character in the string
    for (int i = 0; i < len; i++)
    {
        // if current character is a backslash
        if (fileContent[i] == '\\')
        {
            // replace the backslash with a space
            // set escape flag
            escape = 1;
        }
        // if the next character is a newline and the escape flag is set
        else if ((fileContent[i] == '\r' || fileContent[i] == '\n') && escape)
        {
            // remove the \ and the newline
            fileContent[i - 1] = ' ';
            fileContent[i + 1] = ' ';

            // remove spaces after the newline
            int j = i + 1;
            while (fileContent[j] == ' ')
            {
                for (int k = j; k < len; k++)
                {
                    fileContent[k] = fileContent[k + 1];
                }
                len--;
            }
            // remove the newline
            for (int j = i; j < len; j++)
            {
                fileContent[j] = fileContent[j + 1];
            }
            // reset escape flag
            escape = 0;
            // decrement i to account for removed newline
            i--;
            // decrement len to account for removed newline
            len--;
        }
        else
        {
            // reset escape flag
            escape = 0;
        }
    }
    // return modified string
    return fileContent;
}
