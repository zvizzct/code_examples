/*
 * Compilers
 * Practice 1: c pre-processor
 * Example file containing only Parametrized Macros directives
 */

#define SUM(x, y) ((x) + (y))
#define PRODUCT(x, y) ((x) * (y))
#define SUBSTRACTION(x, y) ((x) \
                            - (y))
#define DIVISION(x, y) ((x) \
                            / (y))

int main(int argc, char **argv)
{
    int sum = SUM(9, 5);
    int sub = SUBSTRACTION(8, 4);
    int mult = PRODUCT(3, 4);
    int div =DIVISION(8, 4);
    return 0;
}
