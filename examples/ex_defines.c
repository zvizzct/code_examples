/*
 * Compilers
 * Practice 1: c pre-processor
 * Example file containing only define directive
 */

#define A 1
#define B 3
#define C 5
#define D 10

int main(int argc, char **argv)
{
    int sum = A + B;
    int sub = A - B;
    int mult = C * D;
    int div = C / D;
    return 0;
}