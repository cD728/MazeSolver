#include <raylib.h>
#include <stdlib.h>
#include "cell.h"
#include "board.h"
#include "stack.h"

int recursiveMazeStack(Board board, int side, int width, int height, Color rectFill, int lineThick, Color rectOut, bool noDrawing) {
    int x = GetRandomValue(0, height - 1);
    int y = GetRandomValue(0, width - 1);
    Stack* stack = createStack(&board[x][y]);
    stack->cell->visited = 1;

    double dt = 0;

    while (!isEmptyStack(stack)) {
        int startPosX = (GetScreenWidth()-side*width)/2;
        int startPosY = (GetScreenHeight()-side*height)/2;
        dt -= GetFrameTime();

        if (WindowShouldClose() || (IsKeyDown(KEY_LEFT_CONTROL) && IsKeyDown(KEY_LEFT_SHIFT) && IsKeyDown(KEY_ESCAPE))) return 1;
        if (!noDrawing && IsKeyPressed(KEY_ESCAPE)) noDrawing = !noDrawing;
        
        if (dt < 0 || noDrawing) {
            dt = 0.000;
            Cell* currentCell = pop(&stack);
            currentCell->state = CURRENT;

            if (!noDrawing) {
                BeginDrawing();
                    DrawBoard(board, startPosX, startPosY, side, width, height, rectFill, lineThick, rectOut);
                EndDrawing();
            }

            int n = 0;
            Cell* neigh[4];
            uint8_t mask[4]; // nao gosto disto oh well
            for (int i = 0; i < 4; i++) {
                if (((currentCell->neighbors << i) & 128) == 128) {
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
                    if (board[x][y].visited != 1) {
                        neigh[n] = &board[x][y];
                        mask[n] = 1 << (3 - i);
                        n++;
                    }
                }
            }

            if (n != 0) {
                push(&stack, currentCell);
                int neighbor = GetRandomValue(0, n - 1); 

                currentCell->neighbors ^= mask[neighbor];
                uint8_t invMask = (mask[neighbor] << 3) & 0b1000;
                invMask += (mask[neighbor] << 1) & 0b100;
                invMask += (mask[neighbor] >> 1) & 0b10;
                invMask += (mask[neighbor] >> 3) & 1;
                neigh[neighbor]->neighbors ^= invMask;

                neigh[neighbor]->visited++;

                push(&stack, neigh[neighbor]);
            }
            currentCell->state = VISITED;
        } else {
            stack->cell->state = CURRENT;
            if (!noDrawing) {
                BeginDrawing();
                    DrawBoard(board, startPosX, startPosY, side, width, height, rectFill, lineThick, rectOut);
                EndDrawing();
            }
        }
    }
    return 0;
}