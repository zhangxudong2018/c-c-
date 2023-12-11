/*
 * @Descripttion: 
 * @Author: zhangxudong
 * @version: 
 * @Date: 2023-12-06 11:13:39
 * @LastEditTime: 2023-12-06 11:40:04
 */


#include <stdio.h>
#include <stdlib.h>

typedef struct String {
    char* data;
    int len;
} String;

String* initString() {
    String* s = (String*)malloc(sizeof(String));
    s->data = NULL;
    s->len = 0;
    return s;
}

void stringAssign(String* s, char* data) {
    if (s->data) {
        free(s->data);
    }
    int len = 0;
    char* temp = data;
    while (*temp) {
        len++;
        temp++;
    }
    if (len == 0) {
        s->data = NULL;
        s->len = 0;
    } else {
        temp = data;
        s->len = len;
        // c语言字符串\0结尾，开辟空间字符串长度+1
        s->data = (char*)malloc(sizeof(char) * (len + 1));
        for (int i = 0; i < len; i++, temp++) {
            s->data[i] = *temp;
        }
    }
}

void printString(String* s) {
    for (int i = 0; i < s->len; i++) {
        printf("%c", s->data[i]);
    }
    printf("\n");
}

int* getNext(String* s) {
    int* next = (int*)malloc(sizeof(int) * s->len);
    int i = 0;  // next 索引
    int j = -1; // next value
    next[i] = j;
    while (i < s->len - 1) {
        if (j == -1 || s->data[i] == s->data[j]) {
            i++;
            j++;
            next[i] = j;
        } else {
            j = next[j];
        }
    }
    return next;
}

void kmpMatch(String* master, String* sub, int* next) {
    int i = 0;
    int j = 0;
    while (i < master->len && j < sub->len) {
        if (j == -1 || master->data[i] == sub->data[j]) {
            i++;
            j++;
        } else {
            j = next[j];
        }
    }
    if (j == sub->len) {
        printf("kmp match success.\n");
    } else {
        printf("kmp match fail.\n");
    }
}

void printNext(int* next, int len) {
    printf("next value\n");
    for (int i = 0; i < len; i++) {
        printf("%d", next[i] + 1);
    }
    printf("\n");
}

// ABACCABABD

int main(int argc, char* argv[]) {
    String* s1 = initString();
    String* s2 = initString();
    stringAssign(s1, argv[1]);
    stringAssign(s2, argv[2]);
    printString(s1);
    printString(s2);
    int* next = getNext(s2);
    printNext(next, s2->len);
    kmpMatch(s1, s2, next);
    return 0;
}