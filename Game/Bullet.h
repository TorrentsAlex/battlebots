#pragma once
#include "Entity.h"

class Bullet : public Entity {
private:
	float bVelocity = 3.5f;
	glm::vec3 bDirection;
	float angle;
public:
	Bullet();
	~Bullet();
	void init();
	void setDirection(glm::vec3 direction);
	void update();
};

