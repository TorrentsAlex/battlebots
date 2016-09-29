#pragma once
#include <iostream>
#include "Vertex.h"
#include "GameObject.h"
#include "Geometry.h"
#include "Sphere.h"
#include "Camera.h"
#include <glm/gtx/rotate_vector.hpp>
#include "MaterialManager.h"

enum class CarVelocityState { STOP, ACCELERATE, BRAKE, REVERSE, DESACCELERATE, BOUNCE};
enum class CarRotateState {STRAIGHT, RIGHT, LEFT, AXIS};

class Car  {
private:
	float life = 100;
	float cSpeed = 0.001f;
	float cBrake = 0.007f;

	float cVelocity = 0;
	float cVelocityMax = 5;

	float cWidth;
	float cHeight;

	CarVelocityState state = CarVelocityState::STOP;
	CarRotateState rotateState = CarRotateState::STRAIGHT;
	bool isBouncing;
	int counterBouncing = 0;

	const float maxAngle = 2;
	float axisAngle;
	double legAdjacent = 0;
	const float legOpossite = 32767; // Max of the joystick axis

	glm::vec2 cBounceVector;
	glm::vec2 cMaxBounceDistance;
	OBJ cObject;
	GameObject cGameObject;
	Sphere cBoundingBox;
	float cDistanceFrontBB;
	Sphere cFrontBBox;
	Sphere cMiddleBBox;
	Sphere cBackBBox;
	Material cMaterial;

	// Missing variables

	// Forward vector
	// The vertices
	// Bounding box's
	// Position
	// Length
	// and more...
	glm::vec3 cForwardVector;

	string cTexturePath;
	GLuint cTextureId;
public:
	Car();
	~Car();

	// Setters
	void setGameObject(GameObject gObject);
	void setPosition(glm::vec3 pos);
	void setOBJ(OBJ obj);
	void setTextureId(string texturePath);
	void setTextureId(GLuint textureId);
	void setMaterial(Material material);
	Material getMaterial();

	// Getters
	Vertex * getMesh();
	int getNumVertices();
	GameObject getGameObject();
	float getLife();
	GLuint getTextureId();

	glm::vec3 getPosition();
	float getXPosition();
	float getYPosition();
	glm::vec3 getForwardVector();

	Sphere getBoundingBox();
	Sphere getFrontBoundingBox();
	Sphere getMiddleBoundingBox();
	Sphere getBackBoundingBox();
	float getVelocity();
	float getHeight();
	float getWidth();

	void restartLife();
	void substractLife(float damage);
	void restartPosition();

	// Physics methods
	void accelerate();
	void desaccelerate();
	void brake();

	void left();
	void right();

	void rotate(int axis);

	void update();

	void launchCar(glm::vec2 vector);

	void rotateCarInMenu();
};

