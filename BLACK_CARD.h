#ifndef BLACK_CARD_H
#define BLACK_CARD_H

#include "CARD.h"

class BlackCard : public Card {
public:
	BlackCard();
	BlackCard(int val, char name, const char* path);
	virtual ~BlackCard() = 0;
	virtual char getSuit() = 0;
	char getColour();
};


#endif BLACK_CARD_H