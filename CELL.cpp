#include "CELL.h"

Cell::Cell() : cap(0), num(0), arr(nullptr), face(), xy{ 0,0 }, hitBox{ xy.x,xy.y,CELL_WIDTH,CELL_HEIGHT } {}

Cell::Cell(const int cap, const char* path) : cap(cap), num(0), arr(new Card* [cap]),
hitBox{ xy.x,xy.y,CELL_WIDTH,CELL_HEIGHT } {
	face = LoadTexture(path);
	xy = { 0,0 };
}

Cell::~Cell() { delete[] arr; }

int Cell::getNum() { return num; }

int Cell::getCap() { return cap; }

char Cell::getLatestColour() { return arr[num - 1]->getColour(); }

Rectangle Cell::getHitBox() { return hitBox; }

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
	num++;
}

void Cell::remove(Card* obj) { num--; }

Card* Cell::getCard(const int i) {
	if (i <= num) return arr[i];
}