#include <iostream>
#include <raylib.h>

using namespace std;

const int SCREEN_WIDTH = 1200;
const int SCREEN_HEIGHT = 1200;
const int SCREEN_FPS = 20;
const int CELL_SIZE = 5;

const int GRID_WIDTH = SCREEN_WIDTH / CELL_SIZE;
const int GRID_HEIGHT = SCREEN_HEIGHT / CELL_SIZE;

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
void paintCell(Cell grid[GRID_WIDTH][GRID_HEIGHT]);

int main () {
    bool isRunning = true;

    // init window
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Game of Life");
    SetTargetFPS(SCREEN_FPS);

    // init grid
    Cell grid[GRID_WIDTH][GRID_HEIGHT];
    initGrid(grid);

    // main loop
    while (WindowShouldClose() == false){
        if(IsKeyPressed(KEY_SPACE)) {
            isRunning = !isRunning;
        }
        paintCell(grid);

        BeginDrawing();
            ClearBackground(BLACK);

            if (isRunning) {
                updateGrid(grid);
            }

            randomizeGrid(grid);
            clearGrid(grid);
            drawGrid(grid);
        EndDrawing();
    }

    CloseWindow();
}

void initGrid(Cell grid[GRID_WIDTH][GRID_HEIGHT]) {
    int cx = GRID_WIDTH / 2;
    int cy = GRID_HEIGHT / 2;

    grid[cx][cy].isAlive = true;
    grid[cx + 1][cy].isAlive = true;

    grid[cx - 1][cy + 1].isAlive = true;
    grid[cx][cy + 1].isAlive = true;

    grid[cx][cy + 2].isAlive = true;
}

void updateGrid(Cell grid[GRID_WIDTH][GRID_HEIGHT]) {
    Cell newGrid[GRID_WIDTH][GRID_HEIGHT];

    for (int x = 0; x < GRID_WIDTH; x++) {
        for (int y = 0; y < GRID_HEIGHT; y++) {
            int aliveNeighbors = 0;

            int totalR = 0;
            int totalG = 0;
            int totalB = 0;

            for (int i = -1; i <= 1; i++) {
                for (int j = -1; j <= 1; j++) {
                    if (i == 0 && j == 0) continue;
                    int neighborX = x + i;
                    int neighborY = y + j;
                    
                    if (neighborX < 0 || neighborX >= GRID_WIDTH || neighborY < 0 || neighborY >= GRID_HEIGHT) continue;

                    if (grid[neighborX][neighborY].isAlive) {
                        aliveNeighbors++;
                        totalR += grid[neighborX][neighborY].r;
                        totalG += grid[neighborX][neighborY].g;
                        totalB += grid[neighborX][neighborY].b;
                    }
                }
            }

            int avgR = (aliveNeighbors > 0) ? totalR / aliveNeighbors : 0;
            int avgG = (aliveNeighbors > 0) ? totalG / aliveNeighbors : 0;
            int avgB = (aliveNeighbors > 0) ? totalB / aliveNeighbors : 0;

            if (grid[x][y].isAlive) {
                newGrid[x][y] = (aliveNeighbors == 2 || aliveNeighbors == 3) ? 
                    Cell{
                        true, 
                        (unsigned char)avgR,
                        (unsigned char)avgG,
                        (unsigned char)avgB,
                    } : 
                    Cell{false, 0, 0, 0};
            } else {
                newGrid[x][y] = (aliveNeighbors == 3) ? 
                    Cell{
                        true, 
                        (unsigned char)avgR,
                        (unsigned char)avgG,
                        (unsigned char)avgB,
                    } : 
                    Cell{false, 0, 0, 0};
            }
        }
    }

    memcpy(grid, newGrid, sizeof(newGrid));
}

void drawGrid(Cell grid[GRID_WIDTH][GRID_HEIGHT]) {
    for (int x = 0; x < GRID_WIDTH; x++) {
        for (int y = 0; y < GRID_HEIGHT; y++) {
            if (grid[x][y].isAlive) {
                DrawRectangle(x * CELL_SIZE, y * CELL_SIZE, CELL_SIZE, CELL_SIZE, Color{grid[x][y].r, grid[x][y].g, grid[x][y].b, 255});
            }
        }
    }
}

void randomizeGrid(Cell grid[GRID_WIDTH][GRID_HEIGHT]) {
    if(IsKeyPressed(KEY_R)) {
        for (int x = 0; x < GRID_WIDTH; x++) {
            for (int y = 0; y < GRID_HEIGHT; y++) {
                if(GetRandomValue(0, 1)) {
                    grid[x][y].isAlive = true;
                    grid[x][y].r = (unsigned char)GetRandomValue(0,255);
                    grid[x][y].g = (unsigned char)GetRandomValue(0,255);
                    grid[x][y].b = (unsigned char)GetRandomValue(0,255);
                } else {
                    grid[x][y].isAlive = false;
                }
            }
        }
    }
}

void clearGrid(Cell grid[GRID_WIDTH][GRID_HEIGHT]) {
    if(IsKeyPressed(KEY_C)) {
        for (int x = 0; x < GRID_WIDTH; x++) {
            for (int y = 0; y < GRID_HEIGHT; y++) {
                grid[x][y].isAlive = false;
            }
        }
    }
}

void paintCell(Cell grid[GRID_WIDTH][GRID_HEIGHT]) {
    int cellX = GetMouseX() / CELL_SIZE;
    int cellY = GetMouseY() / CELL_SIZE;

    if (cellX < 0 || cellX >= GRID_WIDTH ||
        cellY < 0 || cellY >= GRID_HEIGHT)
        return;

    if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
        grid[cellX][cellY].isAlive = true;
        grid[cellX][cellY].r = (unsigned char)GetRandomValue(0,255);
        grid[cellX][cellY].g = (unsigned char)GetRandomValue(0,255);
        grid[cellX][cellY].b = (unsigned char)GetRandomValue(0,255);
    }

    if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT))
        grid[cellX][cellY].isAlive = false;
}