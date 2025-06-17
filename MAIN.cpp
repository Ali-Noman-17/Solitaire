#include "BOARD.h"


int main()
{
    //HOME WINDOW
    InitWindow(BOARD_LENGTH, BOARD_HEIGHT, "Solitaire MENU");
    SetTargetFPS(60);

    //HOME MENU UI STUFF
    float saveButtonY = DIVISION_HEIGHT_SUITS + BUTTON_HEIGHT;
    float exitButtonY = saveButtonY + (2 * BUTTON_HEIGHT);
    Rectangle saveButton = { BUTTON_START, saveButtonY, BUTTON_LENGTH, BUTTON_HEIGHT };
    Rectangle exitButton = { BUTTON_START, exitButtonY, BUTTON_LENGTH, BUTTON_HEIGHT };
    Rectangle loadButton = { 25, 500, BUTTON_LENGTH, BUTTON_HEIGHT };
    Rectangle newButton = { 25, 400, BUTTON_LENGTH, BUTTON_HEIGHT };
    Texture2D background = LoadTexture(BACKGROUND_TEXTURE);
    background.width = BOARD_LENGTH;
    background.height = BOARD_HEIGHT;

    bool flag = 0, win = 0;
    Vector2 mouse;

    //HOME MENU
    while (true) {
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            mouse = GetMousePosition();
            if (CheckCollisionPointRec(mouse, newButton)) break;
            if (CheckCollisionPointRec(mouse, loadButton)) {
                flag = 1;
                break;
            }
        }
        BeginDrawing();
        DrawTexture(background, 0, 0, WHITE);
        DrawRectangleRec(newButton, GRAY);
        DrawText(NEW_TEXT, (int)newButton.x + 5, (int)newButton.y + 5, BUTTON_FONT, WHITE);
        DrawRectangleRec(loadButton, GRAY);
        DrawText(LOAD_TEXT, (int)loadButton.x + 5, (int)loadButton.y + 5, BUTTON_FONT, WHITE);
        EndDrawing();
    }
    UnloadTexture(background);
    CloseWindow();

    //SOLITAIRE WINDOW
    InitWindow(BOARD_LENGTH, BOARD_HEIGHT, "Solitaire");
    SetTargetFPS(60);

    //INITIALISING THE MASTER OCTOPUS
    Board& octopus = Board::getInstance();
    octopus.randomise();
    octopus.initialise();
    octopus.position();
    if (flag) octopus.loadGame();

    //GAMELOOP
    while (!WindowShouldClose()) {
        if (octopus.checkWin()) {
            win = 1;
            break;
        }
        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
            octopus.setMouse(GetMousePosition());
            if (CheckCollisionPointRec(octopus.getMouse(), saveButton)) {
                try {
                    octopus.saveGame();
                }
                catch (const char* error) {
                    octopus.logError(ERROR_FILE);
                }
                break;
            }
            if (CheckCollisionPointRec(octopus.getMouse(), exitButton)) {
                break;
            }
        }
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
        
        BeginDrawing();
        ClearBackground(GREEN);

        octopus.draw();

        DrawRectangleRec(saveButton, GRAY);
        DrawText(SAVE_TEXT, (int)saveButton.x, (int)saveButton.y, BUTTON_FONT, WHITE);
        DrawRectangleRec(exitButton, GRAY);
        DrawText(EXIT_TEXT, (int)exitButton.x, (int)exitButton.y, BUTTON_FONT, WHITE);

        EndDrawing();
    }

    //CLEAN-UP
    octopus.destroy();
    CloseWindow();
    return 0;
}