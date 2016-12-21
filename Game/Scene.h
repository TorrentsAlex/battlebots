#pragma once

#include <btBulletDynamicsCommon.h>
#include <btBulletCollisionCommon.h>

#include "Entity.h"

#include "Light.h"

struct DecorObjects {
	Entity* e;
	vector<GameObject> g;
};

class Scene {
private:
	Entity sSkybox;
	Entity sTerrain;
	
	vector<Entity> sDecoration;

	vector<Light> sLights;

	// Bullet physics
	btDiscreteDynamicsWorld* wDynamicWorld;
	btCollisionWorld* wCollisionWorld;

public:
	Scene();
	~Scene();
	
	vector<DecorObjects> listObjects;
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


	void addBodyToDynamicWorld(btRigidBody* body);

	void clean();
	void update();
};

