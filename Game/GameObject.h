#pragma once
#include <glm/glm.hpp>			//OpenGL Mathematics 


struct GameObject {
	int _objectType;
	glm::vec3 _translate;
	float _angle;
	glm::vec3 _rotation;
	glm::vec3 _scale;
	bool _textureRepetition;
	float xTil;
	float yTil;
};