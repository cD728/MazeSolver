#ifndef ASTAR_H_
#define ASTAR_H_
#include "board.h"

typedef enum {
    ASTAR,
    DIJKSTRA
} PATHFINDERS;

int ManhattanDistance(Cell* cell0, Cell* cell1);
int Astar(Cell** board, Cell* start, Cell* end, int height, int width, int side, Color rectFill, int lineThick, Color rectOut, bool noDrawing);
int dijkstra(Cell** board, Cell* start, Cell* end, int height, int width, int side, Color rectFill, int lineThick, Color rectOut, bool noDrawing);

#endif