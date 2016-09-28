#include "Car.h"


Car::Car():
	cBoundingBox(),
	cFrontBBox() {
	// Calculate the adjacent leg 
	legAdjacent = tan(90 - maxAngle) / legOpossite;	
	cForwardVector = glm::vec3(0, 1, 0);
}

Car::~Car() {
	//delete[] cObject->mesh;
}

// Model methods
void Car::setOBJ(OBJ  obj) {
	cObject = obj;
	cWidth = cObject.width.y - cObject.width.x;
	cHeight = cObject.lenght.y - cObject.lenght.x;
	// Set the bounding boxes
	//cBoundingBox.calculateBoundingBoxes(cObject);
	
	cFrontBBox.setCenter(cGameObject._translate.x, cGameObject._translate.y + (cHeight / 2.0f - cWidth / 2.0f));
	cFrontBBox.setRadius(cWidth/2.0f);
	cMiddleBBox.setRadius(cWidth / 2.0f);
	cBackBBox.setRadius(cWidth / 2.0f);
	cDistanceFrontBB = cHeight / 2.0f - cWidth / 2.0f;
}

void Car::setGameObject(GameObject gObject) {
	cGameObject = gObject;
}

void Car::setTextureId(string texturePath) {
	cTexturePath = texturePath;
}

void Car::setTextureId(GLuint textureId) {
	cTextureId = textureId;
}

void Car::setMaterial(Material material) {
	cMaterial = material;
}

// Getters
GameObject Car::getGameObject() {
	return cGameObject;
}

Material Car::getMaterial() {
	return cMaterial;
}

int Car::getNumVertices() {
	return cObject.numVertices;
}

Vertex * Car::getMesh() {
	return cObject.mesh;
}

float Car::getVelocity() {
	return cVelocity;
}

glm::vec3 Car::getPosition() {
	return cGameObject._translate;
}

float Car::getXPosition() {
	return cGameObject._translate.x;
}

float Car::getYPosition() {
	return cGameObject._translate.y;
}

glm::vec3 Car::getForwardVector() {
	return cForwardVector;
}

GLuint Car::getTextureId() {
	return cTextureId;
}
// Bounding Box methods
Sphere Car::getBoundingBox() {
	return cBoundingBox;
}

Sphere Car::getFrontBoundingBox() {
	return cFrontBBox;
}

Sphere Car::getMiddleBoundingBox() {
	return cMiddleBBox;
}

Sphere Car::getBackBoundingBox() {
	return cBackBBox;
}

// lifes
float Car::getLife() {
	return life;
}

void Car::restartLife() {
	life = 100;
}

void Car::setPosition(glm::vec3 pos) {
	cGameObject._translate.x = pos.x;
	cGameObject._translate.y = pos.y;

}

void Car::restartPosition() {
	cGameObject._translate.x = 0;
	cGameObject._translate.y = 0;
	life = 100;
	cGameObject._angle = 0;
	cVelocity = 0;
}

void Car::substractLife(float damage) {
	life -= damage;
}

// Car Physyics
void Car::accelerate() {
	state = CarVelocityState::ACCELERATE;
}

void Car::desaccelerate() {
	state = CarVelocityState::DESACCELERATE;
}

void Car::brake() {
	state = CarVelocityState::BRAKE;
}

void Car::launchCar(glm::vec2 vector) {
	cVelocity /= 4.0f;
	isBouncing = true;
	cBounceVector.x = vector.x / 4.0f;
	cBounceVector.y = vector.y / 4.0f;
}

void Car::left() {	
	//if (cVelocity != 0) {
		rotateState = CarRotateState::LEFT;
	//}
}

void Car::right() {
	//if (cVelocity != 0) {
		rotateState = CarRotateState::RIGHT;
	//}
}

