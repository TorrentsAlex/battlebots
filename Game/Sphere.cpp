#include "Sphere.h"



Sphere::Sphere() {
}

Sphere::~Sphere() {
}

// Setter
void Sphere::setRadius(float radius) {
	sRadius = radius;
}

void Sphere::setCenter(glm::vec2 center) {
	sCenter = center;
}

void Sphere::setCenter(float x, float y) {
	sCenter = glm::vec2(x, y);
}

// Getters
float Sphere::getRadius() {
	return sRadius;
}

glm::vec2 Sphere::getCenter() {
	return sCenter;
}

float Sphere::getXCenter() {
	return sCenter.x;
}

float Sphere::getYCenter() {
	return sCenter.y;
}

void Sphere::calculateBoundingBoxes(OBJ mesh) {

	// if the object is not a square shape calculate the major radius
	float xRadius, yRadius;
	xRadius = (mesh.width.y - mesh.width.x) / 2;
	yRadius = (mesh.lenght.y - mesh.lenght.x) / 2;

	sRadius = (xRadius > yRadius) ? xRadius: yRadius;
}
