#include <stdio.h>
#include <limits.h>

int main(int argc, const char *argv[])
{
    int a = 10;
    unsigned int b = +100U;
    unsigned c = -1U;
    printf("a + b = %d\n", a + b);
    printf("c = 0x%X\n", c);
    printf("a + c = %d\n", a + c);
    a++;
    printf("a = %d\n", a);
    printf("INT_MIN=%d\n", INT_MIN);
    printf("INT_MAX=%d\n", INT_MAX);
    printf("UINT_MAX=%u\n", UINT_MAX);
}
