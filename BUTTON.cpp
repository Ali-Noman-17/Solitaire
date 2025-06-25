#include "BUTTON.h"

Button::Button() : hitBox(), text(), textSize() {}

Button::Button(const float x, const float y, const float width, const float height, string txt) : hitBox{ x,y,width,height }, 
text(txt), textSize(height/2) {}

Button::~Button() {}

bool Button::isHovered() {
	Vector2 mouse = GetMousePosition();
	return (CheckCollisionPointRec(mouse, hitBox));
}

void Button::draw() {
	if (isHovered()) DrawRectangleRec(hitBox, SKYBLUE);
	else DrawRectangleRec(hitBox, GRAY);
	DrawText(text.data(), hitBox.x + 8, hitBox.y + 8, textSize, WHITE);
}

Rectangle Button::getHitBox() {
	return hitBox;
}