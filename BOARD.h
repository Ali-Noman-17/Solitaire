#ifndef BOARD_H
#define BOARD_H

#include <iostream>
#include <string>
#include <raylib.h>
#include "INPUT_RECORDER.h"
#include "LOGGER.h"
using namespace std;

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
	Rectangle highlight;
	
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
	void setHighlight();
	void resetHighlight();
	bool inputSetAllowed();
	bool isSourceComplete();

	void saveGame();
	void loadGame();
	void save(ofstream& file);
	void load(ifstream& file);
	bool canLoad();

	void setMouse(Vector2 mouseCoords);
	Vector2 getMouse();

	int getScore();
	void addScore();
	void subScore();
	bool checkWin();
	void randomise();
	int getRandom();
	string pathConctructor(const char name, const char suit);
};

#endif BOARD_H