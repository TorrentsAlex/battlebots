#include "Bullet.h"

Bullet::Bullet() {	

}

Bullet::~Bullet() {
}

void Bullet::init() {
	angle = rand() % 360 + 1;
	eGameObject._rotation = glm::vec3(rand(), rand(), rand());
}

void Bullet::setDirection(glm::vec3 direction) {
	bDirection = direction;
}

void Bullet::update() {
	eGameObject._translate.x += bDirection.x * bVelocity;
	eGameObject._translate.y += bDirection.y * bVelocity;
	eGameObject._translate.z += bDirection.z * bVelocity;

	eGameObject._angle += angle;
}