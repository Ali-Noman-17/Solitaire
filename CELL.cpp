#include "CELL.h"

Cell::Cell() : cap(0), num(0), arr(nullptr), face(), xy{ 0,0 } {}

Cell::Cell(const int cap, const char* path) : cap(cap), num(0), arr(new Card* [cap]) {
	face = LoadTexture(path);
	xy = { 0,0 };
}

Cell::~Cell() { delete[] arr; }

int Cell::getNum() { return num; }

int Cell::getCap() { return cap; }

char Cell::getLatestColour() { return arr[num - 1]->getColour(); }

bool Cell::isEmpty() { return (num == 0); }

void Cell::move(const float x, const float y) { xy = { x, y }; }

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
			arr[i]->draw();
		}
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