#ifndef CELL_H
#define CELL_H

#include <iostream>
#include <string>
#include <raylib.h>
#include "CARD.h"
using namespace std;

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
	void savePrimitives(ofstream& file);
	void loadPrimitives(ifstream& file);
	void saveCards(ofstream& file);
	void loadCards(ifstream& file, Card** deck);
	virtual void save(ofstream& file);
	virtual void load(ifstream& file, Card** deck);
};

#endif CELL_H