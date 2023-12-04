/*
 * @Descripttion: 
 * @Author: zhangxudong
 * @version: 
 * @Date: 2023-11-30 18:24:26
 * @LastEditTime: 2023-12-04 14:56:49
 */

#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0

typedef struct Node {
    int data;
    struct Node* pre;
    struct Node* next;
} Node;

Node* initList() {
    Node* list = (Node*)malloc(sizeof(Node));
    list->data = 0;
    list->pre = NULL;
    list->next = NULL;
    return list;
}

void headInsert(Node* list, int data) {
    Node* node = (Node*)malloc(sizeof(Node));
    node->data = data;
    if (list->data == 0) {
        // 链表为空
        node->next = list->next;
        node->pre = list;
        list->next = node;
    } else {
        node->pre = list;
        node->next = list->next;
        list->next->pre = node;
        list->next = node;
    }
    list->data++;
}

void tailInsert(Node* list, int data) {
    Node* node = list;
    Node* n = (Node*)malloc(sizeof(Node));
    n->data = data;
    while (node->next) {
        node = node->next;
    }
    n->next = node->next;
    node->next = n;
    n->pre = node;
    list->data++;
}

int delete(Node* list, int data) {
    Node* node = list->next;
    while (node) {
        if (node->data == data) {
            if (node->next == NULL) {
                node->pre->next = NULL;
                free(node);
                list->data--;
                return TRUE;
            } else {
                node->pre->next = node->next;
                node->next->pre = node->pre;
                free(node);
                list->data--;
                return TRUE;
            }
            
        }
        node = node->next;
    }
    return FALSE;
}

void printList(Node* list) {
    printf("head=%p\tdata=%d\n", list, list->data);
    Node* node = list->next;
    while (node) {
        printf("data = %d\taddress=%p\tnext=%p\tpre=%p\n", node->data, node, node->next, node->pre);
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