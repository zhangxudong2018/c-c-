/*
 * @Descripttion: 
 * @Author: zhangxudong
 * @version: 
 * @Date: 2023-12-19 16:53:59
 * @LastEditTime: 2023-12-19 17:21:14
 */
/**
 * @file main.c
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2023-12-19
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include <stdlib.h>
#include <stdio.h>

typedef struct TreeNode {
    int data;
    struct TreeNode* lchild;
    struct TreeNode* rchild;
} TreeNode;

TreeNode* bstSearch(TreeNode* t, int key) {
    if (t) {
        if (key == t->data) {
            return t;
        } else if (key < t->data) {
            return bstSearch(t->lchild, key);
        } else {
            return bstSearch(t->rchild, key);
        }
    } else {
        return NULL;
    }
}

void bstInsert(TreeNode** t, int data) {
    if (*t == NULL) {
        *t = (TreeNode*)malloc(sizeof(TreeNode));
        (*t)->data = data;
        (*t)->lchild = NULL;
        (*t)->rchild = NULL;
    } else if (data == (*t)->data) {
        return;
    } else if (data < (*t)->data) {
        bstInsert(&((*t)->lchild), data);
    } else {
        bstInsert(&((*t)->rchild), data);
    }
}

void printOrder(TreeNode* t) {
    if (t) {
        printf("%d ->", t->data);
        printOrder(t->lchild);
        printOrder(t->rchild);
    }
}

int main()
{
    TreeNode* t = NULL;
    int nums[6] = {4,5,19,26,2,8};
    for (int i = 0; i < 6; i++) {
        bstInsert(&t, nums[i]);
    }
    printOrder(t);
    printf("\n");
    TreeNode* s = bstSearch(t, 8);
    printf ("%d \n", s->data);
    return 0;
}