#include "Robot.h"

#include "GamePad.h"

Robot::Robot() {}

Robot::~Robot() {
	if (rGamePad) {
		rGamePad->clean();
		delete rGamePad;
	}
	
}

void Robot::update() {

}


void Robot::input() {

}

void Robot::setGamePad(GamePad& gamePad) {
	*rGamePad = gamePad;
}

GamePad* Robot::getGamePad() {
	return rGamePad;
}

void Robot::movement(glm::vec2 axis) {
	// Invert Y axis
	// Get a value between 0 and 1
	axis.x /= 32767;
	axis.y /= 32767;

	eGameObject._translate.x += axis.x * velocity;
	eGameObject._translate.y += axis.y * velocity;
}

void Robot::rotation(glm::vec2 axis) {
	//vectorForward.x = cosf();
	double angle = atan2((double)axis.y, (double)axis.x) * (180.0 / 3.14159);
	glm::vec2 forwardRotated = glm::rotate(glm::vec2(vectorForward.x, vectorForward.y), (float)angle);
	vectorForward.x = forwardRotated.x;
	vectorForward.y = forwardRotated.y;
	eGameObject._angle = angle;
	cout << " angle: " << angle << endl;
}

void Robot::jump() {
	cout << "jump " << name << endl;
}

void Robot::shoot() {

}

void Robot::pointGun(float x, float y) {

}
