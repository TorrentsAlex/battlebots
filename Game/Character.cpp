#include "Character.h"

#include "GamePad.h"

Character::Character() {
	rGamePad = new GamePad();
	vectorForward = glm::vec3(1,0,0);
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

	eGameObject._translate.x += axis.x * velocity;
	eGameObject._translate.y += axis.y * velocity;
}

void Character::rotation(glm::vec2 axis) {
	//vectorForward.x = cosf();
	double angle = atan2((double)axis.y, (double)axis.x) * (180.0 / 3.14159);
	glm::vec2 forwardRotated = glm::rotate(glm::vec2(1, 0), (float)angle);
	vectorForward.x = forwardRotated.x;
	vectorForward.y = forwardRotated.y;
	eGameObject._angle = angle;
	cout << " angle: " << angle << endl;
}

void Character::jump() {
	cout << "jump " << vectorForward.x <<"/" << vectorForward.y  << endl;
	eGameObject._translate.x += vectorForward.x * velocity*10;
	eGameObject._translate.y += vectorForward.y * velocity*10;
}

void Character::shoot() {

}

void Character::pointGun(float x, float y) {

}
