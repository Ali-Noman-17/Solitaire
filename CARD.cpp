#include "CARD.h"

Card::Card() : value(0), name('\0'), flipped(0), front(), face(), xy{ 0,0 }, 
hitBox{ xy.x,xy.y,CARD_WIDTH,CARD_HEIGHT } {}

Card::Card(int val, char name, const char* path) :value(val), name(name), flipped(0), front(path),
hitBox{ xy.x,xy.y,CARD_WIDTH,CARD_HEIGHT } {
	face = LoadTexture(BACK_TEXTURE);
	xy = { 0,0 };
}

Card::~Card() {}

int Card::getValue() { return value; }

char Card::getName() { return name; }

Rectangle Card::getHitBox() { return hitBox; }

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

void Card::move(const float x, const float y) { xy = { x,y }; }

void Card::updateHitBox() { hitBox = { xy.x,xy.y, hitBox.width, hitBox.height }; }

void Card::updateHitBox(const float width, const float height) { hitBox = { xy.x,xy.y,width,height }; }

void Card::unload(){ UnloadTexture(face); }