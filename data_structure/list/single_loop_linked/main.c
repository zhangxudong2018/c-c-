/*
 * @Descripttion: 
 * @Author: zhangxudong
 * @version: 
 * @Date: 2023-11-30 17:22:06
 * @LastEditTime: 2023-11-30 18:01:15
 */

#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0

typedef struct Node {
    int data;
    struct Node* next;
} Node;

Node* initList() {
    Node* list = (Node*)malloc(sizeof(Node));
    list->data = 0;
    list->next = list;
    return list;
}

void headInsert(Node* list, int data) {
    Node* node = (Node*)malloc(sizeof(Node));
    node->data = data;
    node->next = list->next;
    list->next = node;
    list->data++;
}

void tailInsert(Node* list, int data) {
    Node* n = list;
    Node* node = (Node*)malloc(sizeof(Node));
    node->data = data;
    while (n->next != list) {
        n = n->next;
    }
    node->next = list;
    n->next = node;
    list->data++;
}

int delete(Node* list, int data) {
    Node* preNode = list;
    Node* node = list->next;
    while (node != list) {
        if (node->data == data) {
            preNode->next = node->next;
            free(node);
            list->data--;
            return TRUE;
        }
        preNode = node;
        node = node->next;
    }
    return FALSE;
}

void printList(Node* list) {
    printf("head=%p\tdata=%d\n", list, list->data);
    Node* node = list->next;
    while (node != list) {
        printf("data = %d\taddress=%p\tnext=%p\n", node->data, node, node->next);
        node = node->next;
    }
    printf("\n");
}

int main() {
    Node* list = initList();
    headInsert(list, 1);
    headInsert(list, 2);
    headInsert(list, 3);
    headInsert(list, 4);
    headInsert(list, 5);
    tailInsert(list, 6);
    tailInsert(list, 7);
    tailInsert(list, 8);
    tailInsert(list, 9);
    tailInsert(list, 10);
    printList(list);
    delete(list, 6);
    delete(list, 10);
    delete(list, 5);
    printList(list);
    return 0;
}