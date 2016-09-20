#include "ButtonManager.h"

ButtonManager::ButtonManager() {
}


ButtonManager::~ButtonManager() {
}

void ButtonManager::initButtons() {
	button.setButtonID(HOLA);
	SDL_Color color;
	color.r = (Uint8)255;
	color.g = (Uint8)0;
	color.b = (Uint8)0;
	color.a = (Uint8)255;
	button.setTextureId(textManager.getTextureID("Alex Torrents", color));
	play.setTextureId(textManager.getTextureID("P: Play", color));
	editor.setTextureId(textManager.getTextureID("E: Editor", color));

	GameObject bObject;
	bObject._textureRepetition = false;
	bObject._translate = glm::vec3(-0.78, -0.97, 0);
	bObject._angle = 0;
	bObject._rotation = glm::vec3(0, 0, 0);
	bObject._scale = glm::vec3(0.2, 0.02, 1);
	button.setGameObject(bObject);

	bObject._translate = glm::vec3(0.4, 0.2f,0);
	bObject._scale = glm::vec3(0.3, 0.1 ,1);
	play.setGameObject(bObject);

	bObject._translate = glm::vec3(0.4, -0.2f, 0);
	bObject._scale = glm::vec3(0.3, 0.1, 1);
	editor.setGameObject(bObject);
	
	buttons.push_back(button);
	buttons.push_back(play);
	buttons.push_back(editor);

}

glm::mat4 ButtonManager::getMatrix() {
	return unitaryMatrix;
}

Button ButtonManager::getButtonToDraw() {
	return buttons.at(currentButton);
}

GLuint ButtonManager::getTextureId() {
	return buttons.at(currentButton).getTextureId();
}

float ButtonManager::size() {
	return buttons.size();
}

void ButtonManager::nextButton() {
	currentButton++;
	if (currentButton >=buttons.size()) {
		currentButton = 0;
	}
}