#include "config.h"
#include "grid.h"

#include <iostream>
#include <raylib.h>

#define RAYGUI_IMPLEMENTATION
#include "raygui.h"
#define GUI_GAME_OF_LIFE_UI_IMPLEMENTATION
#include "gui_game_of_life_ui.h"

int main () {
    bool isRunning = true;

    // init window
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Game of Life");
    SetTargetFPS(SCREEN_FPS);

    GuiLoadStyle("assets/styles/style_jungle.rgs");

    GuiGameOfLifeUiState ui = InitGuiGameOfLifeUi();

    Rectangle gameView = ui.layoutRecs[1];

    Camera2D camera = {};

    camera.target = {0.0f, 0.0f};

    camera.offset = {
        gameView.x,
        gameView.y
    };

    camera.rotation = 0.0f;
    camera.zoom = 1.0f;

    // init grid
    Cell grid[GRID_WIDTH][GRID_HEIGHT]{};
    initGrid(grid);

    // main loop
    while (WindowShouldClose() == false){
        ui.randomPressed = false;
        ui.clearPressed = false;
        ui.playPausePressed = false;

        paintCell(grid, camera, gameView);

        Vector2 mouse = GetMousePosition();
        bool mouseInsideGameView = CheckCollisionPointRec(mouse, gameView);

        if (mouseInsideGameView && IsMouseButtonDown(MOUSE_BUTTON_MIDDLE)) {
            Vector2 delta = GetMouseDelta();
            camera.target.x -= delta.x / camera.zoom;
            camera.target.y -= delta.y / camera.zoom;
        }

        if (mouseInsideGameView) {

        float wheel = GetMouseWheelMove();
            if (wheel != 0.0f) {
                camera.zoom += wheel * 0.1f;
                if (camera.zoom < 0.2f) camera.zoom = 0.2f;
                if (camera.zoom > 5.0f) camera.zoom = 5.0f;
            }
        }

        BeginDrawing();
            ClearBackground(BLACK);
            GuiGameOfLifeUi(&ui);

            BeginScissorMode(
                (int)gameView.x,
                (int)gameView.y,
                (int)gameView.width,
                (int)gameView.height
            );
                BeginMode2D(camera);
                    if (isRunning) { updateGrid(grid); }
                    if(IsKeyPressed(KEY_R) || ui.randomPressed) { randomizeGrid(grid); }
                    if(IsKeyPressed(KEY_C) || ui.clearPressed) { clearGrid(grid); }
                    if(IsKeyPressed(KEY_SPACE) || ui.playPausePressed) { isRunning = !isRunning; }
                    drawGrid(grid);
                EndMode2D();
            EndScissorMode();
        EndDrawing();
    }

    CloseWindow();
}