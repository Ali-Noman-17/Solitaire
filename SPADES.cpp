#include "SPADES.h"

Spades::Spades(): BlackCard() {}

Spades::Spades(int val, char name, const char* path): BlackCard(val, name, path) {}

Spades::~Spades() { unload(); }

char Spades::getSuit() { return SUIT_SPADES; }