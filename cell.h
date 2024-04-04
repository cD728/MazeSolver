#ifndef CELL_H_
#define CELL_H_

#include <stdint.h>
#include <raylib.h>

typedef enum {
    EMPTY, 
    START, 
    PATH, 
    END,
    CURRENT,
    VISITED,
    BESTPATH
} STATE;

typedef struct cell {
  STATE state;       // status of the cell.
  int x,y;           // positions of cell.
  uint8_t neighbors; // the first 4 bits are the neighbors.
                     // the last 4 bits are the walls of the cell.
  int visited;       // to check if visited.
  int distance;
  struct cell* prev;
} Cell;

void DrawCellWalls(int x, int y, int side, Cell* cell, int lineThick, Color color);

#endif // CELL_H_
