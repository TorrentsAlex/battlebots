#include "Button.h"

Button::Button() {
}

Button::Button(int id, std::string text, int width, int height, int x, int y, int backgroundImage, int textColor) {
	this->width = id;
	this->text = text;
	this->width = width;
	this->height = height;
	this->x = x;
	this->y = y;
	this->backgroundImage = backgroundImage;
	this->textColor = textColor;

	// Init the image background png
	startBackgroundX = this->x - 30;
	startBackgroundY = this->y - 15;
	backgroundWidth = width + 60;
	backgroundHeight = height + 40;
}

Button::~Button() {
}

/**
Listener for the buttons;
*/
bool Button::detectPressed(int xMouse, int yMouse) {
	if ((xMouse >= startBackgroundX) && (xMouse <= startBackgroundX + backgroundWidth) &&
		(yMouse >= startBackgroundY) && (yMouse <= startBackgroundY + backgroundHeight)) {
		return true;
	}
	return false;
}

/**
Draw the button and the text in the screen

void Button::draw(SDLInterface& graphic) {
	graphic.drawTexture(backgroundImage, 0, 0, 500, 162, startBackgroundX, startBackgroundY, backgroundWidth, backgroundHeight);
	graphic.drawText(" " + this->text + " ", BLACK, this->x, this->y);
}*/

void Button::setButtonID(int id) {
	this->id = id;
}

int Button::getWidth() {
	return this->backgroundWidth;
}

int Button::getHeight() {
	return this->backgroundHeight;
}

/**
Return the Button id
*/
int Button::getId() {
	return id;
}