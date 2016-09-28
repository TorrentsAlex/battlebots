#pragma once

#include "Entity.h"
#include "TurriFramework.h"

class Robot : public Entity {
private:
	SDL_Joystick* rGamePad;

public:
	Robot();
	~Robot();

	void update();
	void input();

	void setGamePad(SDL_Joystick* gamepad);
};

