// double
// float
// long long
// long
// int
// short
// char

#include <stdio.h>

int main() {
    double x = 1.0;
    float y = 1.0f; // 添加f后缀指定为float类型
    long long z = 1LL; // 添加LL后缀指定为long long类型
    long w = 1L; // 添加L后缀指定为long类型
    int v = 1; // 整型可以直接赋值，不需要后缀
    short u = 1; // 同上，对于short类型，直接赋值即可，但需留意整型提升的问题
    char t = 1; // 字符型也可以直接赋值，但注意其范围通常是-128到127
    char str[10] = "Hello";
    int i = (int)x;

    printf("double: %f\n", x);
    printf("float: %f\n", y); // 注意：虽然可以这样打印，但最好使用%f并强制类型转换
    printf("long long: %lld\n", z); // 使用正确的格式化说明符
    printf("long: %ld\n", w);
    printf("int: %d\n", v);
    printf("short: %hd\n", u); // 使用'h'前缀指定short类型
    printf("char: %d\n", t); // 字符型通常以%d格式打印以显示ASCII码值
    printf("char: %s\n", str);
    printf("int: %d\n", i);

    return 0;
}
