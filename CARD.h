#ifndef CARD_H
#define CARD_H

#include <iostream>
#include <fstream>
#include <string>
#include <raylib.h>
using namespace std;

#define SAVE_FILE "SAVED_DATA.bin"
#define BACK_TEXTURE "./sprites/texture-back.jpg"
#define FRONT_TEXTURE_PREFIX "./sprites/"
#define FRONT_TEXTURE_SUFFIX ".jpg"
#define RED_CARD_COLOUR 'R'
#define BLACK_CARD_COLOUR 'B'
#define SUIT_SPADES 'S'
#define SUIT_CLUBS 'C'
#define SUIT_HEARTS 'H'
#define SUIT_DIAMONDS 'D'
#define CARD_WIDTH 75
#define CARD_HEIGHT 112.5
#define CARD_HEIGHT_STACKED 22.5
#define CARD_ROTATION 0.00
#define CARD_SCALE 1.00
#define CARD_TINT WHITE

class Card {
	int value;
	char name;
	bool flipped;
	string front;
	Texture2D face;
	Vector2 xy;
	Rectangle hitBox;
	
public:
	Card();
	Card(int val, char name, const char* path);
	virtual ~Card();
	int getValue();
	char getName();
	virtual char getColour() = 0;
	virtual char getSuit() = 0;
	Rectangle getHitBox();
	void flip();
	void setFlip(bool flip);
	bool isFlipped();
	bool canStackAsc(Card* obj);
	bool canStackDsc(Card* obj);
	void draw();
	void move(const float x, const float y);
	void updateHitBox(const float width, const float height);
	void updateHitBox();
	void unload();
	void save(ofstream& file);
	void load(ifstream& file);

};

#endif CARD_H