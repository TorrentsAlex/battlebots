#pragma once

#include <string>
#include "Object.h"

class Button: public Object {
private:
	int id;
	std::string text;
	int width, height, x, y;
	int backgroundImage;
	int textColor;

	int startBackgroundX, startBackgroundY;
	int backgroundWidth, backgroundHeight;

public:
	Button();
	Button(int id, std::string text, int width, int height, int x, int y, int backgroundImage, int textColor);
	~Button();

	// Detect when the mouse clicked the button
	bool detectPressed(int xMouse, int yMouse);
	//void draw(SDLInterface& graphic);
	void setText(string text);
	void setButtonID(int id);
	int getWidth();
	int getHeight();
	int getId();

};