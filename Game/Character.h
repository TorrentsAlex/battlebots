#pragma once

#include <iostream>
#include "Entity.h"
#include <glm/gtx/rotate_vector.hpp>

struct GamePad;
class Character : public Entity {
private:
	
	float velocity = 0.5;
	GamePad* rGamePad;

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

	void pointGun(float x, float y);

	void movement(glm::vec2 axis);
	void rotation(glm::vec2 axis);

	void setGamePad(GamePad& gamePad);
	GamePad* getGamePad();

	void clean();
};

