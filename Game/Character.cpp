#include "Character.h"

#include "GamePad.h"

Character::Character() {
	rGamePad = new GamePad();
}

Character::~Character() {
	if (rGamePad) {
		delete rGamePad;
	}
}

void Character::clean() {
	SDL_GameControllerClose(rGamePad->gameController);
	rGamePad->clean();
}

void Character::update() {

}


void Character::input() {

}

void Character::setGamePad(GamePad& gamePad) {
	*rGamePad = gamePad;
}

GamePad* Character::getGamePad() {
	return rGamePad;
}

void Character::movement(glm::vec2 axis) {
	// Invert Y axis
	// Get a value between 0 and 1
	axis.x /= 32767;
	axis.y /= 32767;
	//Get rotation from joysticks & Transform to (-)180 - 0 - 180 degrees
	double angle = atan2((double)axis.y, (double)axis.x) * (180.0 / 3.14159);
	//Movement
	eGameObject._translate.x += axis.x * velocity;
	eGameObject._translate.y += axis.y * velocity;
	//Rotation
	glm::vec2 forwardRotated = glm::rotate(glm::vec2(vectorForward.x, vectorForward.y), (float)angle);
	vectorForward.x = forwardRotated.x;
	vectorForward.y = forwardRotated.y;
	eGameObject._angle = angle;
	cout << " angle: " << angle << endl;

	double angle = atan2((double)axis.y, (double)axis.x) * (180.0 / 3.14159);

	glm::vec2 forwardRotated = glm::rotate(glm::vec2(vectorForward.x, vectorForward.y), (float)angle);

	glm::vec2 forwardRotated;
	forwardRotated.x = (toRotate.x - fromRotate.x) / timeToRotate;
	forwardRotated.y = (toRotate.y - fromRotate.y) / timeToRotate;
}

void Character::rotation(glm::vec2 axis) {
	//vectorForward.x = cosf();
	/*
	double angle = atan2((double)axis.y, (double)axis.x) * (180.0 / 3.14159);
	glm::vec2 forwardRotated = glm::rotate(glm::vec2(vectorForward.x, vectorForward.y), (float)angle);
	vectorForward.x = forwardRotated.x;
	vectorForward.y = forwardRotated.y;
	eGameObject._angle = angle;
	cout << " angle: " << angle << endl;
	*/
}

void Character::jump() {
	cout << "jump " << name << endl;
}

void Character::shoot() {

}

void Character::pointGun(float x, float y) {

}