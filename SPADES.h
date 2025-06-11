#ifndef SPADES_H
#define SPADES_H

#include "BLACK_CARD.h"

class Spades : public BlackCard {
public:
	Spades();
	Spades(int val, char name, const char* path);
	~Spades();
	char getSuit();
};

#endif SPADES_H