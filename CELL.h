#ifndef CELL_H
#define CELL_H

#include <iostream>
#include <string>
#include <raylib.h>
#include "CARD.h"
using namespace std;

#define CELL_TEXTURE "./sprites/texture-cell.jpg"
#define SPADES_CELL_TEXTURE "./sprites/texture-cell-S.jpg"
#define CLUBS_CELL_TEXTURE "./sprites/texture-cell-C.jpg"
#define HEARTS_CELL_TEXTURE "./sprites/texture-cell-H.jpg"
#define DIAMONDS_CELL_TEXTURE "./sprites/texture-cell-D.jpg"
#define CELL_ROTATION 0.00
#define CELL_SCALE 0.25
#define CELL_TINT WHITE
#define STACK_WIDTH 10
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
	bool isEmpty();
	virtual bool stackAllowed(Card* obj) = 0;
	void move(const float x, const float y);
	void alignCards();
	void empty();
	void unload();
	virtual void draw();
	void drawEmpty();
	void drawCascade();
	void flipTop();
	void increaseCap();
	void add(Card* obj);
	void remove(Card* obj);
	Card* getCard(const int i);
};

#endif CELL_H