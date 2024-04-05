// Duarte nao te esqueces q esta queue e uma valente merda existe queues q sao O(1) nas partes importantes em vez desta merda
#include "queue.h"

int isEmptyQueue(Queue* queue) {
    if (queue == NULL) return 1;
    return 0;
}

Queue* createQueue(Cell* cell, int priority, int *size) {
    Queue* queue = (Queue*) malloc(sizeof(Queue));
    queue->priority = priority;
    queue->cell = cell;
    *size = 1;

    return queue;
}

void minHeapify(Queue* queue, int size, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = left + 1;

    if (left < size && queue[left].priority < queue[largest].priority)
        largest = left;

    if (right < size && queue[right].priority < queue[largest].priority)
        largest = right;

    if (largest != i) {
        Queue temp = queue[i];
        queue[i] = queue[largest];
        queue[largest] = temp;

        minHeapify(queue, size, largest);
    }
}

void reverseMinHeapify(Queue* queue, int i) {
    int parent = (i - 1) / 2;
    if (parent >= 0) {
        if (queue[i].priority < queue[parent].priority) {
            Queue temp = queue[i];
            queue[i] = queue[parent];
            queue[parent] = temp;
            
            reverseMinHeapify(queue, parent);
        }
    }
}

int find(Queue* queue, Cell* cell, int size) {
    for (int i = 0; i < size; i++) {
        if (queue[i].cell->x == cell->x && queue[i].cell->y == cell->y)
            return queue[i].priority;
    }

    return -1;
}

void insert(Queue** queue, Cell* cell, int priority, int* size) {
    *queue = realloc(*queue, (++(*size))*sizeof(Queue));

    int i = *size - 1;
    (*queue)[i] = (Queue) {priority, cell};
    if (i != 0)
        reverseMinHeapify(*queue, i);
}

Cell* removeFirst(Queue** queue, int* size) {
    Queue node = (*queue)[0];

    (*queue)[0] = (*queue)[*size - 1];

    *queue = realloc(*queue, (--(*size))*sizeof(Queue));

    minHeapify(*queue, *size, 0);

    return node.cell;
}

void removeCell(Queue** queue, Cell* cell, int* size) {
    for (int i = 0; i < *size; i++) {
        if ((*queue)[i].cell->x == cell->x && (*queue)[i].cell->y == cell->y) {
            (*queue)[i] = (*queue)[*size - 1];

            *queue = realloc(*queue, (--(*size))*sizeof(Queue));

            minHeapify(*queue, *size, i);
            break;
        }
    }
}

void freeQueue(Queue* queue) {
    free(queue);
}