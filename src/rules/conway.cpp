#include "grid.h"
#include <string.h>

void conwayRule(Cell grid[GRID_WIDTH][GRID_HEIGHT]) {
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

                    if (grid[neighborX][neighborY].life >= 0.5f) {
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

            if (grid[x][y].life >= 0.5f) {
                newGrid[x][y] = (aliveNeighbors == 2 || aliveNeighbors == 3) ? 
                    Cell{
                        1.0f,
                        (unsigned char)avgR,
                        (unsigned char)avgG,
                        (unsigned char)avgB,
                    } : 
                    Cell{0.0f, 0, 0, 0};
            } else {
                newGrid[x][y] = (aliveNeighbors == 3) ? 
                    Cell{
                        1.0f,
                        (unsigned char)avgR,
                        (unsigned char)avgG,
                        (unsigned char)avgB,
                    } : 
                    Cell{0.0f, 0, 0, 0};
            }
        }
    }

    memcpy(grid, newGrid, sizeof(newGrid));
}
