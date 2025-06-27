#ifndef DIVISION_H
#define DIVISION_H

#include <iostream>
#include <string>
#include <raylib.h>
#include "SPADES.h"
#include "CLUBS.h"
#include "HEARTS.h"
#include "DIAMONDS.h"
#include "CELL.h"
#include "ALTERNATE_CELL.h"
#include "SUIT_CELL.h"
#include "FREE_CELL.h"
using namespace std;

template <typename T>
class Division {
	int num;
	Cell** arr;
	Texture2D face;
	Vector2 xy;
	Rectangle hitBox;
public:
	Division() : num(0), arr(nullptr), face(), xy{ 0,0 } {}

	Division(const int num, const char* path, const float width, const float height) :
		num(num), arr(new Cell* [num]) {
		face = LoadTexture(path);
		xy = { 0,0 };
		for (int i = 0; i < num; i++) { arr[i] = new T; }
		hitBox = { xy.x, xy.y, width, height };
		face.width = hitBox.width;
		face.height = hitBox.height;
		initialiseCells();
	}

	~Division() { 
		UnloadTexture(face); 
		for (int i = 0; i < num; i++) { delete arr[i]; }
		delete[] arr;
	}

	T* constructCell() {
		return new T();
	}

	void draw() {
		DrawTextureEx(face, xy, DIVISION_ROTATION, DIVISION_SCALE, DIVISION_TINT);
		for (int i = 0; i < num; i++) { arr[i]->draw(); }
	}

	void initialiseCells() {
		if (num == ALTERNATE_DIVISION_NUM) {
			for (int i = 0; i < num; i++) {
				delete arr[i];
				arr[i]= new AlternateCell(NUMBER_VALS, CELL_TEXTURE);
			}
		}
		else if (num == SUIT_DIVISION_NUM) {
			for (int i = 0; i < NUMBER_SUITS; i++) { delete arr[i]; }
			arr[0] = new SuitCell(NUMBER_VALS, SPADES_CELL_TEXTURE, SUIT_SPADES);
			arr[1] = new SuitCell(NUMBER_VALS, CLUBS_CELL_TEXTURE, SUIT_CLUBS);
			arr[2] = new SuitCell(NUMBER_VALS, HEARTS_CELL_TEXTURE, SUIT_HEARTS);
			arr[3] = new SuitCell(NUMBER_VALS, DIAMONDS_CELL_TEXTURE, SUIT_DIAMONDS);
		}
		else if (num == POOL_DIVISION_NUM) {
			for (int i = 0; i < num; i++) {
				delete arr[i];
				arr[i] = new FreeCell(NUMBER_POOL, CELL_TEXTURE);
			}
		}
	}
	
	void positionCells() {
		float yShift = xy.y + VERT_WIDTH;
		for (int i = 0; i < num; i++) {
			float cellWidth = i * CELL_WIDTH;
			float spacerWidth = (i + 1) * SPACER_WIDTH;
			float xShift = xy.x + cellWidth + spacerWidth;

			arr[i]->move(xShift, yShift);
			arr[i]->updateHitBox();
			arr[i]->alignCards();
		}
	}

	Cell* getCellRef(const int index) { return arr[index]; }

	Rectangle getHitBox() { return hitBox; };

	Rectangle getCellHitBox(const int index) { return arr[index]->getHitBox(); };

	void move(const float x, const float y) { xy = { x,y }; }

	void updateHitBox() { hitBox = { xy.x,xy.y, hitBox.width, hitBox.height }; }

	void updateHitBox(const float width, const float height) { hitBox = { xy.x,xy.y,width,height }; }

	void moveToCell(Card* obj, Cell* baseCell, Cell* targetCell) {
		int index = -1;
		int size = baseCell->getNum();
		for (int i = 0; i < size; i++) {
			if (baseCell->getCard(i) == obj) {
				index = i;
				break;
			}
		}
		if (index == -1) return;
		if (!targetCell->stackAllowed(obj)) return;
		else moveStack(obj, baseCell, targetCell, index);
	}

	void moveStack(Card* obj, Cell* baseCell, Cell* targetCell, const int index) {
		int size = baseCell->getNum();
		for (int i = index; i < size; i++) {
			targetCell->add(baseCell->getCard(i));
		}
		for (int i = index; i < size; i++) {
			baseCell->remove(baseCell->getCard(i));
		}
	}

	void flipTops() { 
		for (int i = 0; i < num; i++) { arr[i]->flipTop(); } 
	}

	int getCellNum(const int cellNum) { return arr[cellNum]->getNum(); }

	void addToCell(Card* obj, const int cellNum) {
		arr[cellNum]->add(obj);
	}

	void reveal() {
		int i = arr[POOL_LOCKED_CELL]->getNum() - 1;
		Card* obj = arr[POOL_LOCKED_CELL]->getTopCard();
		obj->flip();
		moveStack(obj, arr[POOL_LOCKED_CELL], arr[POOL_AVAILABLE_CELL], i);
	}
	
	void cycleBack() {
		int size = arr[POOL_AVAILABLE_CELL]->getNum();
		for (int i = 1; i <= size; i++) {
			Card* obj = arr[POOL_AVAILABLE_CELL]->getCard(size - i);
			obj->flip();
			arr[POOL_LOCKED_CELL]->add(obj);
			arr[POOL_AVAILABLE_CELL]->remove(obj);
		}
	}

	void save(ofstream& file) {
		for (int i = 0; i < num; i++) { arr[i]->save(file); }
	}

	void load(ifstream& file, Card** deck) {
		for (int i = 0; i < num; i++) { arr[i]->load(file,deck); }
	}

	bool isCellEmpty(const int i) { return arr[i]->isEmpty(); }
};

#endif DIVISION_H