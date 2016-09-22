#pragma once

#include "Entity.h"
#include "Immovable.h"

class Scene {

private:
	Entity robot1;

	Immovable skyBox;
	Immovable Terrain;

public:
	Scene();
	~Scene();
};

