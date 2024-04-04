#ifndef QUEUE_H_
#define QUEUE_H_
#include <stdlib.h>
#include "cell.h"

typedef struct queue {
   double priority;
   Cell* cell;
   struct queue* next;
} Queue;

Queue* createQueue(Cell* cell, double priority);
int isEmptyQueue(Queue* queue);
void insert(Queue** queue, Cell* cell, double priority);
double find(Queue* queue, Cell* cell);
Cell* removeFirst(Queue** queue);
void removeCell(Queue** queue, Cell* cell);
void freeQueue(Queue** queue);

#endif