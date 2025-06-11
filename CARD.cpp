#include "CARD.h"

Card::Card() : value(0), name('\0'), flipped(0), front(), face(), xy{ 0,0 } {}

Card::Card(int val, char name, const char* path) :value(val), name(name), flipped(0), front(path) {
	face = LoadTexture(BACK_TEXTURE);
	xy = { 0,0 };
}

Card::~Card() {}

int Card::getValue() { return value; }

char Card::getName() { return name; }

void Card::flip() {
	flipped = (flipped + 1) % 2;
	if (isFlipped()) {
		UnloadTexture(face);
		face = LoadTexture(front.data());
	}
	else {
		UnloadTexture(face);
		face = LoadTexture(BACK_TEXTURE);
	}
}

bool Card::isFlipped() { return flipped; }

bool Card::canStack(Card* obj) { return (obj->value == value - 1); }

void Card::draw() { DrawTextureEx(face, xy, CARD_ROTATION, CARD_SCALE, CARD_TINT); }

void Card::move(const int x, const int y) { xy = { (float)x, (float)y }; }

void Card::unload(){ UnloadTexture(face); }