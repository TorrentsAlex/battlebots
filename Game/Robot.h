#pragma once

#include <iostream>

#include "Entity.h"

class Robot : public Entity {
private:

public:
	Robot();
	~Robot();
	glm::vec3 vectorForward;

	void update();
	void input();
	std::string name;
	//void setGamePad(SDL_Joystick* gamepad);
	//GamePad* gamepad;

	void jump();
	void shoot();

	void pointGun(float x, float y);

	void movement(glm::vec2 axis);
	void rotation(glm::vec2 axis);

};

