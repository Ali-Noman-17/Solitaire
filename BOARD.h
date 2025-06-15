#ifndef BOARD_H
#define BOARD_H

#include <iostream>
#include <string>
#include <raylib.h>
#include "INPUT_RECORDER.h"
using namespace std;

#define CARD_VALUES "A23456789TJQK"
#define SCORE_INCREMENT 5
#define BOARD_LENGTH 1000
#define BOARD_HEIGHT 800

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
	
	void recordInput(InputRecorder rec);
	void recordPlayCollision(InputRecorder rec);
	void recordSuitsCollision(InputRecorder rec);
	void recordPoolCollision(InputRecorder rec);
	void resetInputs();
	bool inputSetAllowed();

	void saveGame(ofstream& file);
	void loadGame(ifstream& file);

	bool checkWin();
	void addScore();
	void randomise();
	int getRandom();
	string pathConctructor(const char name, const char suit);
};

#endif BOARD_H