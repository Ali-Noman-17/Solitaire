#ifndef CARD_H
#define CARD_H

#include <iostream>
#include <string>
#include <raylib.h>
using namespace std;

#define BACK_TEXTURE "./backtext.png"
#define RED_CARD_COLOUR 'R'
#define BLACK_CARD_COLOUR 'B'
#define SUIT_SPADES 'S'
#define SUIT_CLUBS 'C'
#define SUIT_HEARTS 'H'
#define SUIT_DIAMONDS 'D'
#define CARD_ROTATION 0.00
#define CARD_SCALE 0.25
#define CARD_TINT WHITE

class Card {
	int value;
	char name;
	bool flipped;
	string front;
	Texture2D face;
	Vector2 xy;
	
public:
	Card();
	Card(int val, char name, const char* path);
	virtual ~Card() = 0;
	int getValue();
	char getName();
	virtual char getColour() = 0;
	virtual char getSuit() = 0;
	void flip();
	bool isFlipped();
	bool canStack(Card* obj);
	void draw();
	void move(const int x, const int y);
	void unload();

};

#endif CARD_H
