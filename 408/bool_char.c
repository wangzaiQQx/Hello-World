#include <stdio.h>
#include <stdbool.h>
#include <limits.h>

int main(int argc, char const *argv[])
{
    bool a = true;
    bool b = false;
    bool c = a == b;
    printf("a = %d\n", a);
    printf("b = %d\n", b);
    printf("c = %d\n", c);
    printf("\', \", \?, \\, \123, \x30\n");
}