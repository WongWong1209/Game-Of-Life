#pragma once

#include "config.h"
#include "raylib.h"

struct Cell {
    float life = 0.0f;

    unsigned char r = 255;
    unsigned char g = 255;
    unsigned char b = 255;
};

void updateGrid(Cell grid[GRID_WIDTH][GRID_HEIGHT]);
void drawGrid(Cell grid[GRID_WIDTH][GRID_HEIGHT]);
void initGrid(Cell grid[GRID_WIDTH][GRID_HEIGHT]);
void randomizeGrid(Cell grid[GRID_WIDTH][GRID_HEIGHT]);
void clearGrid(Cell grid[GRID_WIDTH][GRID_HEIGHT]);
void paintCell(Cell grid[GRID_WIDTH][GRID_HEIGHT], Camera2D camera, Rectangle gameView);
