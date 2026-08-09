#include "grid.h"

#include <raylib.h>
#include <cstring>

// RULES
#include "rules/conway.h"
#include "rules/smoothlifel.h"

void initGrid(Cell grid[GRID_WIDTH][GRID_HEIGHT]) {
    randomizeGrid(grid);

    /* Original fixed starting pattern:
    int cx = GRID_WIDTH / 2;
    int cy = GRID_HEIGHT / 2;

    grid[cx][cy].life = 1.0f;
    grid[cx][cy].r = 255;
    grid[cx][cy].g = 255;
    grid[cx][cy].b = 255;
    
    grid[cx + 1][cy].life = 1.0f;
    grid[cx + 1][cy].r = 255;
    grid[cx + 1][cy].g = 255;
    grid[cx + 1][cy].b = 255;

    grid[cx - 1][cy + 1].life = 1.0f;
    grid[cx - 1][cy + 1].r = 255;
    grid[cx - 1][cy + 1].g = 255;
    grid[cx - 1][cy + 1].b = 255;

    grid[cx][cy + 1].life = 1.0f;
    grid[cx][cy + 1].r = 255;
    grid[cx][cy + 1].g = 255;
    grid[cx][cy + 1].b = 255;

    grid[cx][cy + 2].life = 1.0f;
    grid[cx][cy + 2].r = 255;
    grid[cx][cy + 2].g = 255;
    grid[cx][cy + 2].b = 255;
    */
}

void updateGrid(Cell grid[GRID_WIDTH][GRID_HEIGHT]) {
    smoothLifeLRule(grid);
    // conwayRule(grid);
}

void drawGrid(Cell grid[GRID_WIDTH][GRID_HEIGHT]) {
    for (int x = 0; x < GRID_WIDTH; x++) {
        for (int y = 0; y < GRID_HEIGHT; y++) {
            if (grid[x][y].life > 0.001f) {
                unsigned char alpha = static_cast<unsigned char>(
                    grid[x][y].life * 255.0f
                );

                DrawRectangle(
                    x * CELL_SIZE, 
                    y * CELL_SIZE, 
                    CELL_SIZE, 
                    CELL_SIZE, 
                    Color{
                        grid[x][y].r, 
                        grid[x][y].g, 
                        grid[x][y].b, 
                        alpha
                    }
                );
            }
        }
    }
}

void randomizeGrid(Cell grid[GRID_WIDTH][GRID_HEIGHT]) {
    for (int x = 0; x < GRID_WIDTH; x++) {
        for (int y = 0; y < GRID_HEIGHT; y++) {
            if(GetRandomValue(0, 1)) {
                grid[x][y].life = 1.0f;
                grid[x][y].r = (unsigned char)GetRandomValue(0,255);
                grid[x][y].g = (unsigned char)GetRandomValue(0,255);
                grid[x][y].b = (unsigned char)GetRandomValue(0,255);
            } else {
                grid[x][y].life = 0.0f;
                grid[x][y].r = 0;
                grid[x][y].g = 0;
                grid[x][y].b = 0;
            }
        }
    }
}

void clearGrid(Cell grid[GRID_WIDTH][GRID_HEIGHT]) {
    for (int x = 0; x < GRID_WIDTH; x++) {
        for (int y = 0; y < GRID_HEIGHT; y++) {
            grid[x][y].life = 0.0f;
        }
    }
}

void paintCell(
    Cell grid[GRID_WIDTH][GRID_HEIGHT],
    Camera2D camera,
    Rectangle gameView
) {
    Vector2 mouseScreen = GetMousePosition();

    if (!CheckCollisionPointRec(mouseScreen, gameView)) return;

    Vector2 mouseWorld = GetScreenToWorld2D(mouseScreen, camera);

    int cellX = (int)(mouseWorld.x / CELL_SIZE);
    int cellY = (int)(mouseWorld.y / CELL_SIZE);

    if (cellX < 0 || cellX >= GRID_WIDTH || cellY < 0 || cellY >= GRID_HEIGHT) return;

    if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
        grid[cellX][cellY].life = 1.0f;
        grid[cellX][cellY].r = GetRandomValue(0, 255);
        grid[cellX][cellY].g = GetRandomValue(0, 255);
        grid[cellX][cellY].b = GetRandomValue(0, 255);
    }

    if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT)) {
        grid[cellX][cellY].life = 0.0f;
    }
}
