#include "DIAMONDS.h"

Diamonds::Diamonds() : RedCard() {}

Diamonds::Diamonds(int val, char name, const char* path) : RedCard(val, name, path) {}

Diamonds::~Diamonds() { unload(); }
char Diamonds::getSuit() { return SUIT_DIAMONDS; }