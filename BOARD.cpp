#include "BOARD.h"

Board::Board() : randoms(new int[NUMBER_CARDS]), num(NUMBER_CARDS), score(0), 
play(ALTERNATE_DIVISION_NUM, ALTERNATE_DIVISION_TEXTURE, DIVISION_WIDTH_PLAY, DIVISION_HEIGHT_PLAY),
suits(SUIT_DIVISION_NUM, SUIT_DIVISION_TEXTURE, DIVISION_WIDTH_SUITS, DIVISION_HEIGHT_SUITS), 
pool(POOL_DIVISION_NUM, POOL_DIVISION_TEXTURE, DIVISION_WIDTH_POOL, DIVISION_HEIGHT_POOL),
deck(new Card* [NUMBER_CARDS]) {
}

Board::~Board() { 
	for (int i = 0; i < NUMBER_CARDS; i++) { delete deck[i]; }
	delete[] deck;
	delete[] randoms;
}

void Board::initDeck() {
	int preset = 0;
	for (int i = 0; i < NUMBER_VALS; i++) {
		string path = pathConctructor(CARD_VALUES[i], SUIT_SPADES);
		deck[preset + i] = new Spades(i + 1, CARD_VALUES[i], path.data());
	}
	preset += NUMBER_VALS;
	for (int i = 0; i < NUMBER_VALS; i++) {
		string path = pathConctructor(CARD_VALUES[i], SUIT_CLUBS);
		deck[preset + i] = new Clubs(i + 1, CARD_VALUES[i], path.data());
	}
	preset += NUMBER_VALS;
	for (int i = 0; i < NUMBER_VALS; i++) {
		string path = pathConctructor(CARD_VALUES[i], SUIT_HEARTS);
		deck[preset + i] = new Hearts(i + 1, CARD_VALUES[i], path.data());
	}
	preset += NUMBER_VALS;
	for (int i = 0; i < NUMBER_VALS; i++) {
		string path = pathConctructor(CARD_VALUES[i], SUIT_DIAMONDS);
		deck[preset + i] = new Diamonds(i + 1, CARD_VALUES[i], path.data());
	}
}

void Board::initPlay() {
	for (int i = 0; i < ALTERNATE_DIVISION_NUM; i++) {
		for (int j = 0; j < i + 1; j++) {
			int index = getRandom();
			play.addToCell(deck[index], i);
		}
	}
}

void Board::initSuits() { 
	suits.defSuitCells(); 
}

void Board::initPool() {
	int size = num;
	for (int i = 0; i < size; i++) {
		int index = getRandom();
		pool.addToCell(deck[index], POOL_LOCKED_CELL);
	}
}

void Board::initialise() {
	initDeck();
	initPlay();
	initPool();
	initSuits();
}

void Board::position() {
	positionPool();
	positionSuits();
	positionPlay();
}

void Board::positionPlay() {
	float y = (2 * VERT_WIDTH) * CELL_HEIGHT;
	play.move(0, y);
	play.updateHitBox();
	play.positionCells();
}

void Board::positionSuits() {
	float x = (3 * SPACER_WIDTH) + (3 * CELL_WIDTH);
	suits.move(x, 0);
	suits.updateHitBox();
	suits.positionCells();
}

void Board::positionPool() {
	pool.move(0, 0);
	pool.updateHitBox();
	pool.positionCells();
}

void Board::addScore() { score += SCORE_INCREMENT; }

bool Board::checkWin() { 
	for (int i = 0; i < NUMBER_SUITS; i++) {
		if (suits.getCellNum(i) < NUMBER_CARDS) return 0;
	}
	return 1;
}

void Board::randomise() {
	for (int i = 0; i < NUMBER_CARDS; i++) {
		randoms[i] = i;
	}
	for (int i = NUMBER_CARDS - 1; i > 0; i--) {
		int j = GetRandomValue(0, i);
		std::swap(randoms[i], randoms[j]);
	}
}

int Board::getRandom() {
	int random = randoms[num];
	num--;
	return random;
}

string Board::pathConctructor(const char name, const char suit) {
	string dash = "-";
	string path = FRONT_TEXTURE_PREFIX + name + dash + FRONT_TEXTURE_SUFFIX;
	return  path;
}