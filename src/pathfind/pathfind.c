#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <raylib.h>
#include "../pathfind/pathfind.h"
#include "../queue/queue.h"
#include "../cell/cell.h"

int manhattanDistance(Cell* cell0, Cell* cell1) {
  return abs(cell0->x - cell1->x) + abs(cell0->y - cell1->y);
}

double absoluteDistance(Cell* cell0, Cell* cell1) {
    double x = cell0->x - cell1->x;
    double y = cell0->y - cell1->y;
    return sqrt(x*x + y*y);
}

int Astar(Cell** board, Cell* start, Cell* end, int height, int width, int side, Color rectFill, int lineThick, Color rectOut, bool noDrawing) {
    int size;
    Queue* openCells = createQueue(start, 0, &size);
    bool closedCells[height][width];

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            closedCells[i][j] = false;
        }
    }

    closedCells[0][0] = true;    

    while (size > 0) {
        if (WindowShouldClose() || (IsKeyDown(KEY_LEFT_CONTROL) && IsKeyDown(KEY_LEFT_SHIFT) && IsKeyDown(KEY_ESCAPE))) return 1;
        if (!noDrawing && IsKeyPressed(KEY_ESCAPE)) noDrawing = !noDrawing;

        Cell* currentCell = removeFirst(&openCells, &size);

        if (currentCell == end) {
            freeQueue(openCells);
            return 0;
        }
        if (currentCell != start) currentCell->state = PATH;

        for (int i = 0; i < 4; i++) {
            if (!(((currentCell->neighbors << i) & 8) == 8)) {
                int x = currentCell->x, y = currentCell->y;
                switch (i) {
                    case 0:
                        x--;
                        break;
                    case 1:
                        y--;
                        break;
                    case 2:
                        y++;
                        break;
                    case 3:
                        x++;
                        break;
                }
                int tentativeG = currentCell->distance + 1;
                if (!closedCells[x][y] || tentativeG < board[x][y].distance) {
                    board[x][y].distance = tentativeG;
                    board[x][y].state = VISITED;
                    board[x][y].prev = (struct cell*) currentCell;
                    int fScore = board[x][y].distance + manhattanDistance(&board[x][y], end);
                    int distance = find(openCells, &board[x][y], size);
                    if (distance != -1) {
                        removeCell(&openCells, &board[x][y], &size);
                        insert(&openCells, &board[x][y], fScore, &size);
                    } else {
                        closedCells[x][y] = true;
                        insert(&openCells, &board[x][y], fScore, &size);
                    }
                }
            }
        }
        if (!noDrawing) {
            int startPosX = (GetScreenWidth()-side*width)/2;
            int startPosY = (GetScreenHeight()-side*height)/2;

            BeginDrawing();
                DrawBoard(board, startPosX, startPosY, side, width, height, rectFill, lineThick, rectOut);
            EndDrawing();
        }
    }
    freeQueue(openCells);
    return 0;
}

int dijkstra(Cell** board, Cell* start, Cell* end, int height, int width, int side, Color rectFill, int lineThick, Color rectOut, bool noDrawing) {
    int size;
    Queue* openCells = createQueue(start, 0, &size);
    bool closedCells[height][width];
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            closedCells[i][j] = false;
        }
    }

    closedCells[0][0] = true; 
    while (size > 0) {
        Cell* currentCell = removeFirst(&openCells, &size);

        if (WindowShouldClose() || (IsKeyDown(KEY_LEFT_CONTROL) && IsKeyDown(KEY_LEFT_SHIFT) && IsKeyDown(KEY_ESCAPE))) return 1;
        if (!noDrawing && IsKeyPressed(KEY_ESCAPE)) noDrawing = !noDrawing;

        if (currentCell == end) {
            freeQueue(openCells);
            return 0;
        }
        if (currentCell != start) currentCell->state = PATH;

        for (int i = 0; i < 4; i++) {
            if (!(((currentCell->neighbors << i) & 8) == 8)) {
                int x = currentCell->x, y = currentCell->y;
                switch (i) {
                    case 0:
                        x--;
                        break;
                    case 1:
                        y--;
                        break;
                    case 2:
                        y++;
                        break;
                    case 3:
                        x++;
                        break;
                }
                int tentativeG = currentCell->distance + 1;
                if (!closedCells[x][y] || tentativeG < board[x][y].distance) {
                    board[x][y].distance = tentativeG;
                    board[x][y].state = VISITED;
                    board[x][y].prev = (struct cell*) currentCell;
                    if (find(openCells, &board[x][y], size) != -1) {
                        removeCell(&openCells, &board[x][y], &size);
                        insert(&openCells, &board[x][y], tentativeG, &size);
                    } else {
                        closedCells[x][y] = true;
                        insert(&openCells, &board[x][y], tentativeG, &size);
                    }
                }
            }
        }
        if (!noDrawing) {
            int startPosX = (GetScreenWidth()-side*width)/2;
            int startPosY = (GetScreenHeight()-side*height)/2;
    
            BeginDrawing();
                DrawBoard(board, startPosX, startPosY, side, width, height, rectFill, lineThick, rectOut);
            EndDrawing();
        }
    }

    freeQueue(openCells);
    return 0;
}