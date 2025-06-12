#include "FREE_CELL.h"

FreeCell::FreeCell() : Cell() {}

FreeCell::FreeCell(const int cap, const char* path) : Cell(cap, path) {}

FreeCell::~FreeCell() { 
	empty(); 
	unload(); 
}

bool FreeCell::stackAllowed(Card* obj) { return 1; }