#ifndef SUIT_CELL
#define SUIT_CELL

#include "CELL.h"

class SuitCell : public Cell {
	char suit;
public:
	SuitCell();
	SuitCell(const int cap, const char* path, const char suit);
	~SuitCell();
	bool stackAllowed(Card* obj) override;
};
#endif SUIT_CELL