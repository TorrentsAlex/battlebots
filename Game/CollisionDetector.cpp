#include "CollisionDetector.h"



CollisionDetector::CollisionDetector() {
}


CollisionDetector::~CollisionDetector() {
}

// Detection between 2 spheres
bool CollisionDetector::GetCollision(Sphere s1, Sphere s2) {
	float deltaXSquared = s2.getXCenter() - s1.getXCenter();
	float deltaYSquared = s2.getYCenter() - s1.getYCenter();

	deltaXSquared *= deltaXSquared;
	deltaYSquared *= deltaYSquared;
	
	float sumRadisquared = s1.getRadius() + s2.getRadius();

	sumRadisquared *= sumRadisquared;

	if (deltaXSquared + deltaYSquared <= sumRadisquared) {
		return true;
	} else {
		return false;
	}
}

// Detecion between Sphere and cube
glm::vec2 CollisionDetector::GetCollision(Sphere s1, Box b2) {
	float distSquared = s1.getRadius() * s1.getRadius();
	float closestX = s1.getXCenter();
	float closestY = s1.getYCenter();
	
	// Compare the center of the objects to see what corners we need to compare
	// the sphere is on the left of the box
	if (s1.getXCenter() < (b2.getXCenter() - b2.getWidth() / 2.0f)) {
		closestX = b2.getXCenter() - b2.getWidth() / 2.0f;
	} else if(s1.getXCenter() > (b2.getXCenter() + b2.getWidth() / 2.0f)) {
		closestX = b2.getXCenter() + b2.getWidth() / 2.0f;
	}
	// The sphere is under the box
	if (s1.getYCenter() < (b2.getYCenter() - b2.getHeight() / 2.0f)) {
		closestY = b2.getYCenter() - b2.getHeight() / 2.0f;
	} else if (s1.getYCenter() > (b2.getYCenter() + b2.getHeight() / 2.0f)) {
		closestY= b2.getYCenter() + b2.getHeight() / 2.0f;
	}

	closestX -= s1.getXCenter();
	closestX *= closestX;
	closestY -= s1.getYCenter();
	closestY *= closestY;

	if (closestX + closestY < distSquared) {
		return glm::normalize(glm::vec2(b2.getXCenter() - s1.getXCenter(), b2.getYCenter() - s1.getYCenter()));
	} else {
		return glm::vec2(0, 0);
	}
}