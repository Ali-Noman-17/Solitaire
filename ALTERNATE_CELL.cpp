#include "ALTERNATE_CELL.h"

AlternateCell::AlternateCell() : Cell() {}

AlternateCell::AlternateCell(const int cap, const char* path) : Cell(cap, path) {}

AlternateCell::~AlternateCell() {
	empty();
	unload();
}

bool AlternateCell::stackAllowed(Card* obj) {
	if (getNum() == 0) return 1;
	if (obj->getColour() == getLatestColour()) return 0;
	else return 1;
}