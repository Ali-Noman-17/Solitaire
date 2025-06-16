#include "ALTERNATE_CELL.h"

AlternateCell::AlternateCell() : Cell() {}

AlternateCell::AlternateCell(const int cap, const char* path) : Cell(cap, path) {}

AlternateCell::~AlternateCell() {
	empty();
	unload();
}

void AlternateCell::draw() { 
	drawCascade(); 
	int num = getNum();
	float height = ((num - 1) * STACK_WIDTH) + CARD_HEIGHT;
	updateHitBox(CELL_WIDTH, height);
}

bool AlternateCell::stackAllowed(Card* obj) {
	if (isEmpty()) return 1;
	if (obj->getColour() == getLatestColour()) return 0;
	if (getTopCard()->canStackAsc(obj)) return 1;
	else return 0;
}