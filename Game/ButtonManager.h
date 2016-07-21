#pragma once
#include "TextManager.h"
#include "Button.h"

#define HOLA 0
class ButtonManager {
private:
	TextManager textManager;
	Button button;
	Button play;
	Button editor;
	std::vector<Button> buttons;
	glm::mat4 unitaryMatrix;

	int currentButton = 0;

public:
	ButtonManager();
	~ButtonManager();

	void initButtons();
	void nextButton();

	float size();
	Button getButtonToDraw();
	GLuint getTextureId();


	glm::mat4 getMatrix();
};

