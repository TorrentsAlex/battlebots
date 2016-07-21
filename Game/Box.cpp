#include "Box.h"



Box::Box() {
}


Box::~Box() {
}

void Box::setCenter(glm::vec2 center) {
	bCenter = center;
}

void Box::setCenter(float x, float y) {
	bCenter.x = x;
	bCenter.y = y;
}

void Box::setSize(float width, float height) {
	bWidth = width;
	bHeight = height;
}

glm::vec2 Box::getCenter() {
	return bCenter;
}

float Box::getXCenter() {
	return bCenter.x;
}

float Box::getYCenter() {
	return bCenter.y;
}


float Box::getWidth() {
	return bWidth;
}

float Box::getHeight() {
	return bHeight;
}