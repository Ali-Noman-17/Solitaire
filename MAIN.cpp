#include "BOARD.h"
#include "BUTTON.h"


int main()
{
    //HOME WINDOW
    InitWindow(BOARD_LENGTH, BOARD_HEIGHT, "Solitaire MENU");
    SetTargetFPS(60);

    //HOME MENU UI STUFF
    float saveButtonY = DIVISION_HEIGHT_SUITS + BUTTON_HEIGHT;
    float exitButtonY = saveButtonY + (2 * BUTTON_HEIGHT);

    Button saveButton(BUTTON_START, saveButtonY, BUTTON_WIDTH, BUTTON_HEIGHT, SAVE_TEXT);
    Button exitButton(BUTTON_START, exitButtonY, BUTTON_WIDTH, BUTTON_HEIGHT, EXIT_TEXT);
    Button newButton(25, 400, BUTTON_WIDTH, BUTTON_HEIGHT, NEW_TEXT);
    Button loadButton(25, 500, BUTTON_WIDTH, BUTTON_HEIGHT, LOAD_TEXT);

    Texture2D background = LoadTexture(BACKGROUND_TEXTURE);
    background.width = BOARD_LENGTH;
    background.height = BOARD_HEIGHT;

    bool flag = 0, win = 0;
    Vector2 mouse;

    //HOME MENU
    while (true) {
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            mouse = GetMousePosition();
            if (CheckCollisionPointRec(mouse, newButton.getHitBox())) break;
            if (CheckCollisionPointRec(mouse, loadButton.getHitBox())) {
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
        saveButton.draw();
        exitButton.draw();
        EndDrawing();
    }

    //CLEAN-UP
    octopus.destroy();
    CloseWindow();
    return 0;
}