
#include <stdio.h> 
#include <stdlib.h> // 

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

//TODO: 1.A) #include
void directivesInclude() {
  
}

//TODO: 1.B) #define

void findAndReplace(char *fileContent, char *name, char *value) {
    char *temp;
    char *occurrence = strstr(fileContent, name);

    while (occurrence != NULL) {
        temp = strdup(occurrence + strlen(name));
        strncpy(occurrence, value, strlen(value));
        strcat(occurrence, temp);
        free(temp);
        occurrence = strstr(fileContent, name);
    }
}

void deleteLine(char *fileContent, char *line) {
    char *temp;
    char *occurrence = strstr(fileContent, line);

    if (occurrence != NULL) {
        temp = strdup(occurrence + strlen(line));
        strncpy(occurrence, temp, strlen(temp));
        free(temp);
    }
}

void directivesDefine(char *fileContent) {

    char *line, *name, *value;
    char *token, *temp;
    char *delimiter = "\n";
    char *define = "#define ";
    // printf("%s", fileContent);
    line = strtok(fileContent, delimiter);
    if(line != NULL)
        printf("%s", line);
    // printf("%s", line);

    // while (line != NULL) {
    //     if (strstr(line, define) != NULL) {
    //         temp = strdup(line + strlen(define));
    //         token = strtok(temp, " ");
    //         name = strdup(token);
    //         token = strtok(NULL, " ");
    //         value = strdup(token);

    //         findAndReplace(fileContent, name, value);
    //         deleteLine(fileContent, line);
    //     }
    //     line = strtok(NULL, delimiter);
    // }

}

//TODO: 1.C) #ifdef - #endif
void directivesIfdef() {
  
}

//TODO: 2) Parametrized macros
void parametrizedMacros() {
  
}

//TODO: 3) Operator backslash “\”
void operatorBackslash() {
  
}

//TODO: 4) Eliminate comments and replace each of them by a space (empty lines are not eliminated)
void eliminateComments() {
  
}




