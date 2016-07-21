#include "PointLight.h"



PointLight::PointLight(): Light() {
	init();
}

PointLight::PointLight(glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular): 
	Light(ambient, diffuse, specular) {
	init();
}

PointLight::~PointLight() {
}

void PointLight::init() {
	lType = LIGHT_POINT;
}

// Setters
void PointLight::setConstant(float constant) {
	pConstant = constant;
}

void PointLight::setLinear(float linear) {
	pLinear = linear;
}

void PointLight::setQuadratic(float quadratic) {
	pQuadratic = quadratic;
}

void PointLight::setAttenuation(float constant, float linear, float quadratic) {
	pQuadratic = quadratic;
}

void PointLight::setCutoff(float cutoff) {
	pCutoff = cutoff;
}

void PointLight::setType(int type) {
	lType = type;
}

// Getters
float PointLight::getCutoff() {
	return pCutoff;
}
float PointLight::getConstant() {
	return pConstant;
}

float PointLight::getLinear() {
	return pLinear;
}

float PointLight::getQuadratic() {
	return pQuadratic;
}