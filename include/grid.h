#pragma once

#include "config.h"
#include "raylib.h"

struct Cell {
    bool isAlive;

    unsigned char r;
    unsigned char g;
    unsigned char b;
};

void updateGrid(Cell grid[GRID_WIDTH][GRID_HEIGHT]);
void drawGrid(Cell grid[GRID_WIDTH][GRID_HEIGHT]);
void initGrid(Cell grid[GRID_WIDTH][GRID_HEIGHT]);
void randomizeGrid(Cell grid[GRID_WIDTH][GRID_HEIGHT]);
void clearGrid(Cell grid[GRID_WIDTH][GRID_HEIGHT]);
void paintCell(Cell grid[GRID_WIDTH][GRID_HEIGHT], Camera2D camera, Rectangle gameView);