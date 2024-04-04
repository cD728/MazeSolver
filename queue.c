// Duarte nao te esqueces q esta queue e uma valente merda existe queues q sao O(1) nas partes importantes em vez desta merda
#include "queue.h"

int isEmptyQueue(Queue* queue) {
    if (queue == NULL) return 1;
    return 0;
}

Queue* createQueue(Cell* cell, double priority) {
    Queue* queue = (Queue*) malloc(sizeof(Queue));
    queue->priority = priority;
    queue->cell = cell;
    queue->next = NULL;

    return queue;
}

double find(Queue* queue, Cell* cell) {
    Queue* node = queue; 
    while (node != NULL) {
        if (node->cell == cell) return node->priority;
        node = node->next;
    }
    
    return -1;
}

void insert(Queue** queue, Cell* cell, double priority) {
    Queue* prev = NULL;
    Queue* current = *queue;

    while (current != NULL) {
        if (priority < current->priority) break;

        prev = current;
        current = current->next;
    }
    
    Queue* node = (Queue*) malloc(sizeof(Queue));
    node->cell = cell;
    node->priority = priority;
    node->next = current;
    if (prev != NULL) {
        prev->next = node;
    } else {
        *queue = node;
    }
} 

Cell* removeFirst(Queue** queue) {
    Queue* node = *queue;
    Cell* cell = node->cell;
    *queue = node->next;
    free(node);

    return cell;
}

void removeCell(Queue** queue, Cell* cell) {
    Queue* prev = NULL;
    Queue* current = *queue;

    while (current != NULL) {
        if (cell == current->cell) {
            if (prev != NULL) {
                prev->next = current->next;
            } else {
                *queue = current->next;
            }

            free(current);
        }

        prev = current;
        current = current->next;
    }
}

void freeQueue(Queue** queue) {
    Queue* node = *queue;

    while (node != NULL) {
        Queue* temp = node;
        node = node->next;
        free(temp);
    }
    
    *queue = NULL;
}