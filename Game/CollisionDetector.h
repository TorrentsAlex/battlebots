#pragma once
#include "Sphere.h"
#include "Box.h"

class CollisionDetector {
public:
	CollisionDetector();
	~CollisionDetector();

	static glm::vec2 GetCollision(Sphere s1, Sphere s2);
	static glm::vec2 GetCollision(Sphere s1, Box b2);
};

