#include "BOARD.h"

Board* Board::instance = nullptr;

Board::Board() : randoms(new int[NUMBER_CARDS]), num(NUMBER_CARDS), score(0), 
play(ALTERNATE_DIVISION_NUM, ALTERNATE_DIVISION_TEXTURE, DIVISION_WIDTH_PLAY, DIVISION_HEIGHT_PLAY),
suits(SUIT_DIVISION_NUM, SUIT_DIVISION_TEXTURE, DIVISION_WIDTH_SUITS, DIVISION_HEIGHT_SUITS), 
pool(POOL_DIVISION_NUM, POOL_DIVISION_TEXTURE, DIVISION_WIDTH_POOL, DIVISION_HEIGHT_POOL),
deck(new Card* [NUMBER_CARDS]), mouse{0,0}, source(), target(), logger(LOG_FILE), isMousePressed(0) {}

Board::~Board() { 
	for (int i = 0; i < NUMBER_CARDS; i++) { delete deck[i]; }
	delete[] deck;
	delete[] randoms;
}

void Board::destroy() { delete instance; }

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
	play.flipTops();
}

void Board::initSuits() {}

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
	float y = DIVISION_HEIGHT_POOL;
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

void Board::pickCard() {
	recordInput(source);
	if (!source.isDataComplete) throw ERROR_INVALID;
	//pool moves
	if (source.divNum == POOL && source.cellNum == POOL_LOCKED_CELL) {
		if (!source.cell->isEmpty()) {
			pool.reveal();
			source.isDataComplete = 0;
		}
		else if (!pool.getCellRef(POOL_AVAILABLE_CELL)->isEmpty()) {
			pool.cycleBack();
			source.isDataComplete = 0;
		}
		else throw ERROR_INVALID;
	}
}

void Board::setCard() {
	recordInput(target);
	if (!target.isDataComplete) throw ERROR_INVALID;
	if (!inputSetAllowed()) throw ERROR_INVALID;
	if (target.divNum == POOL) throw ERROR_INVALID;
	//suits move
	if (target.divNum == SUITS) {
		if (source.divNum == POOL || source.divNum == PLAY) {
			if (!source.cell->isTopCard(source.card)) throw ERROR_INVALID;
			suits.moveToCell(source.card, source.cell, target.cell);
		}
		else if (source.divNum == SUITS) throw ERROR_INVALID;
	}
	//play move
	if (target.divNum == PLAY) {
		if (source.divNum == SUITS && source.cardNum == -1) throw ERROR_INVALID;
		if (source.divNum == POOL || source.divNum == SUITS) {
			if (!source.cell->isTopCard(source.card)) throw ERROR_INVALID;
			play.moveToCell(source.card, source.cell, target.cell);
		}
		else if (source.divNum == PLAY) play.moveToCell(source.card, source.cell, target.cell);
	}

}

void Board::logError(string error) {
	logger.writeError(error);
}

void Board::draw() {
	play.draw();
	suits.draw();
	pool.draw();
}

void Board::recordInput(InputRecorder& rec) {
	if (rec.divNum == -1) recordPoolCollision(rec);
	if (rec.divNum == -1) recordSuitsCollision(rec);
	if (rec.divNum == -1) recordPlayCollision(rec);
}

void Board::recordPlayCollision(InputRecorder& rec) {
	for (int i = 0; i < ALTERNATE_DIVISION_NUM; i++) {
		if (CheckCollisionPointRec(mouse, play.getCellHitBox(i))) {
			rec.cell = play.getCellRef(i);
			rec.cellNum = i;
			rec.divNum = PLAY;
			break;
		}
	}
	if (rec.cell == nullptr) throw ERROR_INVALID;
	for (int i = 0; i < rec.cell->getNum(); i++) {
		if (CheckCollisionPointRec(mouse, rec.cell->getCardHitBox(i))) {
			rec.card = rec.cell->getCard(i);
			rec.cardNum = i;
			rec.dataCompleted();
			return;
		}
	}
}

void Board::recordSuitsCollision(InputRecorder& rec){
	for (int i = 0; i < SUIT_DIVISION_NUM; i++) {
		if (CheckCollisionPointRec(mouse, suits.getCellHitBox(i))) {
			rec.cell = suits.getCellRef(i);
			rec.cellNum = i;
			rec.divNum = SUITS;
			break;
		}
	}
	if (rec.cell == nullptr) return;
	if (!rec.cell->isEmpty()) {
		rec.card = rec.cell->getTopCard();
		rec.cardNum = rec.cell->getNum() - 1;
	}
	rec.dataCompleted();
}

void Board::recordPoolCollision(InputRecorder& rec){
	for (int i = 0; i < POOL_DIVISION_NUM; i++) {
		if (CheckCollisionPointRec(mouse, pool.getCellHitBox(i))) {
			rec.cell = pool.getCellRef(i);
			rec.cellNum = i;
			rec.divNum = POOL;
			break;
		}
	}
	if (rec.cellNum == -1) return;
	if (rec.cellNum == POOL_LOCKED_CELL) rec.dataCompleted();
	if (rec.cellNum == POOL_AVAILABLE_CELL) {
		if (!rec.cell->isEmpty()) {
			rec.card = rec.cell->getTopCard();
			rec.cardNum = rec.cell->getNum() - 1;
			rec.dataCompleted();
		}
	}
	return;
}

void Board::resetInputs() {
	source.flushVals();
	target.flushVals();
}

bool Board::inputSetAllowed(){
	if (source.cell == target.cell) return 0;
	else return 1;
}

bool Board::isSourceComplete() { return source.isDataComplete; }

void Board::saveGame() {
	ofstream file(SAVE_FILE);
	if (!file.is_open()) throw ERROR_FILE;
	save(file);
	file.close();
}

void Board::loadGame() {
	ifstream file(SAVE_FILE);
	if (!file.is_open()) throw ERROR_FILE;
	load(file);
	file.close();
}

void Board::save(ofstream& file) {
	file.write((char*)&num, sizeof(int));
	file.write((char*)&score, sizeof(int));
	file.write((char*)&mouse.x, sizeof(float));
	file.write((char*)&mouse.y, sizeof(float));
	file.write((char*)&isMousePressed, sizeof(bool));
	play.save(file);
	suits.save(file);
	pool.save(file);
}

void Board::load(ifstream& file) {
	file.read((char*)&num, sizeof(int));
	file.read((char*)&score, sizeof(int));
	file.read((char*)&mouse.x, sizeof(float));
	file.read((char*)&mouse.y, sizeof(float));
	file.read((char*)&isMousePressed, sizeof(bool));
	play.load(file, deck);
	suits.load(file, deck);
	pool.load(file, deck);
}

bool Board::canLoad() {
	ifstream file(SAVE_FILE, std::ios::binary | std::ios::ate);
	return file.tellg() > 0;
}

void Board::addScore() { score += SCORE_INCREMENT; }

void Board::setMouse(Vector2 mouseCoords) {
	mouse.x = mouseCoords.x;
	mouse.y = mouseCoords.y;
}

Vector2 Board::getMouse() { return mouse; }

bool Board::mousePress() { return isMousePressed; }

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
	int random = randoms[num - 1];
	num--;
	return random;
}

string Board::pathConctructor(const char name, const char suit) {
	string pre = "./sprites/";
	string dash = "-";
	string suf = ".jpg";
	string path = pre + name + dash + suit + suf;
	return  path;
}