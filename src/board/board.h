#ifndef BOARD_H_
#define BOARD_H_
#include "../cell/cell.h"

typedef Cell** Board;

Board createBoard(int x, int y);
void clearBoard(Board board, int x, int y);
void deleteBoard(Cell** board, int x);
void DrawBoard(Board board, int startPosX, int startPosY, int side, int width, int height, Color rectFill, int lineThick, Color rectOut);
void clearBoardColor(Board board, int x, int y);

#endif // BOARD_H_
