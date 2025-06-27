#include "BOARD.h"
#include "BUTTON.h"

int main()
{
    //SOLITAIRE WINDOW
    InitWindow(BOARD_WIDTH, BOARD_HEIGHT, "Solitaire");
    SetTargetFPS(60);

    //PROGRAM LOOP
    while (!WindowShouldClose()) {
        //HOME MENU UI STUFF
        float saveButtonY = DIVISION_HEIGHT_SUITS + BUTTON_HEIGHT;
        float exitButtonY = saveButtonY + (2 * BUTTON_HEIGHT);
        float time = 0.0f;

        Button saveButton(BUTTON_START, saveButtonY, BUTTON_WIDTH, BUTTON_HEIGHT, SAVE_TEXT);
        Button exitButton(BUTTON_START, exitButtonY, BUTTON_WIDTH, BUTTON_HEIGHT, EXIT_TEXT);
        Button newButton(25, 400, BUTTON_WIDTH, BUTTON_HEIGHT, NEW_TEXT);
        Button loadButton(25, 500, BUTTON_WIDTH, BUTTON_HEIGHT, LOAD_TEXT);
        Button backButton(25, 500, BUTTON_WIDTH, BUTTON_HEIGHT, BACK_TEXT);

        Texture2D background = LoadTexture(BACKGROUND_TEXTURE);
        background.width = BOARD_WIDTH;
        background.height = BOARD_HEIGHT;

        bool flag = 0, win = 0, stay = 0;
        int pens = 0;
        Vector2 mouse;

        //HOME MENU LOOP
        while (!WindowShouldClose()) {
            if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                mouse = GetMousePosition();
                if (CheckCollisionPointRec(mouse, newButton.getHitBox())) {
                    stay = 1;
                    break;
                }
                if (CheckCollisionPointRec(mouse, loadButton.getHitBox())) {
                    stay = 1;
                    flag = 1;
                    break;
                }
            }
            BeginDrawing();
            DrawTexture(background, 0, 0, WHITE);
            newButton.draw();
            loadButton.draw();
            EndDrawing();
        }
        UnloadTexture(background);

        if (!stay) break;

        //INITIALISING MASTER OCTOPUS
        Board& octopus = Board::getInstance();
        octopus.randomise();
        octopus.initialise();
        octopus.position();
        if (flag) octopus.loadGame();

        //GAME LOOP
        while (!WindowShouldClose()) {
            //WIN CHECK
            if (octopus.checkWin()) {
                win = 1;
                break;
            }
            //SAVE/EXIT BUTTON CHECK
            if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
                octopus.setMouse(GetMousePosition());
                if (CheckCollisionPointRec(octopus.getMouse(), saveButton.getHitBox())) {
                    try {
                        octopus.saveGame();
                    }
                    catch (const char* error) {
                        octopus.logError(ERROR_FILE);
                    }
                    break;
                }
                if (CheckCollisionPointRec(octopus.getMouse(), exitButton.getHitBox())) {
                    break;
                }
            }
            //MOVE MAKING
            if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                octopus.setMouse(GetMousePosition());
                if (!octopus.isSourceComplete()) {
                    octopus.resetInputs();
                    try {
                        octopus.pickCard();
                    }
                    catch (const char* error) {
                        octopus.logError(ERROR_INVALID);
                        if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) continue;
                    }
                }
                else {
                    try {
                        octopus.setCard();
                    }
                    catch (const char* error) {
                        octopus.logError(ERROR_INVALID);
                        octopus.resetInputs();
                    }
                    octopus.resetInputs();
                }
            }

            //TIME UPDATES
            time += GetFrameTime();
            int minutes = (int)time / 60;
            int seconds = (int)time % 60;
            if (minutes == pens + 1) {
                pens++;
                octopus.subScore();
            }

            //DRAWING UPDATES
            BeginDrawing();
            ClearBackground(GREEN);
            octopus.draw();
            saveButton.draw();
            exitButton.draw();
            DrawText(TextFormat("Time : %02d:%02d", minutes, seconds), BUTTON_START, VERT_WIDTH, 25, WHITE);
            DrawText(TextFormat("Score : %d", octopus.getScore()), BUTTON_START, (VERT_WIDTH * 3), 25, WHITE);
            EndDrawing();
        }

        //LOADING WIN SCREEN
        background = LoadTexture(WIN_TEXTURE);
        background.width = BOARD_WIDTH;
        background.height = BOARD_HEIGHT;

        //WIN SCREEN LOOP
        while (win) {
            if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                mouse = GetMousePosition();
                if (CheckCollisionPointRec(mouse, backButton.getHitBox())) break;
            }
            BeginDrawing();
            DrawTexture(background, 0, 0, WHITE);
            DrawText(TextFormat("Score : %d", octopus.getScore()), 25, 400, 30, WHITE);
            backButton.draw();
            EndDrawing();
        }
        //CLEAN-UP
        UnloadTexture(background);
        octopus.destroy();
    }

    //CLOSING
    CloseWindow();
    return 0;
}