#ifndef DIVISION_H
#define DIVISION_H

#include <iostream>
#include <string>
#include <raylib.h>
#include "CELL.h"
using namespace std;

#define ALTERNATE_DIVISION_TEXTURE "./sprites/texture-alt-div.jpg"
#define SUIT_DIVISION_TEXTURE "./sprites/texture-suit-div.jpg"
#define POOL_DIVISION_TEXTURE "./sprites/texture-pool-div.jpg"
#define ALTERNATE_DIVISION_NUM 7
#define SUIT_DIVISION_NUM 4
#define POOL_DIVISION_NUM 2
#define POOL_SIZE 16
#define POOL_LOCKED_CELL 0
#define POOL_AVAILABLE_CELL 1
#define CELL_WIDTH 75
#define SPACER_WIDTH 25
#define VERT_WIDTH 20
#define DIVISION_ROTATION 0.00
#define DIVISION_SCALE 1.00
#define DIVISION_TINT WHITE


template <typename T>
class Division {
	int num;
	Cell** arr;
	Texture2D face;
	Vector2 xy;
public:
	Division() : num(0), arr(nullptr), face(), xy{ 0,0 } {}

	Division(const int num, const char* path) : num(num), arr(new Cell* [num]) {
		face = LoadTexture(path));
		xy = { 0,0 };
		for (int i = 0; i < num; i++) { arr[i] = new T; }
	}

	~Division() { 
		UnloadTexture(face); 
		for (int i = 0; i < num; i++) { delete arr[i]; }
		delete[] arr;
	}

	void draw() {
		DrawTextureEx(face, xy, DIVISION_ROTATION, DIVISION_SCALE, DIVISION_TINT);
		for (int i = 0; i < num; i++) { arr[i]->draw(); }
	}

	void positionCells() {
		float yShift = xy.y + VERT_WIDTH;
		for (int i = 0; i < num; i++) {
			float cellWidth = i * CELL_WIDTH;
			float spacerWidth = (i + 1) * SPACER_WIDTH;
			float xShift = xy.x + cellWidth + spacerWidth;

			arr[i]->move(xShift, yShift);
		}
	}

	void move(const float x, const float y) { xy = { x,y }; }

	void moveToCell(Card* obj, Cell* baseCell, Cell* targetCell) {
		int index = -1;
		int size = baseCell->getNum();
		for (int i = 0; i < size; i++) {
			if (arr[i] == obj) {
				index = i;
				break;
			}
		}
		if (index == -1) return; //error
		if (!targetCell->stackAllowed(obj)) return; //error
		else moveStack(obj, baseCell, targetCell, index);
	}

	void moveStack(Card* obj, Cell* baseCell, Cell* targetCell, const int index) {
		int size = baseCell->getNum();
		for (int i = index; i < size; i++) {
			targetCell->add(obj);
			baseCell->remove(obj);
		}
	}

	void flipTops() { 
		for (int i = 0; i < num; i++) { arr[i]->flipTop(); } 
	}

	void reveal() {
		int i = arr[POOL_LOCKED_CELL]->getNum();
		Card* obj = arr[POOL_LOCKED_CELL]->getCard(i);
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

	bool isCellEmpty(const int i) { return arr[i]->isEmpty(); }
};

#endif DIVISION_H