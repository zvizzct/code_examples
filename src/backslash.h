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
    int len = strlen(fileContent);
    int escape = 0;
    for (int i = 0; i < len; i++)
    {
        if (fileContent[i] == '\\')
        {
            fileContent[i] = ' ';
            escape = 1;
        }
        else if (fileContent[i + 1] == '\n' && escape)
        {
            int j = i + 1 + 1;
            while (fileContent[j] == ' ')
            {
                for (int k = j; k < len; k++)
                {
                    fileContent[k] = fileContent[k + 1];
                }
                len--;
            }
            for (int j = i; j < len; j++)
            {
                fileContent[j] = fileContent[j + 1 + 1];
            }
            escape = 0;
            i--;
            len--;
        }
        else
        {
            escape = 0;
        }
    }
    return fileContent;
}