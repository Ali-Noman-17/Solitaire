#ifndef DIAMONDS_H
#define DIAMONDS_H

#include "RED_CARD.h"

class Diamonds : public RedCard {
public:
	Diamonds();
	Diamonds(int val, char name, const char* path);
	~Diamonds();
	char getSuit();
};

#endif DIAMONDS_H