/*
 * @Descripttion: 
 * @Author: zhangxudong
 * @version: 
 * @Date: 2023-12-20 15:32:14
 * @LastEditTime: 2023-12-20 16:16:44
 */
/**
 * @file main.c
 * @author your name (you@domain.com)
 * @brief 哈夫曼树
 * @version 0.1
 * @date 2023-12-20
 * 
 * @copyright Copyright (c) 2023
 * 
 */

/*

哈夫曼树：所有叶子结点的带权路径长度最小

如何通过权值，节点列表生成哈夫曼树

1.从节点列表中选出第一和第二小的节点，并组成一棵树，父亲节点的权值=两节点权值之和
2.将生成的新树再次放入节点列表中，重复第一步，直到列表中只剩下一个节点

例：a:1 b:2 c:3 d:4

                                                         O(10)
         O                                                / \
        / \                         O                  d(4) O(6)
       a   b          ->           / \            ->        / \
                                  O   c                   0(3) c(3)
                                 / \                      / \
                                a   b                   a(1) b(2)  
    权值=3*1+3*2+2*3+1*4=19 最小

*/

#include <stdlib.h>
#include <stdio.h>

typedef struct TreeNode {
    int weight;
    int parent;
    int lchild;
    int rchild;
} TreeNode;

typedef struct HFTree {
    TreeNode* data;
    int length;
} HFTree;

HFTree* initTree(int* weight, int length) {
    HFTree* t = (HFTree*)malloc(sizeof(HFTree));
    t->data = (TreeNode*)malloc(sizeof(TreeNode)* (2 * length - 1));
    t->length = length;
    for (int i = 0; i < length; i++) {
        t->data[i].weight = weight[i];
        t->data[i].parent = 0;
        t->data[i].lchild = -1;
        t->data[i].rchild = -1;
    }
    return t;
}

int* selectMin(HFTree* t) {
    int min = 10000;
    int secondMin = 10000;
    int minIndex;
    int secondMinIndex;
    for (int i = 0; i < t->length; i++) {
        if (t->data[i].parent == 0) {
            if (t->data[i].weight < min) {
                min = t->data[i].weight;
                minIndex = i;
            }
        }
    }
    for (int i = 0; i < t->length; i++) {
        if (t->data[i].parent == 0 && i != minIndex) {
            if (t->data[i].weight < secondMin) {
                secondMin = t->data[i].weight;
                secondMinIndex = i;
            }
        }
    }
    int* res = (int*)malloc(sizeof(int) * 2);
    res[0] = minIndex;
    res[1] = secondMinIndex;
    return res;
}

void createHFTree(HFTree* t) {
    int* res;
    int min;
    int secondMin;
    int length = t->length * 2 -1;
    for (int i = t->length; i < length; i++) {
        res = selectMin(t);
        min = res[0];
        secondMin = res[1];
        t->data[i].weight = t->data[min].weight + t->data[secondMin].weight;
        t->data[i].lchild = min;
        t->data[i].rchild = secondMin;
        t->data[min].parent = i;
        t->data[secondMin].parent = i;
        t->length++;
    }
}

void preOrder(HFTree* t, int index) {
    if (index != -1) {
        printf("%d ->", t->data[index].weight);
        preOrder(t, t->data[index].lchild);
        preOrder(t, t->data[index].rchild);
    }
}

int main() {
    int weight[4] = {1,2,3,4};
    HFTree* t = initTree(weight, 4);
    int* res = selectMin(t);
    printf("res[0] = %d\tres[1]=%d\n", res[0], res[1]);
    createHFTree(t);
    preOrder(t, t->length - 1);
    return 0;
}

