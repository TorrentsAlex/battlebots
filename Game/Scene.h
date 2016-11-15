#pragma once

#include "Entity.h"

#include "Light.h"

class Scene {
private:
	Entity sSkybox;

	Entity sTerrain;
	
	vector<Entity> sDecoration;

	vector<Light> sLights;

public:
	Scene();
	~Scene();
	
	// Setters
	void setSkyBox(OBJ object, GLuint texture);
	void setTerrain(OBJ object, GLuint texture, Material material);
	void setDecoration(vector<Entity> decoration);
	void setLights(vector<Light> lights);

	// Getters
	Entity getTerrain();
	Entity getSkyBox();
	vector<Entity> getDecoration();
	vector<Light> getLights();

	void clean();
	void update();
};

