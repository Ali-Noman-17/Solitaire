#ifndef CARD_H
#define CARD_H

#include <iostream>
#include <fstream>
#include <string>
#include <raylib.h>
#include "MACROS.h"
using namespace std;

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
	void correctFace();
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