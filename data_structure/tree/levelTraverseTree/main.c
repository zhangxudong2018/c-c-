/*
 * @Descripttion:  层次遍历二叉树
 * @Author: zhangxudong
 * @version: 
 * @Date: 2023-12-08 21:51:01
 * @LastEditTime: 2023-12-08 22:28:21
 */

#include <stdlib.h>
#include <stdio.h>

typedef struct TreeNode {
    char data;
    struct TreeNode* lchild;
    struct TreeNode* rchild;
} TreeNode;

typedef struct QueueNode {
    TreeNode* data;
    struct QueueNode* pre;
    struct QueueNode* next;
} QueueNode;

void createTree(TreeNode** t, char* data, int* index) {
    char ch;
    ch = data[*index];
    *index += 1;
    if (ch == '#') {
        // 此时为空节点
        *t = NULL;
    } else {
        *t = (TreeNode*)malloc(sizeof(TreeNode));
        (*t)->data = ch;
        createTree(&((*t)->lchild), data, index);
        createTree(&((*t)->rchild), data, index);
    }
}

QueueNode* initQueue() {
    QueueNode* q = (QueueNode*)malloc(sizeof(QueueNode));
    q->data = NULL;
    q->pre = q;
    q->next = q;
    return q;
}

void enQueue(TreeNode* data, QueueNode* q) {
    QueueNode* node = (QueueNode*)malloc(sizeof(QueueNode));
    node->data = data;
    node->pre = q;
    node->next = q;
    q->pre->next = node;
    q->pre = node;
}

int isEmpty(QueueNode* q) {
    if (q->next == q) {
        return 1;
    } else {
        return 0;
    }
}

QueueNode* deQueue(QueueNode* q) {
    if (isEmpty(q)) {
        return NULL;
    } else {
        QueueNode* node = q->next;
        q->next->next->pre = q;
        q->next = q->next->next;
        return node;
    }
}

void levelTraverse(QueueNode* q, TreeNode* t) {
    enQueue(t, q);
    while(!isEmpty(q)) {
        QueueNode* node = deQueue(q);
        printf("%c ", node->data->data);
        if (node->data->lchild) {
            enQueue(node->data->lchild, q);
        }
        if (node->data->rchild) {
            enQueue(node->data->rchild, q);
        }
    }
}

// abd##e##cf##g## 

int main(int argc, char* argv[])
{
    TreeNode* t;
    int index = 0;
    QueueNode* q = initQueue();
    createTree(&t, argv[1], &index);
    levelTraverse(q, t);
    printf("\n");
    return 0;
}