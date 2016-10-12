#pragma once

#include <iostream>

#include "Bullet.h"
#include <glm/gtx/rotate_vector.hpp>

class Robot : public Entity {
private:
	
	float velocity = 0.5;
	std::vector<Bullet> bullets;
	Bullet currentBullet;
	bool canShoot;

public:
	Robot();
	~Robot();
	glm::vec3 vectorForward;

	virtual void update() override;
	void input();
	std::string name;

	void jump();
	void shoot();

	void pointGun(float x, float y);

	void movement(glm::vec2 axis);
	void rotation(glm::vec2 axis);


	void setBullet(Bullet nextBullet);

	vector<Bullet> getBullets();


};

