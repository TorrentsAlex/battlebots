#include "SpotLight.h"



SpotLight::SpotLight() {
}

SpotLight::SpotLight(glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular) :
	PointLight(ambient, diffuse, specular) {
}

SpotLight::~SpotLight() {
}

void SpotLight::setCutOff(float cutoff) {
	sCutoff = cutoff;
};

float SpotLight::getCutOff() {
	return sCutoff;
}
