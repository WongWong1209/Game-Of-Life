/*******************************************************************************************
*
*   GameOfLifeUi v1.0.0 - Game of Life control panel
*
*   MODULE USAGE:
*       #define GUI_GAME_OF_LIFE_UI_IMPLEMENTATION
*       #include "gui_game_of_life_ui.h"
*
*       INIT: GuiGameOfLifeUiState state = InitGuiGameOfLifeUi();
*       DRAW: GuiGameOfLifeUi(&state);
*
*   LICENSE: Propietary License
*
*   Copyright (c) 2022 WongWong1209. All Rights Reserved.
*
*   Unauthorized copying of this file, via any medium is strictly prohibited
*   This project is proprietary and confidential unless the owner allows
*   usage in any other form by expresely written permission.
*
**********************************************************************************************/

#include "raylib.h"
#include "grid.h"

// WARNING: raygui implementation is expected to be defined before including this header
#undef RAYGUI_IMPLEMENTATION
#include "raygui.h"

#include <string.h>     // Required for: strcpy()

#ifndef GUI_GAME_OF_LIFE_UI_H
#define GUI_GAME_OF_LIFE_UI_H

typedef struct {
    bool WindowBox000Active;
    bool TextBox004EditMode;
    char TextBox004Text[128];

    Color ColorPicker010Value;
    float Slider011Value;
    float Slider014Value;

    bool randomPressed;
    bool clearPressed;
    bool playPausePressed;

    Rectangle layoutRecs[15];

    // Custom state variables (depend on development software)
    // NOTE: This variables should be added manually if required

} GuiGameOfLifeUiState;

#ifdef __cplusplus
extern "C" {            // Prevents name mangling of functions
#endif

//----------------------------------------------------------------------------------
// Defines and Macros
//----------------------------------------------------------------------------------
//...

//----------------------------------------------------------------------------------
// Types and Structures Definition
//----------------------------------------------------------------------------------
// ...

//----------------------------------------------------------------------------------
// Module Functions Declaration
//----------------------------------------------------------------------------------
GuiGameOfLifeUiState InitGuiGameOfLifeUi(void);
void GuiGameOfLifeUi(GuiGameOfLifeUiState *state);

#ifdef __cplusplus
}
#endif

#endif // GUI_GAME_OF_LIFE_UI_H

/***********************************************************************************
*
*   GUI_GAME_OF_LIFE_UI IMPLEMENTATION
*
************************************************************************************/
#if defined(GUI_GAME_OF_LIFE_UI_IMPLEMENTATION)

#include "raygui.h"

//----------------------------------------------------------------------------------
// Global Variables Definition
//----------------------------------------------------------------------------------
//...

//----------------------------------------------------------------------------------
// Internal Module Functions Definition
//----------------------------------------------------------------------------------
//...

//----------------------------------------------------------------------------------
// Module Functions Definition
//----------------------------------------------------------------------------------
GuiGameOfLifeUiState InitGuiGameOfLifeUi(void)
{
    GuiGameOfLifeUiState state = { 0 };

    state.WindowBox000Active = true;
    state.TextBox004EditMode = false;
    strcpy(state.TextBox004Text, "");
    state.ColorPicker010Value = (Color){ 0, 0, 0, 0 };
    state.Slider011Value = 0.0f;
    state.Slider014Value = 0.0f;

    state.layoutRecs[0] = (Rectangle){ 0, 0, 1464, 912 };
    state.layoutRecs[1] = (Rectangle){ 32, 56, 1152, 824 };
    state.layoutRecs[2] = (Rectangle){ 1208, 56, 224, 824 };
    state.layoutRecs[3] = (Rectangle){ 1224, 64, 120, 24 };
    state.layoutRecs[4] = (Rectangle){ 1224, 88, 120, 24 };
    state.layoutRecs[5] = (Rectangle){ 1224, 144, 192, 144 };
    state.layoutRecs[6] = (Rectangle){ 1256, 160, 128, 32 };
    state.layoutRecs[7] = (Rectangle){ 1256, 200, 128, 32 };
    state.layoutRecs[8] = (Rectangle){ 1256, 240, 128, 32 };
    state.layoutRecs[9] = (Rectangle){ 1224, 640, 192, 216 };
    state.layoutRecs[10] = (Rectangle){ 1264, 744, 96, 96 };
    state.layoutRecs[11] = (Rectangle){ 1240, 672, 160, 16 };
    state.layoutRecs[12] = (Rectangle){ 1240, 648, 120, 24 };
    state.layoutRecs[13] = (Rectangle){ 1240, 688, 120, 24 };
    state.layoutRecs[14] = (Rectangle){ 1240, 712, 160, 16 };

    // Custom variables initialization

    return state;
}


void GuiGameOfLifeUi(GuiGameOfLifeUiState *state)
{
    const char *WindowBox000Text = "GAME OF LIFE";
    const char *GroupBox002Text = "CONTROL";
    const char *Label003Text = "World Size";
    const char *GroupBox005Text = "Action Buttons";
    const char *Button006Text = "Random (R)";
    const char *Button007Text = "Clear (C)";
    const char *Button008Text = "Play / Pause (SPACE)";
    const char *GroupBox009Text = "Brush Settings";
    const char *Slider011Text = "";
    const char *Label012Text = "Brush Size";
    const char *Label013Text = "Eraser Size";
    const char *Slider014Text = "";
    const char *Panel001Text = "";
    const char *ColorPicker010Text = "";
    
    if (state->WindowBox000Active)
    {
        state->WindowBox000Active = !GuiWindowBox(state->layoutRecs[0], WindowBox000Text);
        GuiPanel(state->layoutRecs[1], Panel001Text);
    }
    GuiGroupBox(state->layoutRecs[2], GroupBox002Text);
    GuiLabel(state->layoutRecs[3], Label003Text);
    if (GuiTextBox(state->layoutRecs[4], state->TextBox004Text, 128, state->TextBox004EditMode)) state->TextBox004EditMode = !state->TextBox004EditMode;
    GuiGroupBox(state->layoutRecs[5], GroupBox005Text);

    if (GuiButton(state->layoutRecs[6], Button006Text)) {
        state->randomPressed = true;
    }

    if (GuiButton(state->layoutRecs[7], Button007Text)) {
        state->clearPressed = true;
    }

    if (GuiButton(state->layoutRecs[8], Button008Text)) {
        state->playPausePressed = true;
    }
    
    GuiGroupBox(state->layoutRecs[9], GroupBox009Text);
    GuiColorPicker(state->layoutRecs[10], ColorPicker010Text, &state->ColorPicker010Value);
    GuiSlider(state->layoutRecs[11], Slider011Text, NULL, &state->Slider011Value, 0, 100);
    GuiLabel(state->layoutRecs[12], Label012Text);
    GuiLabel(state->layoutRecs[13], Label013Text);
    GuiSlider(state->layoutRecs[14], Slider014Text, NULL, &state->Slider014Value, 0, 100);
}

#endif // GUI_GAME_OF_LIFE_UI_IMPLEMENTATION
