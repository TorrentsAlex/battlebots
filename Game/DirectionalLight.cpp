#include "DirectionalLight.h"

DirectionalLight::DirectionalLight() {}

DirectionalLight::DirectionalLight(glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular) :
	Light(ambient, diffuse, specular) {
	lType = LIGHT_DIRECTIONAL;
}

DirectionalLight::~DirectionalLight() {
}
