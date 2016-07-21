#pragma once
#include <iostream>

#include "Object.h"

class Terrain: public Object {
public:
	Terrain();
	Terrain(OBJ* obj, GameObject gameObject);
	~Terrain();

	void paintVertex(std::vector<glm::vec3> vertex, glm::vec3 color);
};

