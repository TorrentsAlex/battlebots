#pragma once

#include "Entity.h"

class Scene {

private:
	Entity sSkybox;
	Entity sRobot1;

	Entity sTerrain;
	
	std::vector<Entity> sDecoration;

public:
	Scene();
	~Scene();
	
	// Setters
	void setSkyBox(OBJ object, GLuint texture);
	void setRobots(Entity robots);
	void setTerrain(OBJ object, GLuint texture, Material material);
	void setDecoration(std::vector<Entity> decoration);

	// Getters
	Entity getRobots();
	Entity getTerrain();
	Entity getSkyBox();
	std::vector<Entity> getDecoration();


	void update();
};

