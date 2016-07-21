#pragma once
#include <glm/glm.hpp>

class Box {
private:
	glm::vec2 bCenter;
	float bWidth;
	float bHeight;

public:
	Box();
	~Box();

	void setCenter(float x, float y);
	void setCenter(glm::vec2 center);
	void setSize(float width, float height);

	glm::vec2 getCenter();
	float getXCenter();
	float getYCenter();

	float getWidth();
	float getHeight();
};

