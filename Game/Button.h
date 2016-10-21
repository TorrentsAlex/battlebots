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
	GLuint bSpecularMapOn;
	ButtonState currentState;

public:
	Button();
	~Button();


	void setTextureOff(GLuint textureOff);
	void setSpecularMap(GLuint specularMap);

	void changeStateOn();
	void changeStateOff();

	bool isOn();

	void setName(string name);
	string getName();
};

