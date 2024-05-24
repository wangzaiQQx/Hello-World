#include <stdio.h>
#include <math.h>

int main(int argc, char const *argv[]){
    int len=printf("你好\n");
    printf("长度为%d\n",len);
    printf("输出字符是：%c, 输出浮点数是：%f\n",'A',M_PI);
    printf("1000的十六进制数为：0x%X\n",1000);
    const char *s="hello, world!";
    printf("打印：%s\n",s);
}
