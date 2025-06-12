#ifndef FREE_CELL
#define FREE_CELL

#include "CELL.h"

class FreeCell : public Cell {
public:
	FreeCell();
	FreeCell(const int cap, const char* path);
	~FreeCell();
	bool stackAllowed(Card* obj);
};
#endif FREE_CELL