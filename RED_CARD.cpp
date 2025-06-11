#include "RED_CARD.h"

RedCard::RedCard(): Card() {}

RedCard::RedCard(int val, char name, const char* path): Card(val,name,path) {}

char RedCard::getColour() { return RED_CARD_COLOUR; }