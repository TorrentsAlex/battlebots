#include "Movable.h"
#include <glm/glm.hpp>
#include <glm/gtx/rotate_vector.hpp>


#include <iostream>
Movable::Movable() {
	init();
}

Movable::Movable(OBJ* mesh, GameObject gameObject):
	Entity(mesh, gameObject) {
	init();
}

Movable::~Movable() {
	//delete[] sMesh;
}

void Movable::update(glm::vec3 car) {
	// Check if the person is outside the map
	if (sGameObject._translate.x < 0 ||
		sGameObject._translate.x > 63) {
		fForwardV.x *= -1;
	}
	if (sGameObject._translate.y < 0 ||
		sGameObject._translate.y > 63) {
		fForwardV.y *= -1;
	}
	
	//The enemy move
	carDirection= glm::vec3(car.x- sGameObject._translate.x, car.y-sGameObject._translate.y, car.z- sGameObject._translate.z);

	//Calculate the distance and stop to walk if distance is minus or equal than radius
	float distance = (carDirection.x*carDirection.x) + (carDirection.y*carDirection.y) + (carDirection.z*carDirection.z);
	distance = glm::sqrt(distance);
	
	carDirection = glm::normalize(carDirection);
	sGameObject._translate.x += carDirection.x * velocity;
	sGameObject._translate.y += carDirection.y * velocity;

	//Calculate the angle between the forward and the direccion of Car
	float divisor = glm::dot(carDirection, fForwardV);
	float operation = (carDirection.x *carDirection.x) + (carDirection.y*carDirection.y)+ (carDirection.z*carDirection.z);
	float operation2 = (fForwardV.x *fForwardV.x) + (fForwardV.y*fForwardV.y) + (fForwardV.z*fForwardV.z);
	float dividend = operation*operation2;
	float angle = divisor / dividend;

	//Rotate the enemy to the Car
	glm::vec2 rot = glm::rotate(glm::vec2(fForwardV.x, fForwardV.y), angle);
	fForwardV.x = rot.x;
	fForwardV.y = rot.y;
	sGameObject._angle = sGameObject._angle+ angle;

	sBoundingBox.setCenter(sGameObject._translate.x, sGameObject._translate.y);
}

void Movable::update() {
	// Check if the person is outside the map
	if (sGameObject._translate.x < 0 ||
		sGameObject._translate.x > 63) {
		fForwardV.x *= -1;
	}
	if (sGameObject._translate.y < 0 ||
		sGameObject._translate.y > 63) {
		fForwardV.y *= -1;
	}
	sGameObject._translate.x += fForwardV.x * velocity;
	sGameObject._translate.y += fForwardV.y * velocity;

	sBoundingBox.setCenter(sGameObject._translate.x, sGameObject._translate.y);
}


void Movable::init() {
	float x = rand() % 100 + 1;
	float y = rand() % 100 + 1;
	x /= 100;
	y /= 100;
	float angle = sGameObject._angle;
	fForwardV = glm::vec3(cos(angle), sin(angle), 0);
	sBoundingBox.calculateBoundingBoxes(sMesh);
}