/*
 * @Descripttion: 字符串暴力匹配
 * @Author: zhangxudong
 * @version: 
 * @Date: 2023-12-06 09:23:20
 * @LastEditTime: 2023-12-06 09:50:13
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

void forceMatch(String* master, String* sub) {
    int i = 0;
    int j = 0; 
    while (i < master->len && j < sub->len) {
        if (master->data[i] == sub->data[j]) {
            i++;
            j++;
        } else {
            i = i - j + 1;
            j = 0;
        }
    }
    if (j == sub->len) {
        printf("force match success.\n");
    } else {
        printf("force match fail.\n");
    }
}

int main(int argc, char* argv[]) {
    String* s1 = initString();
    String* s2 = initString();
    stringAssign(s1, argv[1]);
    stringAssign(s2, argv[2]);
    printString(s1);
    printString(s2);
    forceMatch(s1, s2);
    return 0;
}