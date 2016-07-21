#pragma once
#include "Light.h"

class PointLight: public Light {
private:    
	float pConstant;
	float pLinear;
	float pQuadratic;
	float pAttenuation;
	float pCutoff;
	void init();
public:
	PointLight();
	PointLight(glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular);

	~PointLight();

	float getConstant();
	float getLinear();
	float getQuadratic();
	float getCutoff();

	void setAttenuation(float constant, float linear, float quadratic);
	void setConstant(float constant);
	void setLinear(float linear);
	void setQuadratic(float quadratic);
	void setCutoff(float cutoff);
	void setType(int type);
};

