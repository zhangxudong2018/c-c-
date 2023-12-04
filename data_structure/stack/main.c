/*
 * @Descripttion: 
 * @Author: zhangxudong
 * @version: 
 * @Date: 2023-12-04 15:33:01
 * @LastEditTime: 2023-12-04 16:00:27
 */

#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;

Node* initStack() {
    Node* s = (Node*)malloc(sizeof(Node));
    s->data = 0;
    s->next = NULL;
    return s;
}

int isEmpty(Node* s) {
    if (s->data == 0 || s->next == NULL) {
        return 1;
    } else {
        return 0;
    }
}

int top(Node* s) {
    if (isEmpty(s)) {
        return -1;
    } else {
        return s->next->data;
    }
}

int pop(Node* s) {
    if (isEmpty(s)) {
        return -1;
    } else {
        Node* node = s->next;
        s->next = node->next;
        int data = node->data;
        free(node);
        s->data--;
        return data;
    }
}

void push(Node* s, int data) {
    Node* node = (Node*)malloc(sizeof(Node));
    node->data = data;
    node->next = s->next;
    s->next = node;
    s->data++;
}

void printStack(Node* s) {
    if (isEmpty(s)) {
        printf("stack is empty\n");
    }
    Node* node = s->next;
    while (node) {
        printf("data = %d\taddress=%p\tnext=%p\n", node->data, node, node->next);
        node = node->next;
    }
    printf("\n");
}

int main() 
{
    Node* s = initStack();
    push(s, 1);
    push(s, 2);
    push(s, 3);
    push(s, 4);
    push(s, 5);
    printStack(s);
    int p1 = pop(s);
    printf("top=%d\n", p1);
    pop(s);
    printStack(s);
    pop(s);
    pop(s);
    pop(s);
    printStack(s);
    return 0;
}