#include "CLUBS.h"

Clubs::Clubs(): BlackCard() {}

Clubs::Clubs(int val, char name, const char* path) : BlackCard(val, name, path) {}

Clubs::~Clubs() { unload(); }

char Clubs::getSuit() { return SUIT_CLUBS; }