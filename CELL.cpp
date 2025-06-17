#include "CELL.h"

Cell::Cell() : cap(0), num(0), arr(nullptr), face(), xy{ 0,0 }, hitBox{ xy.x,xy.y,CELL_WIDTH,CELL_HEIGHT } {}

Cell::Cell(const int cap, const char* path) : cap(cap), num(0), arr(new Card* [cap]), face(), xy{0,0},
hitBox{ xy.x,xy.y,CELL_WIDTH,CELL_HEIGHT } {
	face = LoadTexture(path);
	xy = { 0,0 };
	face.width = hitBox.width;
	face.height = hitBox.height;
}

Cell::~Cell() {}

int Cell::getNum() { return num; }

int Cell::getCap() { return cap; }

char Cell::getLatestColour() { return arr[num - 1]->getColour(); }

Rectangle Cell::getHitBox() { return hitBox; }

Rectangle Cell::getCardHitBox(const int index) { return arr[index]->getHitBox(); }

Rectangle Cell::getTopCardHitBox() { return arr[num - 1]->getHitBox(); }

bool Cell::isEmpty() { return (num == 0); }

void Cell::move(const float x, const float y) { xy = { x, y }; }

void Cell::updateHitBox() { hitBox = { xy.x,xy.y, hitBox.width, hitBox.height }; }

void Cell::updateHitBox(const float width, const float height) { hitBox = { xy.x,xy.y,width,height }; }

void Cell::alignCards() {
	for (int i = 0; i < num; i++) {
		arr[i]->move(xy.x, xy.y);
	}
}

void Cell::empty() { delete[] arr; }

void Cell::unload() { UnloadTexture(face); }

void Cell::draw() {
	if (num == 0) drawEmpty();
	else arr[num - 1]->draw();
}

void Cell::drawCascade() {
	if (num == 0) drawEmpty();
	else {
		for (int i = 0; i < num; i++) {
			int yShift = xy.y + (i * STACK_WIDTH);
			arr[i]->move(xy.x, yShift);
			arr[i]->updateHitBox(CARD_WIDTH, CARD_HEIGHT_STACKED);
			if (i == num - 1 && !arr[i]->isFlipped()) arr[i]->flip();
			arr[i]->draw();
		}
		arr[num - 1]->updateHitBox(CARD_WIDTH, CARD_HEIGHT);
	}
}

void Cell::drawEmpty() { DrawTextureEx(face, xy, CELL_ROTATION, CELL_SCALE, CELL_TINT); }

void Cell::flipTop() { arr[num - 1]->flip(); }

void Cell::increaseCap() {
	Card** temp = new Card * [cap + CAP_INCREMENT];
	for (int i = 0; i < cap; i++) { temp[i] = arr[i]; }
	delete[] arr;
	arr = temp;
	cap += CAP_INCREMENT;
}

void Cell::add(Card* obj) {
	if (num == cap) increaseCap();
	arr[num] = obj;
	arr[num]->move(xy.x, xy.y);
	num++;
}

void Cell::remove(Card* obj) { num--; }

bool Cell::isTopCard(Card* obj) {
	if (arr[num - 1] == obj) return 1;
	else return 0;
}

Card* Cell::getCard(const int index) {
	if (index <= num) return arr[index];
}

Card* Cell::getTopCard() {
	return arr[num - 1];
}

void Cell::savePrimitives(ofstream& file) {
	file.write((char*)&cap, sizeof(int));
	file.write((char*)&num, sizeof(int));
	file.write((char*)&xy.x, sizeof(float));
	file.write((char*)&xy.y, sizeof(float));
	file.write((char*)&hitBox.width, sizeof(float));
	file.write((char*)&hitBox.height, sizeof(float));
}

void Cell::loadPrimitives(ifstream& file) {
	file.read((char*)&cap, sizeof(int));
	file.read((char*)&num, sizeof(int));
	file.read((char*)&xy.x, sizeof(float));
	file.read((char*)&xy.y, sizeof(float));
	hitBox.x = xy.x;
	hitBox.y = xy.y;
	file.read((char*)&hitBox.width, sizeof(float));
	file.read((char*)&hitBox.height, sizeof(float));
}

void Cell::saveCards(ofstream& file) {
	for (int i = 0; i < num; i++) {
		char name = arr[i]->getName();
		char suit = arr[i]->getSuit();
		bool flipped = arr[i]->isFlipped();
		file.write((char*)&name, sizeof(char));
		file.write((char*)&suit, sizeof(char));
		file.write((char*)&flipped, sizeof(bool));
	}
}

void Cell::loadCards(ifstream& file, Card** deck) {
	delete[] arr;
	arr = new Card * [cap];
	for (int i = 0; i < num; i++) {
		char name, suit;
		bool flipped;
		file.read((char*)&name, sizeof(char));
		file.read((char*)&suit, sizeof(char));
		file.read((char*)&flipped, sizeof(bool));

		for (int j = 0; j < 52; j++) {
			if (deck[j]->getName() == name && deck[j]->getSuit() == suit) {
				arr[i] = deck[j];
				arr[i]->setFlip(flipped);
				arr[i]->move(xy.x, xy.y);
			} 
		}
	}
}

void Cell::save(ofstream& file) {
	savePrimitives(file);
	saveCards(file);
}

void Cell::load(ifstream& file, Card** deck) {
	loadPrimitives(file);
	loadCards(file, deck);
}