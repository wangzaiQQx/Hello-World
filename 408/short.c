#include <stdio.h>
#include <limits.h>

int main(int argc, char const *argv[])
{
    short a = 100, b = 200;
    unsigned short c = 100;
    printf("a -b = %d\n", a - b);
    c -= 200;
    printf("c = %hu\n", c);
    printf("Short Minimum Value = %d\n", SHRT_MIN);
    printf("Short Maximum Value = %d\n", SHRT_MAX);
    printf("Unsigned Short Maximum Value = %u\n", USHRT_MAX);
    return 0;
}