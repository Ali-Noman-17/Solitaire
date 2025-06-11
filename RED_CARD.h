#ifndef RED_CARD_H
#define RED_CARD_H

#include "CARD.h"

class RedCard : public Card {
public:
	RedCard();
	RedCard(int val, char name, const char*);
	virtual ~RedCard();
	virtual char getSuit() = 0;
	char getColour();
};


#endif RED_CARD_H