void Car::update() {
	// Calculate the new velocity car
	switch (state) {
	case CarVelocityState::STOP:
		break;
	case CarVelocityState::ACCELERATE:
		if (cVelocity < cVelocityMax) {
			cVelocity += cSpeed;
		} else {

		}
		break;
	case CarVelocityState::BRAKE:
		if (cVelocity > 0) {
			cVelocity -= cBrake;
		} else if (cVelocity <= 0) {
			cVelocity = 0;
			state = CarVelocityState::REVERSE;
		}
		break;
	case CarVelocityState::DESACCELERATE:
		if (cVelocity > 0) {
			cVelocity -= cSpeed;
		} else if (cVelocity < 0) {
			cVelocity = 0;
			state = CarVelocityState::STOP;
		}
		break;
	case CarVelocityState::REVERSE:
		if (cVelocity <= 0) {
			//cVelocity -= cSpeed/2.0f;
		}
	case CarVelocityState::BOUNCE:

		break;
	}

	// Add to the object the new values 
	glm::vec3 newVelocity;

	newVelocity = glm::vec3(cForwardVector.x * cVelocity, cForwardVector.y * cVelocity, 0);	
	newVelocity.x += cGameObject._translate.x;
	newVelocity.y += cGameObject._translate.y;
	if (isBouncing) {
		newVelocity.x += cBounceVector.x;
		newVelocity.y += cBounceVector.y;
		if (counterBouncing >= 5) {
			counterBouncing = 0;
			isBouncing = false;
		}
		counterBouncing++;
	}
	cGameObject._translate = glm::vec3(newVelocity.x, newVelocity.y, 0);
	
	if (cVelocity != 0) {
		//std::cout << "velocity: " << cVelocity << std::endl;
	}

	// Calculate the new forward vector and rotate the model 
	glm::vec2 d;
	switch (rotateState) {
	case  CarRotateState::RIGHT:
		d = glm::rotate(glm::vec2(cForwardVector.x, cForwardVector.y), -maxAngle/2);
		cForwardVector.x = d.x;
		cForwardVector.y = d.y;
		cGameObject._angle = cGameObject._angle - maxAngle/2;
		cGameObject._rotation.z = 1.0f;
		
		rotateState = CarRotateState::STRAIGHT;
		break;
	case CarRotateState::LEFT:
		d = glm::rotate(glm::vec2(cForwardVector.x, cForwardVector.y), maxAngle/2);
		cForwardVector.x = d.x;
		cForwardVector.y = d.y;
		cGameObject._angle = cGameObject._angle + maxAngle/2.0f;
		cGameObject._rotation.z = 1.0f;

		rotateState = CarRotateState::STRAIGHT;
		break;
	case CarRotateState::AXIS:

	case CarRotateState::STRAIGHT: 
		break;
	}

	// update the bounding box
	cBoundingBox.setCenter(cGameObject._translate.x, cGameObject._translate.y);
	
	// Front bounding box
	glm::vec2 frontCenter = glm::vec2(cGameObject._translate.x, cGameObject._translate.y);
	frontCenter.x += cDistanceFrontBB * cForwardVector.x;
	frontCenter.y += cDistanceFrontBB * cForwardVector.y;
 	cFrontBBox.setCenter(frontCenter);
	
	// Middle bounding box
	cMiddleBBox.setCenter(cGameObject._translate.x, cGameObject._translate.y);
	// Back bounding box
	glm::vec2 backCenter = glm::vec2(cGameObject._translate.x, cGameObject._translate.y);
	backCenter.x -= cDistanceFrontBB * cForwardVector.x;
	backCenter.y -= cDistanceFrontBB * cForwardVector.y;
	cBackBBox.setCenter(backCenter.x, backCenter.y);
}

void Car::rotate(int axis) {
	if (axis == 0) {
		return;
	}
	std::cout << atan(axis / 185830) * 180 / 3.1415 << std::endl;
}


float Car::getHeight() {
	return cHeight;
}

float Car::getWidth() {
	return cWidth;
}


void Car::rotateCarInMenu() {
	cGameObject._angle += 0.01f;
}
