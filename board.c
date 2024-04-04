#include <stdio.h>
#include <stdlib.h>
#include "cell.h"
#include "board.h"

Board createBoard(int x, int y) {
  Board board = (Board) malloc(sizeof(Cell*) * x);

  for (int i = 0; i < x; i++) {
    Cell* line = malloc(sizeof(Cell) * y);
    for (int j = 0; j < y; j++) {
      line[j].state = EMPTY;
      line[j].visited = 0;
      line[j].distance = 0;
      line[j].x = i;
      line[j].y = j;
      line[j].neighbors = 0b1111;
      if (i != 0) {
        line[j].neighbors += 0b10000000;
      }
      if (j != 0) {
        line[j].neighbors += 0b01000000;
      }
      if (i != x - 1) {
        line[j].neighbors += 0b00010000;
      }
      if (j != y - 1) {
        line[j].neighbors += 0b00100000;
      }
    }
    board[i] = line;
  }

  return board;
}

void DrawBoard(Board board, int startPosX, int startPosY, int side, int width, int height, Color rectFill, int lineThick, Color rectOut) {
    ClearBackground(RAYWHITE);

    DrawRectangle(startPosX, startPosY, side*width, side*height, rectFill);
			
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
			DrawCellWalls(startPosX + j*side, startPosY + i*side, side, &board[i][j], lineThick, rectOut);
        }
    }
    DrawFPS(0, 0);
    //DrawRectangleLinesEx((Rectangle) {startPosX, startPosY, side*width, side*height}, 5, rectOut);
}

void clearBoard(Board board, int x, int y) {
    for (int i = 0; i < x; i++) {
        for (int j = 0; j < y; j++) {
            board[i][j].state = EMPTY;
            board[i][j].visited = 0;
            board[i][j].distance = 0;
            board[i][j].x = i;
            board[i][j].y = j;
            board[i][j].neighbors = 0b11111111;
            if (i == 0) {
                board[i][j].neighbors ^= 0b10000000;
            }
            if (j == 0) {
                board[i][j].neighbors ^= 0b01000000;
            }
            if (i == x - 1) {
                board[i][j].neighbors ^= 0b00010000;
            }
            if (j == y - 1) {
                board[i][j].neighbors ^= 0b00100000;
            }
        }
    }
}

void clearBoardColor(Board board, int x, int y) {
    for (int i = 0; i < x; i++) {
        for (int j = 0; j < y; j++) {
            board[i][j].state = EMPTY;
            board[i][j].visited = 0;
            board[i][j].distance = 0;
        }
    }
}

void deleteBoard(Board board, int x) {
  for (int i = 0; i < x; i++) {
    free(board[i]);
  }
  free(board);
}
