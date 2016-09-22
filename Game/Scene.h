#pragma once

#include "Entity.h"

class Scene {

private:
	Entity sRobot1;

	Entity sTerrain;
	
	std::vector<Entity> sDecoration;

public:
	Scene();
	~Scene();
	
	// Setters
	void setRobots(Entity robots);
	void setTerrain(Entity terrain);
	void setDecoration(std::vector<Entity> decoration);

	// Getters
	Entity getRobots();
	Entity getTerrain();
	std::vector<Entity> getDecoration();


	void update();
};

