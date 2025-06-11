#ifndef CLUBS_H
#define CLUBS_H

#include "BLACK_CARD.h"

class Clubs : public BlackCard {
public:
	Clubs();
	Clubs(int val, char name, const char* path);
	~Clubs();
	char getSuit();
};

#endif CLUBS_H