/*
 * Compilers
 * Practice 1: c pre-processor
 * Example file containing only if directives. It works with or without parenthesis and
 * with any numbers of space characters between the if and the condition.
 * Variables can be integer, long and even character, like with the fourth directive
 */

#include <stdio.h>

int main(int argc, char **argv)
{
#if (1 == 1)
    printf("This message is printed");
#endif

#if 1 == 1
    printf("This message is printed");
#endif

#if (1 == 1)
    printf("This message is printed");
#endif

#if 'a' == 'a'
    printf("This message is printed");
#endif

#if (0 == 1)
    printf("This message is not printed");
#endif

    return 0;
}