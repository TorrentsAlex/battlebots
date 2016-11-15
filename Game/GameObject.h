#pragma once
#include <glm/glm.hpp>			//OpenGL Mathematics 

struct GameObject {
	glm::vec3 _translate;
	float _angle;
	glm::vec3 _rotation;
	glm::vec3 _scale;
};
