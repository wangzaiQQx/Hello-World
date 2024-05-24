#include <stdio.h>

int main() {
    int a, b;
    printf("a  b   &  |  ^  !a  !b\n"); 
    printf("--------------------------------\n"); 
    for (a = 0; a <= 1; a++) {
        for (b = 0; b <= 1; b++) {
            // 仅展示按位取反在布尔上下文中的等效意义
            int notA = !a;
            int notB = !b;
            printf("%d  %d   %d  %d  %d   %d   %d\n", a, b, a & b, a | b, a ^ b, notA, notB);
        }
    }
    
    return 0;
}