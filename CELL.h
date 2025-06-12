#ifndef CELL_H
#define CELL_H

#include <iostream>
#include <string>
#include <raylib.h>
#include "CARD.h"
using namespace std;

#define CELL_TEXTURE "./sprites/texture-cell.jpg"
#define SPADES_CELL_TECTURE "./sprites/texture-cell-S.jpg"
#define CLUBS_CELL_TECTURE "./sprites/texture-cell-C.jpg"
#define HEARTS_CELL_TECTURE "./sprites/texture-cell-H.jpg"
#define DIAMONDS_CELL_TECTURE "./sprites/texture-cell-D.jpg"
#define CAP_INCREMENT 5

class Cell {
	int cap;
	int num;
	Card** arr;
	Texture2D face;
	Vector2 xy;
public:
	Cell();
	Cell(const int cap, const char* path);
	virtual ~Cell();
	int getNum();
	int getCap();
	char getLatestColour();
	virtual bool stackAllowed(Card* obj) = 0;
	void empty();
	void increaseCap();
	void add(Card* obj);
	void remove(Card* obj);
};

#endif CELL_H 