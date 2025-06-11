#include "BLACK_CARD.h"

BlackCard::BlackCard() : Card() {}

BlackCard::BlackCard(int val, char name, const char* path): Card(val, name, path) {}

char BlackCard::getColour() { return BLACK_CARD_COLOUR; }