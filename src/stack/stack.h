#ifndef STACK_H_
#define STACK_H_
#include "../cell/cell.h"

typedef struct {
  Cell* cell;
  struct Stack* prev;
} Stack;

int isEmptyStack(Stack* node);
Stack* createStack(Cell* cell);
void push(Stack** stack, Cell* cell);
Cell* pop(Stack** stack);

#endif // STACK_H_
