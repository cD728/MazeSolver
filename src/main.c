#include <raylib.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "cell/cell.h"
#include "stack/stack.h"
#include "board/board.h"
#include "maze/maze.h"
#include "pathfind/pathfind.h"

void reDefine(Board board, Cell** start, Cell** end, int height, int width) {
    *start = &board[0][0];
    *end = &board[height - 1][width - 1];
}   

int paintBestPath(Cell* end, Cell* start, Board board, int side, int width, int height, Color rectFill, int lineThick, Color rectOut, bool noDrawing) {
    struct cell* cell = (struct cell*) end;
    cell->state = END;
    cell = cell->prev;

    int startPosX = (GetScreenWidth()-side*width)/2;
    int startPosY = (GetScreenHeight()-side*height)/2;
    if (!noDrawing) {
        BeginDrawing();
            DrawBoard(board, startPosX, startPosY, side, width, height, rectFill, lineThick, rectOut);
        EndDrawing();
    }

    while (cell != start) {
        if (WindowShouldClose() || (IsKeyDown(KEY_LEFT_CONTROL) && IsKeyDown(KEY_LEFT_SHIFT) && IsKeyDown(KEY_ESCAPE))) return 1;
        if (!noDrawing && IsKeyPressed(KEY_ESCAPE)) noDrawing = !noDrawing;

        cell->state = BESTPATH;
        cell = cell->prev;

        startPosX = (GetScreenWidth()-side*width)/2;
        startPosY = (GetScreenHeight()-side*height)/2;

        if (!noDrawing) {
            BeginDrawing();
                DrawBoard(board, startPosX, startPosY, side, width, height, rectFill, lineThick, rectOut);
            EndDrawing();
        }
    }
    
    return 0;
}

int main(void) {
	int width = 20, height = 10;

  	Board board = createBoard(height, width);

    bool mazeMade = false;
    bool pathFound = false;
    bool noDrawing = false;
    bool autoDrawing = false;

    int side = 50;
    const int lineThick = 2;
    double dt = 0.0;
    int err = 0;

    int startPosX = 0;
    int startPosY = 0;

    Cell* start = &board[0][0];
    Cell* end = &board[height-1][width-1];

    PATHFINDERS pathfinder = 0;
    #if DEBUG
        SetTraceLogLevel(LOG_ALL);
    #else
        SetTraceLogLevel(LOG_ERROR);
    #endif

    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(width*side, height*side, "bruh eu sou pan");  

    Color rectFill = GRAY;
    Color rectOut = BLACK;
    SetExitKey(KEY_NULL);
    SetTargetFPS(0);

    while (!WindowShouldClose() && !(IsKeyDown(KEY_LEFT_CONTROL) && IsKeyDown(KEY_LEFT_SHIFT) && IsKeyDown(KEY_ESCAPE))) {
        startPosX = (GetScreenWidth()-side*width)/2;
        startPosY = (GetScreenHeight()-side*height)/2;
        
        err = 0;

        switch (GetKeyPressed()) {
        case KEY_A: //TODO: nao fazer isto. isto e mau mas eu quero ver o meu programa a ir bruuuuuuuuu
            autoDrawing = !autoDrawing;
            break;
        case KEY_U:
            noDrawing = !noDrawing;
            break;

        case KEY_C:
            if (!mazeMade) {
                err = recursiveMazeStack(board, side, width, height, rectFill, lineThick, rectOut, noDrawing);
                clearBoardColor(board, height, width);
                start->state = START;
  	            end->state = END;
                mazeMade = !mazeMade;
            } else {
                clearBoard(board, height, width);
                reDefine(board, &start, &end, height, width);
                mazeMade = !mazeMade;
                pathFound = false;
            }
            break;

        case KEY_ZERO:
        case KEY_KP_0:
            pathfinder = ASTAR;
            break;
        
        case KEY_ONE:
        case KEY_KP_1:
            pathfinder = DIJKSTRA;
            break;

        case KEY_RIGHT:
            if (!mazeMade) {
                deleteBoard(board, height);
                width++;
                board = createBoard(height, width);
                reDefine(board, &start, &end, height, width);
            }
            break;

        case KEY_LEFT:
            if (!mazeMade && width > 1) {
                deleteBoard(board, height);
                width--;
                board = createBoard(height, width);
                reDefine(board, &start, &end, height, width);
            }
            break;

        case KEY_UP:
            if (!mazeMade) {
                deleteBoard(board, height);
                height++;
                board = createBoard(height, width);
                reDefine(board, &start, &end, height, width);
            }
            break;
        
        case KEY_DOWN:
            if (!mazeMade && height > 1) {
                deleteBoard(board, height);
                height--;
                board = createBoard(height, width);
                reDefine(board, &start, &end, height, width);
            }
            break;

        case KEY_KP_ADD:
        //case KEY
            if (!mazeMade) {
                side++;
            }
            break;

        case KEY_KP_SUBTRACT:
        case KEY_MINUS:
            if (!mazeMade && side > 5) {
                side--;
            }
            break;
        
        case KEY_ENTER:
            if (mazeMade) {
                if (!pathFound) {
                    switch (pathfinder) {
                    case ASTAR:
                        err = Astar(board, start, end, height, width, side, rectFill, lineThick, rectOut, noDrawing);
                        break;
                    
                    case DIJKSTRA:
                        err = dijkstra(board, start, end, height, width, side, rectFill, lineThick, rectOut, noDrawing);
                        break;
                    }
                    
                    paintBestPath(end, start, board, side, width, height, rectFill, lineThick, rectOut, noDrawing);
                    pathFound = !pathFound;
                } else {
                    clearBoardColor(board, height, width);
                    pathFound = !pathFound;
                    start->state = START;
                    end->state = END;
                }
            }
            break;

        default:
            break;
        }

        if (autoDrawing) {
            if (pathFound) {
                if (dt < 0) {
                    clearBoard(board, height, width);
                    reDefine(board, &start, &end, height, width);
                    mazeMade = !mazeMade;
                    pathFound = false;
                } else {
                    dt -= GetFrameTime();
                }
            } else if (!mazeMade) {
                err = recursiveMazeStack(board, side, width, height, rectFill, lineThick, rectOut, noDrawing);
                clearBoardColor(board, height, width);
                start->state = START;
  	            end->state = END;
                mazeMade = !mazeMade;
            } else {
                switch (pathfinder) {
                case ASTAR:
                    err = Astar(board, start, end, height, width, side, rectFill, lineThick, rectOut, noDrawing);
                    break;
                
                case DIJKSTRA:
                    err = dijkstra(board, start, end, height, width, side, rectFill, lineThick, rectOut, noDrawing);
                    break;
                }
                
                paintBestPath(end, start, board, side, width, height, rectFill, lineThick, rectOut, noDrawing);
                pathFound = !pathFound;
                dt = 2.0;
            }
        }

        if (err) break;

        BeginDrawing();
            DrawBoard(board, startPosX, startPosY, side, width, height, rectFill, lineThick, rectOut);
        EndDrawing();
    }

    CloseWindow();

  	//Astar(board, &board[0][0], &board[x-1][y-1]);

  	deleteBoard(board, height);

  	return 0;
}
