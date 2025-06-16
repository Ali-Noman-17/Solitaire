#ifndef BOARD_H
#define BOARD_H

#include <iostream>
#include <string>
#include <raylib.h>
#include "INPUT_RECORDER.h"
#include "LOGGER.h"
using namespace std;

#define ERROR_FILE "Couldn't open file"
#define ERROR_INVALID "Invalid move attempted"
#define LOG_FILE "logData.txt"
#define CARD_VALUES "A23456789TJQK"
#define SAVE_TEXT "Save & Exit"
#define EXIT_TEXT "Exit"
#define NEW_TEXT "New Game"
#define LOAD_TEXT "Load Game"
#define SCORE_INCREMENT 5
#define BOARD_LENGTH 1000
#define BOARD_HEIGHT 800
#define BUTTON_LENGTH 200
#define BUTTON_HEIGHT 50
#define BUTTON_START 762
#define BUTTON_FONT 28


class Board {
	static Board* instance;
	int* randoms;
	int num;
	int score;
	Division<AlternateCell> play;
	Division<SuitCell> suits;
	Division<FreeCell> pool;
	Card** deck;
	Vector2 mouse;
	InputRecorder source;
	InputRecorder target;
	Logger logger;
	bool isMousePressed;
	
	Board();
	~Board();
	Board(const Board& obj) = delete;
	Board& operator=(const Board& obj) = delete;
public:
	static Board& getInstance() {
		if (instance == nullptr) instance = new Board();
		return *instance;
	}
	void destroy();

	void initialise();
	void initDeck();
	void initPlay();
	void initSuits();
	void initPool();

	void position();
	void positionPlay();
	void positionSuits();
	void positionPool();

	void pickCard();
	void setCard();
	void logError(string error);
	void draw();
	
	void recordInput(InputRecorder& rec);
	void recordPlayCollision(InputRecorder& rec);
	void recordSuitsCollision(InputRecorder& rec);
	void recordPoolCollision(InputRecorder& rec);
	void resetInputs();
	bool inputSetAllowed();
	bool isSourceComplete();

	void saveGame();
	void loadGame();
	void save(ofstream& file);
	void load(ifstream& file);
	bool canLoad();

	void setMouse(Vector2 mouseCoords);
	bool mousePress();
	Vector2 getMouse();

	bool checkWin();
	void addScore();
	void randomise();
	int getRandom();
	string pathConctructor(const char name, const char suit);
};

#endif BOARD_H