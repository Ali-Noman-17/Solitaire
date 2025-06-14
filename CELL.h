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
#define CELL_WIDTH 75
#define CELL_HEIGHT 112.5
#define SPACER_WIDTH 25
#define VERT_WIDTH 20
#define CELL_ROTATION 0.00
#define CELL_SCALE 0.25
#define CELL_TINT WHITE
#define STACK_WIDTH 25
#define CAP_INCREMENT 5

class Cell {
	int cap;
	int num;
	Card** arr;
	Texture2D face;
	Vector2 xy;
	Rectangle hitBox;
public:
	Cell();
	Cell(const int cap, const char* path);
	virtual ~Cell();
	int getNum();
	int getCap();
	char getLatestColour();
	Rectangle getHitBox();
	Rectangle getCardHitBox(const int index);
	Rectangle getTopCardHitBox();
	bool isEmpty();
	virtual bool stackAllowed(Card* obj) = 0;
	void move(const float x, const float y);
	void updateHitBox(const float width, const float height);
	void updateHitBox();
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
	bool isTopCard(Card* obj);
	Card* getCard(const int index);
	Card* getTopCard();
};

#endif CELL_H