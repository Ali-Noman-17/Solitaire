#include "HEARTS.h"

Hearts::Hearts() : RedCard() {}

Hearts::Hearts(int val, char name, const char* path) : RedCard(val, name, path) {}

Hearts::~Hearts() { unload(); }

char Hearts::getSuit() { return SUIT_HEARTS; }