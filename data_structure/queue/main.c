/*
 * @Descripttion: 循环队列
 * @Author: zhangxudong
 * @version: 
 * @Date: 2023-12-04 16:11:22
 * @LastEditTime: 2023-12-04 16:39:11
 */

#include <stdlib.h>
#include <stdio.h>

#define MAXSIZE 5

typedef struct Queue {
    int front;
    int rear;
    int data[MAXSIZE];
} Queue;

Queue* initQueue() {
    Queue* q = (Queue*)malloc(sizeof(Queue));
    q->front = q->rear = 0;
    return q;
}

int isFull(Queue* q) {
    if ((q->rear + 1) % MAXSIZE == q->front) {
        printf("queue is full\n");
        return 1;
    } else {
        return 0;
    }
}

int isEmpty(Queue* q) {
    if (q->front == q->rear) {
        printf("queue is empty\n");
        return 1;
    } else {
        return 0;
    }
}

int enQueue(Queue* q, int data) {
    if (isFull(q)) {
        return 0;
    } else {
        q->data[q->rear] = data;
        q->rear = (q->rear + 1) % MAXSIZE;
        return 1;
    }
}

int deQueue(Queue* q) {
    if (isEmpty(q)) {
        return -1;
    } else {
        int data = q->data[q->front];
        q->front = (q->front + 1) % MAXSIZE;
        return data;
    }
}

void printQueue(Queue* q) {
    int length = (q->rear - q->front + MAXSIZE) % MAXSIZE;
    int index = q->front;
    for (int i = 0; i < length; i++) {
        printf("data = %d\n", q->data[index]);
        index = (index + 1) % MAXSIZE; 
    }
    printf("\n");
}

int main()
{
    Queue* q = initQueue();
    enQueue(q, 1);
    enQueue(q, 2);
    enQueue(q, 3);
    enQueue(q, 4);
    enQueue(q, 5);
    printQueue(q);
    deQueue(q);
    deQueue(q);
    printQueue(q);
    enQueue(q, 6);
    enQueue(q, 7);
    printQueue(q);
    return 0;
}