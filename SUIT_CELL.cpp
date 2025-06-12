#include "SUIT_CELL.h"

SuitCell::SuitCell() : Cell() , suit('\0') {}

SuitCell::SuitCell(const int cap, const char* path, const char suit) : Cell(cap, path), suit(suit) {}

SuitCell::~SuitCell() {
	empty();
	unload();
}

bool SuitCell::stackAllowed(Card* obj) {
	if (obj->getSuit() == suit) return 1;
	else return 0;
}