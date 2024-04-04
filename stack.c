#include <stdlib.h>
#include "stack.h"

int isEmptyStack(Stack* node) {
  if (node == NULL)
    return 1;
  return 0;
}

Stack* createStack(Cell* cell) {
  Stack* node = (Stack*) malloc(sizeof(Stack));
  node->cell = cell;
  node->prev = NULL;

  return node;
}

void push(Stack** stack, Cell* cell) {
  Stack* node = (Stack*) malloc(sizeof(Stack));
  node->cell = cell;
  node->prev = (struct Stack*) *stack;
  *stack = node;
}

Cell* pop(Stack** stack) {
  Stack* node = *stack;
  Cell* cell = node->cell;

  if (node->prev != NULL) {
    *stack = (Stack*) node->prev;
  } else {
    *stack = NULL;
  }
  free(node);

  return cell;
}
