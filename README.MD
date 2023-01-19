# Preprocessor app
This application is a preprocessor for C or H files which can process a file and make the following changes:

## Description 
The preprocessor is a tool that allows you to process your code before it is compiled. This application can make the following changes to your code:

1. Directives:
    - a. #include
    - b. #define
    - c. #ifdef - #endif
2. Parametrized macros: A macro is like a function but at the preprocessing level. It is a substitution function that has parameters to provide different situations or values to the substitutions.
3. Operator backslash “\”
4. Eliminate comments and replace each of them by a space (empty lines are not eliminated)

The application can be run with the following flags:

1. -c : It eliminates comments (default)
2. -d : It replaces all directives starting with #
3. -all : It does all processing implemented
4. -help : It prints the "man page" of the preprocessor

## Installation
To install the application, navigate to the directory where the files are located and run the command `make`. This will compile the source code and create the executable.

To clean the object files and the executable generated during the compilation, run the command `make clean`.

## Usage
To use the application, navigate to the directory where the files are located and run the command `./prepreprocesor [flags] [filename]`. Replace "[flags]" with any of the available flags mentioned above and "[filename]" with the name of the file you want to process.

For example, to process a file called "file.c" and eliminate comments, you would run the command `./prepreprocesor -c file.c`.

If you need more information or help, you can use the flag `-help` to get the man page of the preprocessor.