#ifndef HEARTS_H
#define HEARTS_H

#include "RED_CARD.h"

class Hearts : public RedCard {
public:
	Hearts();
	Hearts(int val, char name, const char* path);
	~Hearts();
	char getSuit();
};

#endif HEARTS_H