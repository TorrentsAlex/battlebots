#pragma once
#include "Object.h"
#include "Immovable.h"
#include "CollisionDetector.h"

class Movable: public Object {
private:	
	glm::vec3 fForwardV;
	float velocity = 0.04;
	glm::vec3 carDirection;

	void init();

public:
	Movable();
	Movable(OBJ* mesh, GameObject gameObject);
	~Movable();

	void update(glm::vec3 car);

	void update();
};

