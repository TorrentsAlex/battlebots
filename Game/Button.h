#pragma once
#include "Entity.h"

enum class ButtonState {
	ON,
	OFF
};

class Button : public Entity {
private:
	GLuint bTextureOff;
	GLuint bTextureOn;
	ButtonState currentState;

public:
	Button();
	~Button();

	void setTextureOff(GLuint textureOff);
	void changeState();

	bool isOn();
};

