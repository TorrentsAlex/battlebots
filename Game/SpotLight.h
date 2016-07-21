#pragma once
#include "PointLight.h"
class SpotLight: public PointLight {
private:
	float sCutoff;
public:
	SpotLight();
	SpotLight(glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular);
	~SpotLight();

	void setCutOff(float cutoff);
	float getCutOff();
};

