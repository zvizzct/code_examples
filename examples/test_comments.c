/*
 * Compilers
 * Practice 1: c pre-processor
 * Example file containing only comments
 */

// #include "./comp-p1.h"
// #define A 5
int main(int argc, char **argv)
{
    // blaaaablaa
    // blaaaba
    // blaaaba
    int i;

    /* blablaaaaaa
    blabaaa
    baaaaa */
    i += 3;
    /* blaaaaaaaa
    blaaaaaaaaabla
    blaaa
    baa
    blaa */
/* #if (PRINTWARNING == ON)
        WARNING(i, (errfile, "warning print example %s \n", argv[i]));
#endif */
    i +=3;
/* #if (PRINTERROR == ON)
    ERROR(i, (errfile, "This is an error, and it stops"));
#endif */

    return 0;
}
