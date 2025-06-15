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

void Card::setFlip(bool flip) { flipped = flip; }

bool Card::isFlipped() { return flipped; }

bool Card::canStackAsc(Card* obj) { return (obj->value == value - 1); }

bool Card::canStackDsc(Card* obj) { return (obj->value == value + 1); }


void Card::draw() { DrawTextureEx(face, xy, CARD_ROTATION, CARD_SCALE, CARD_TINT); }

void Card::move(const float x, const float y) { xy = { x,y }; }

void Card::updateHitBox() { hitBox = { xy.x,xy.y, hitBox.width, hitBox.height }; }

void Card::updateHitBox(const float width, const float height) { hitBox = { xy.x,xy.y,width,height }; }

void Card::unload(){ UnloadTexture(face); }

void Card::save(ofstream& file) {
	file.write((char*)&value, sizeof(int));
	file.write((char*)&name, sizeof(char));
	file.write((char*)&flipped, sizeof(bool));
	size_t len = front.length();
	file.write((char*)&len, sizeof(size_t));
	file.write(front.data(), front.length());
	file.write((char*)&xy.x, sizeof(float));
	file.write((char*)&xy.y, sizeof(float));
	file.write((char*)&hitBox.width, sizeof(float));
	file.write((char*)&hitBox.height, sizeof(float));
}

void Card::load(ifstream& file) {
	file.read((char*)&value, sizeof(int));
	file.read((char*)&name, sizeof(char));
	file.read((char*)&flipped, sizeof(bool));

	size_t len;
	file.read((char*)&len, sizeof(size_t));
	front.resize(len);
	file.read((char*)&front[0], len);

	if (flipped) face = LoadTexture(front.data());
	else face = LoadTexture(BACK_TEXTURE);

	file.read((char*)&xy.x, sizeof(float));
	file.read((char*)&xy.y, sizeof(float));
	hitBox.x = xy.x;
	hitBox.y = xy.y;
	file.read((char*)&hitBox.width, sizeof(float));
	file.read((char*)&hitBox.height, sizeof(float));
}