#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 10 // 线性表的最大容量

typedef struct {
    int data[MAX_SIZE]; // 存储线性表元素的数组
    int length;        // 当前线性表的长度
} LinearList;

// 初始化线性表
void initLinearList(LinearList *list) {
    list->length = 0;
}

// 判断线性表是否为空
int isEmpty(LinearList *list) {
    return list->length == 0;
}

// 向线性表末尾插入元素
void insertEnd(LinearList *list, int val) {
    if (list->length >= MAX_SIZE) {
        printf("线性表已满，无法插入新元素。\n");
        return;
    }
    list->data[list->length] = val;
    list->length++;
}

// 删除线性表中的某个元素（这里简化处理，仅删除第一个匹配到的值）
int deleteElement(LinearList *list, int val) {
    int i;
    for (i = 0; i < list->length; i++) {
        if (list->data[i] == val) {
            // 将后面的元素前移
            while (i < list->length - 1) {
                list->data[i] = list->data[i + 1];
                i++;
            }
            list->data[i] = 0; // 或者可以不置零，取决于你的需求
            list->length--;
            return 1; // 表示删除成功
        }
    }
    return 0; // 表示未找到该元素，删除失败
}

// 打印线性表
void printList(LinearList *list) {
    printf("当前线性表内容：");
    for (int i = 0; i < list->length; i++) {
        printf("%d ", list->data[i]);
    }
    printf("\n");
}

int main() {
    LinearList myList;
    initLinearList(&myList);

    insertEnd(&myList, 1);
    insertEnd(&myList, 2);
    insertEnd(&myList, 3);
    printList(&myList);

    if (deleteElement(&myList, 2)) {
        printf("元素2已删除。\n");
    } else {
        printf("元素2不在线性表中。\n");
    }

    printList(&myList);

    return 0;
}