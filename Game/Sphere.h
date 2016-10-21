#pragma once
#include <glm/vec2.hpp>
#include "OBJ.h"
#include "GameObject.h"

class Sphere {
private:
	float sRadius;
	glm::vec2 sCenter;

public:
	Sphere();
	~Sphere();
	void setRadius(float radius);
	void setCenter(glm::vec2 center);
	void setCenter(float x, float y);

	float getRadius();
	glm::vec2 getCenter();
	float getXCenter();
	float getYCenter();

	void calculateBoundingBoxes(OBJ mesh);

};

