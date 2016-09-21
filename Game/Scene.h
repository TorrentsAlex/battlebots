#pragma once

#include "Object.h"
#include "Immovable.h"

class Scene {

private:
	Object robot1;

	Immovable skyBox;
	Immovable Terrain;
public:
	Scene();
	~Scene();
};

