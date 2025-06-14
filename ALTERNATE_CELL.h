#ifndef ALTERANTE_CELL
#define ALTERNATE_CELL

#include "CELL.h"

class AlternateCell : public Cell {
public:
	AlternateCell();
	AlternateCell(const int cap, const char* path);
	~AlternateCell();
	void draw() override;
	bool stackAllowed(Card* obj) override;
};
#endif ALTERNATE_CELL