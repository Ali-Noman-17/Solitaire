#ifndef BUTTON_H
#define BUTTON_H

#include <iostream>
#include <raylib.h>
using namespace std;

class Button {
	Rectangle hitBox;
	string text;
	int textSize;
public:
	Button();
	Button(const float x, const float y, const float width, const float height, string txt);
	~Button();
	bool isHovered();
	void draw();
	Rectangle getHitBox();
};

#endif BUTTON_H