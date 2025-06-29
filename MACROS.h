#ifndef MACROS_H
#define MACROS_H

//TEXTURES
#define FRONT_TEXTURE_PREFIX "./sprites/"
#define CARD_VALUES "A23456789TJQK"
#define FRONT_TEXTURE_SUFFIX ".jpg"
#define BACK_TEXTURE "./sprites/texture-back.jpg"
#define CELL_TEXTURE "./sprites/texture-cell.jpg"
#define SPADES_CELL_TEXTURE "./sprites/texture-cell-S.jpg"
#define CLUBS_CELL_TEXTURE "./sprites/texture-cell-C.jpg"
#define HEARTS_CELL_TEXTURE "./sprites/texture-cell-H.jpg"
#define DIAMONDS_CELL_TEXTURE "./sprites/texture-cell-D.jpg"
#define ALTERNATE_DIVISION_TEXTURE "./sprites/texture-alt-div.jpg"
#define SUIT_DIVISION_TEXTURE "./sprites/texture-suit-div.jpg"
#define POOL_DIVISION_TEXTURE "./sprites/texture-pool-div.jpg"
#define BACKGROUND_TEXTURE "./sprites/texture-bg.jpg"
#define WIN_TEXTURE "./sprites/texture-win.jpg"

//CHARACTERS
#define RED_CARD_COLOUR 'R'
#define BLACK_CARD_COLOUR 'B'
#define SUIT_SPADES 'S'
#define SUIT_CLUBS 'C'
#define SUIT_HEARTS 'H'
#define SUIT_DIAMONDS 'D'

//STRINGS
#define SAVE_FILE "SAVED_DATA.bin"
#define LOG_FILE "logData.txt"
#define ERROR_FILE "Couldn't open file"
#define ERROR_INVALID "Invalid move attempted"
#define SAVE_TEXT "Save & Exit"
#define EXIT_TEXT "Exit"
#define PAUSE_TEXT "Pause"
#define RESUME_TEXT "Resume"
#define NEW_TEXT "New Game"
#define LOAD_TEXT "Load Game"
#define BACK_TEXT "Back to Menu"

//DIMENSIONS-PIXELS
#define CARD_WIDTH 75
#define CARD_HEIGHT 112.5
#define CARD_HEIGHT_STACKED 22.5
#define CELL_WIDTH 75
#define CELL_HEIGHT 112.5
#define SPACER_WIDTH 25
#define VERT_WIDTH 20
#define STACK_WIDTH 25
#define DIVISION_WIDTH_PLAY 725
#define DIVISION_WIDTH_POOL 300
#define DIVISION_WIDTH_SUITS 425
#define DIVISION_HEIGHT_PLAY 645
#define DIVISION_HEIGHT_POOL 153
#define DIVISION_HEIGHT_SUITS 153
#define BOARD_WIDTH 1000
#define BOARD_HEIGHT 800
#define BUTTON_WIDTH 200
#define BUTTON_HEIGHT 50
#define BUTTON_START 762
#define BUTTON_FONT 28

//NUMBERS
#define NUMBER_CARDS 52
#define POOL 1
#define SUITS 2
#define PLAY 3
#define NUMBER_VALS 13
#define NUMBER_SUITS 4
#define NUMBER_POOL 24
#define ALTERNATE_DIVISION_NUM 7
#define SUIT_DIVISION_NUM 4
#define POOL_DIVISION_NUM 2
#define POOL_SIZE 16
#define POOL_LOCKED_CELL 0
#define POOL_AVAILABLE_CELL 1
#define SCORE_INCREMENT 5

//MISC
#define CARD_ROTATION 0.00
#define CARD_SCALE 1.00
#define CARD_TINT WHITE
#define CELL_ROTATION 0.00
#define CELL_SCALE 1.00
#define CELL_TINT WHITE
#define CAP_INCREMENT 5
#define DIVISION_ROTATION 0.00
#define DIVISION_SCALE 1.00
#define DIVISION_TINT WHITE

#endif MACROS_H