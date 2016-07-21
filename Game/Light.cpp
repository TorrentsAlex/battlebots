#include "Light.h"

Light::Light() {}

Light::Light(glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular) {
	lAmbient = ambient;
	lDiffuse = diffuse;
	lSpecular = specular;
}

Light::Light(glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, glm::vec3 direction, glm::vec3 position) {
	lAmbient = ambient;
	lDiffuse = diffuse;
	lSpecular = specular;
	lDirection = direction;
	lPosition = position;
}

Light::~Light() {
}

void Light::setDirection(glm::vec3 direction) {
	lDirection = direction;
}

void Light::setPosition(glm::vec3 position) {
	lPosition = position;
}

void Light::setAmbient(glm::vec3 ambient) {
	lAmbient = ambient;
}

void Light::setDiffuse(glm::vec3 diffuse) {
	lDiffuse = diffuse;
}

void Light::setSpecular(glm::vec3 specular) { 
	lSpecular = specular; 
}

void Light::setPower(float power) {
	lPower = power;
}

// Getters
glm::vec3 Light::getAmbient() {
	return lAmbient;
}

glm::vec3 Light::getDiffuse() {
	return lDiffuse;
}

glm::vec3 Light::getSpecular() {
	return lSpecular;
}

float Light::getPower() {
	return lPower;
}

int Light::getType() {
	return lType;
}

glm::vec3 Light::getPosition() {
	return lPosition;
}

glm::vec3 Light::getDirection() {
	return lDirection;
}