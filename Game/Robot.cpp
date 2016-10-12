#include "Robot.h"


Robot::Robot() {
	canShoot = true;
}


Robot::~Robot() {
}

void Robot::update() {
	// Rotate
	static int counter = 0;
	if (counter >= 16) {
		counter = 0;
		canShoot = true;
	}
	counter++;
	
	static int bulletCounter = 0;
	if (counter >= 200) {
		bulletCounter = 0;
		if (!bullets.empty()) {
			bullets.pop_back();
		}
	}
	bulletCounter++;
	for (int i = 0; i < bullets.size(); i++) {
		bullets.at(i).update();
	}
}

vector<Bullet> Robot::getBullets() {
	return bullets;
}

void Robot::setBullet(Bullet nextBullet) {
	currentBullet = nextBullet;
}

void Robot::input() {

}

void Robot::movement(glm::vec2 axis) {
	// Invert Y axis
	// Get a value between 0 and 1
	axis.x /= 32767;
	axis.y /= 32767;

	eGameObject._translate.x += axis.x * velocity;
	eGameObject._translate.y += axis.y * velocity;
}

void Robot::rotation(glm::vec2 axis) {
	//vectorForward.x = cosf();
	double angle = atan2((double)axis.y, (double)axis.x) * (180.0 / 3.14159);
	glm::vec2 forwardRotated = glm::rotate(glm::vec2(vectorForward.x, vectorForward.y), (float)angle);
	vectorForward.x = forwardRotated.x;
	vectorForward.y = forwardRotated.y;
	eGameObject._angle = angle;
	cout << " angle: " << angle << endl;
}

void Robot::jump() {
	cout << "jump " << name << endl;
}

void Robot::shoot() {
	if (canShoot) {
		canShoot = false;
		GameObject go = currentBullet.getGameObject();
		go._translate = eGameObject._translate;
		go._translate.z = 15.0f;
		currentBullet.setGameObject(go);
		currentBullet.setDirection(vectorForward);
		bullets.push_back(currentBullet);
	}

}

void Robot::pointGun(float x, float y) {

}
