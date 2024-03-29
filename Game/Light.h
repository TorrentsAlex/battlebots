#pragma once
#include "Entity.h"

#define LIGHT_DIRECTIONAL 0
#define LIGHT_POINT 1
#define LIGHT_SPOT 2

class Light {
protected:
	int lType;
	
	// values for pointlights
	float lConstant;
	float lLinear;
	float lQuadratic;

	glm::vec3 lAmbient;
	glm::vec3 lDiffuse;
	glm::vec3 lSpecular;
	
	glm::vec3 lDirection;
	glm::vec3 lPosition;

	float lPower;

public:
	Light();
	Light(glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular);
	Light(glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, glm::vec3 direction, glm::vec3 position);
	~Light();

	void setDirection(glm::vec3 direction);
	void setPosition(glm::vec3 position);
	void setAmbient(glm::vec3 ambient);
	void setDiffuse(glm::vec3 diffuse);
	void setSpecular(glm::vec3 specular);
	void setPower(float power);
	// methods for pointlights
	void setConstant(float constant);
	void setLinear(float linear);
	void setQuadratic(float quadratic);

	void setType(string type);

	glm::vec3 getPosition();
	glm::vec3 getDirection();
	glm::vec3 getAmbient();
	glm::vec3 getDiffuse();
	glm::vec3 getSpecular();


	float getConstant();
	float getLinear();
	float getQuadratic();

	float getPower();

	int getType();

};

