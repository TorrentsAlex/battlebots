#include "Button.h"

Button::Button() {
}


Button::~Button() {
}

void Button::setName(string name) {
	bName = name;
}

string Button::getName() {
	return bName;
}

void Button::setTextureOff(GLuint textureOff) {
	bTextureOff = textureOff;
	// And save the texture on;
	bTextureOn = eMaterial.textureMap;
	currentState = ButtonState::ON;
}

void Button::setSpecularMap(GLuint specularMap) {
	bSpecularMapOn = specularMap;
}

void Button::changeStateOn() {
	currentState = ButtonState::ON;
	eMaterial.textureMap = bTextureOn;
	eMaterial.specularMap = bSpecularMapOn;

}
void Button::changeStateOff() {
	// change to off
	currentState = ButtonState::OFF;
	eMaterial.textureMap = bTextureOff;
	eMaterial.specularMap = -1;
}

bool Button::isOn() {
	if (currentState == ButtonState::ON) {
		return true;
	} else {
		return false;
	}
}