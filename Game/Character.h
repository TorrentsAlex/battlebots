#pragma once

#include <iostream>
#include "Entity.h"
#include <glm/gtx/rotate_vector.hpp>
#include <ctime>

typedef enum STATE {
	STUNNED, WALKING, DASHING, DRINKING, REFILL, JUMPING
};

struct GamePad;
class Character : public Entity {
private:
	
	float velocity = 0.5;
	GamePad* rGamePad;
	STATE currentState;
	float dashAcceleration = 3.0f;
	float dashCooldown = 5.0f;
	float dashTime = 3.0f;
	float jumpPower = 2.0f;
	float stunTime = 4.0f;

	float remainingBeer = 1.0f; // 1 = Full - 0 Empty
	float drunkennes = 1.0f;

public:
	Character();
	~Character();
	glm::vec3 vectorForward;

	virtual void update() override;
	void input();
	std::string name;

	void jump();
	void dash();
	void shoot();
	void refill();
	void drink();

	void pointGun(float x, float y);

	void movement(glm::vec2 axis);
	void rotation(glm::vec2 axis);
	
	void setGamePad(GamePad& gamePad);
	GamePad* getGamePad();
	void clean();
};

