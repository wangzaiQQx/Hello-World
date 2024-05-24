#include <stdio.h>
#include <string.h> // 引入字符串操作相关的头文件

int main()
{
    char name[50]; // 定义一个字符数组来存储名字，假设名字最长不超过49个字符
    int age;
    float height;
    
    printf("Enter your name, age, and height: ");
    // 使用%s来读取字符串，同时需要指定数组的地址
    scanf("%s %d %f", name, &age, &height);
    
    // 使用strlen获取名字的实际长度，确保输出正确
    printf("Name: %s, Age: %d, Height: %.2f meters\n", name, age, height);
    
    return 0;
}