#include <stdio.h>

int main()
{
    int num;
    printf("请输入一个3位数：");
    scanf("%d", &num);
    printf("个位数值为%d\n十位数值为%d\n百位数值为%d\n", num % 10, num / 10 % 10, num / 100);
    return 0;
}