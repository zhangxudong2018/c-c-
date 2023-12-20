/*
 * @Descripttion: 
 * @Author: zhangxudong
 * @version: 
 * @Date: 2023-12-19 17:35:47
 * @LastEditTime: 2023-12-20 15:01:38
 */
/**
 * @file main.c
 * @author your name (you@domain.com)
 * @brief 平衡二叉树
 * @version 0.1
 * @date 2023-12-19
 * 
 * @copyright Copyright (c) 2023
 * 
 */

/*

平衡二叉树：左右子树高度差不超过1

构建一颗平衡二叉树：
1.本质上跟构建二叉排序树一致
2.在构建二叉排序树的过程中，如果发现树不符合特性，需要进行调整

如何判断调整类型：
1.找到平衡树的根节点root
2.找到导致树失衡的节点node，node在root的哪一侧
3.判断node在root孩子的哪一侧

例：1 2 3 4 5

1                       2                       2
 \                     / \                     / \
  2           ->      1   3           ->      1   4
   \                       \                     / \
    3                       4                   3   5
                             \
                              5

RR:取中间的节点，使它的父亲成为它的左孩子，如果它有左孩子的话，那么这个左孩子连接到父亲的右孩子上    

例：5 4 3 2 1

      5                   4                    4               4
     /                   / \                  / \             / \
    4         ->        3   5      ->        3   5    ->     2   5 
   /                                        /               / \
  3                                        2               1   3
                                          /
                                         1 

LL:取中间节点，将它父亲作为自己的右孩子，如果自己有右孩子的话，那么将自己的右孩子，连接到父亲的左孩子上

例：8 7 9 5 6

       8                            8
      / \                          / \
     7   9                        6   9
    /                ->          / \
   5                            5   7
    \
     6

LR:取最后一个节点，作为父节点，将它的父亲作为自己的左孩子，将它的父亲的父亲作为自己的右孩子，如果它有左孩子或右孩子的话，它原先的左孩子，连接到父亲的右孩子上，它现在的右孩子，连接到父亲的父亲的左孩子上

例：1 8 6 7 10

        1                         6                        6
         \                       / \                      / \
          8          ->         1   8          ->        1   8
         /                                                  / \
        6                                                  7   10

RL:取最后一个节点，作为父亲节点，将它原先的父亲作为自己的右孩子，将父亲的父亲作为自己的左孩子，如果自己有左孩子或右孩子的话，自己原先的左孩子连接到父亲的父亲右孩子上，自己原先的右孩子连接到父亲的左孩子上

*/

#include <stdlib.h>
#include <stdio.h>

typedef struct TreeNode {
    int data;
    int height;
    struct TreeNode* lchild;
    struct TreeNode* rchild;
} TreeNode;

int getHeight(TreeNode* t) {
    return t ? t->height : 0;
}

int max(int a, int b) {
    return a > b ? a : b;
}

void llRotation(TreeNode* node, TreeNode** root) {
    TreeNode* tmp = node->lchild;
    node->lchild = tmp->rchild;
    tmp->rchild = node;
    node->height = max(getHeight(node->lchild), getHeight(node->rchild)) + 1;
    tmp->height = max(getHeight(tmp->lchild), getHeight(tmp->rchild)) + 1;
    *root = tmp;
}

void rrRotation(TreeNode* node, TreeNode** root) {
    TreeNode* tmp = node->rchild;
    node->rchild = tmp->lchild;
    tmp->lchild = node;
    node->height = max(getHeight(node->lchild), getHeight(node->rchild)) + 1;
    tmp->height = max(getHeight(tmp->lchild), getHeight(tmp->rchild)) + 1;
    *root = tmp;
}

void avlInsert(TreeNode** t, int data) {
    if (*t == NULL) {
        *t = (TreeNode*)malloc(sizeof(TreeNode));
        (*t)->data = data;
        (*t)->height = 0;
        (*t)->lchild = NULL;
        (*t)->rchild = NULL;
    } else if (data == (*t)->data) {
        return;
    } else if (data < (*t)->data) {
        avlInsert(&(*t)->lchild, data);
        // 拿到当前节点左右子树的高度
        int lHeight = getHeight((*t) ->lchild);
        int rHeight = getHeight((*t) ->rchild);
        // 判断高度差
        if (lHeight - rHeight == 2) {
            if (data < (*t)->lchild->data) {
                // LL调整
                llRotation(*t, t);
            } else  {
                // LR调整
                rrRotation((*t)->lchild, &(*t)->lchild);
                llRotation(*t, t);
            }
        }
        
    } else if (data > (*t)->data) {
        avlInsert(&(*t)->rchild, data);
        int lHeight = getHeight((*t) ->lchild);
        int rHeight = getHeight((*t) ->rchild);
        if (rHeight - lHeight == 2) {
            if (data > (*t)->rchild->data) {
                // RR调整
                rrRotation(*t, t);
            } else  {
                // RL调整
                llRotation((*t)->rchild, &(*t)->rchild);
                rrRotation(*t, t);
            }
        }
    }
    (*t)->height = max(getHeight((*t)->lchild), getHeight((*t)->rchild)) + 1;
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
    TreeNode* rrt = NULL;
    TreeNode* llt = NULL;
    TreeNode* lrt = NULL;
    TreeNode* rlt = NULL;
    int nums1[5] = {1,2,3,4,5};
    int nums2[5] = {5,4,3,2,1};
    int nums3[5] = {8,7,9,5,6};
    int nums4[5] = {1,8,6,7,10};
    for (int i = 0; i < 5; i++) {
        avlInsert(&rrt, nums1[i]);
    }
    printf("rr调整\n");
    printOrder(rrt);
    printf("\n");
    for (int i = 0; i < 5; i++) {
        avlInsert(&llt, nums2[i]);
    }
    printf("ll调整\n");
    printOrder(llt);
    printf("\n");
    for (int i = 0; i < 5; i++) {
        avlInsert(&lrt, nums3[i]);
    }
    printf("lr调整\n");
    printOrder(lrt);
    printf("\n");
    for (int i = 0; i < 5; i++) {
        avlInsert(&rlt, nums4[i]);
    }
    printf("rl调整\n");
    printOrder(rlt);
    printf("\n");
    return 0;
}