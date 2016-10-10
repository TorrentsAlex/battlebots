#pragma once

#include <iostream>

#include "Entity.h"

class Robot : public Entity {
private:
//	SDL_Joystick* rGamePad;

public:
	Robot();
	~Robot();

	void update();
	void input();

	//void setGamePad(SDL_Joystick* gamepad);

	void jump();
	void shoot();

	void pointGun(float x, float y);

};

