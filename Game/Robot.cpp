#include "Robot.h"



Robot::Robot() {
}


Robot::~Robot() {
}


void Robot::update() {
}

void Robot::input() {

	//TurriFramework::Instance().getKeys(rGamePad);
}

void Robot::setGamePad(SDL_Joystick * gamepad) {
	rGamePad = gamepad;
}
