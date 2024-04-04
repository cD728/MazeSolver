#include "cell.h"

void DrawCellWalls(int x, int y, int side, Cell* cell, int lineThick, Color color) {
    switch (cell->state) {
    case START:
        DrawRectangle(x, y, side, side, GREEN);
        break;
    case END:
        DrawRectangle(x, y, side, side, BLUE);
        break;
    case VISITED:
        DrawRectangle(x, y, side, side, ORANGE);
        break;
    case CURRENT:
        DrawRectangle(x, y, side, side, RED);
        break;
    case EMPTY:
        break;
    case PATH:
        DrawRectangle(x, y, side, side, RED);
        break;
    case BESTPATH:
        DrawRectangle(x, y, side, side, PURPLE);
        break;
    }

    if (cell->neighbors & 0b1000) {
        DrawLineEx((Vector2) {x - 1, y}, (Vector2) {x + side, y}, lineThick, color);
    }
    if (cell->neighbors & 0b100) {
        DrawLineEx((Vector2) {x, y - 1}, (Vector2) {x, y + side}, lineThick, color);
    }
    if (cell->neighbors & 0b10) {
        DrawLineEx((Vector2) {x + side, y - 1}, (Vector2) {x + side, y + side}, lineThick, color);
    }
    if (cell->neighbors & 1) {
        DrawLineEx((Vector2) {x - 1, y + side}, (Vector2) {x + side, y + side}, lineThick, color);
    }
}