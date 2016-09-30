#include "Button.h"



Button::Button() {
}


Button::~Button() {
}

void Button::setTextureOff(GLuint textureOff) {
	bTextureOff = textureOff;
	// And save the texture on;
	bTextureOn = eMaterial.textureMap;
}

void Button::changeState() {
	// change to off
	if (currentState == ButtonState::ON) {
		currentState = ButtonState::OFF;
		eMaterial.textureMap = bTextureOff;
	} else {
		// change to on
		currentState = ButtonState::ON;
		eMaterial.textureMap = bTextureOn;
	}
}

bool Button::isOn() {
	if (currentState == ButtonState::ON) {
		return true;
	} else {
		return false;
	}
}