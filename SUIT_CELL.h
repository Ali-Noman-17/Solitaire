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
	void save(ofstream& file) override;
	void load(ifstream& file, Card** deck) override;
};
#endif SUIT_CELL