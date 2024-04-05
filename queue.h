#ifndef QUEUE_H_
#define QUEUE_H_
#include <stdlib.h>
#include "cell.h"

typedef struct queue {
   int priority;
   Cell* cell;
} Queue;

Queue* createQueue(Cell* cell, int priority, int* size);
void insert(Queue** queue, Cell* cell, int priority, int* size);
int find(Queue* queue, Cell* cell, int size);
Cell* removeFirst(Queue** queue, int* size);
void removeCell(Queue** queue, Cell* cell, int* size);
void freeQueue(Queue* queue);

#endif