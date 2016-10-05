#pragma once
#include "Entity.h"

enum class ButtonState {
	ON,
	OFF
};

class Button : public Entity {
private:
	string bName;

	GLuint bTextureOff;
	GLuint bTextureOn;
	ButtonState currentState;

public:
	Button();
	~Button();


	void setTextureOff(GLuint textureOff);
	void changeStateOn();
	void changeStateOff();

	bool isOn();

	void setName(string name);
	string getName();
};

