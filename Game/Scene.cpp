#include "Scene.h"

#include <BulletCollision/Gimpact/btGImpactCollisionAlgorithm.h>

Scene::Scene() {

	btBroadphaseInterface* broadPhase = new btDbvtBroadphase();

	btDefaultCollisionConfiguration* collisionConfiguration = new btDefaultCollisionConfiguration();
	btCollisionDispatcher* dispatcher = new btCollisionDispatcher(collisionConfiguration);

	// Include btGImpactCollisionAlgorithm
	btGImpactCollisionAlgorithm::registerAlgorithm(dispatcher);

	btSequentialImpulseConstraintSolver* solver = new btSequentialImpulseConstraintSolver;

	wDynamicWorld = new btDiscreteDynamicsWorld(dispatcher, broadPhase, solver, collisionConfiguration);

	wDynamicWorld->setGravity(btVector3(0, 0, -10));
}


Scene::~Scene() {
}

void Scene::setSkyBox(OBJ object, GLuint texture, btCollisionObject* collObject) {
	GameObject skyObject;
	skyObject.angle = 0;
	skyObject.translate = glm::vec3(0, 0, 0);
	skyObject.scale = glm::vec3(4, 4, 4);
	skyObject.rotation = glm::vec3(0, 0, 0);
	
	skyObject.collisionObject = collObject;

	sSkybox.setOBJ(object);
	sSkybox.setTextureId(texture);
	sSkybox.setGameObject(skyObject);
}

void Scene::setTerrain(OBJ object, GLuint texture, Material material, btCollisionObject* collObject) {
	GameObject terrainObject;
	terrainObject.angle = 0;
	terrainObject.translate = glm::vec3(0, 0, 0);
	terrainObject.scale = glm::vec3(1, 1, 1);
	terrainObject.rotation = glm::vec3(0, 0, 0);

	terrainObject.collisionObject = collObject;

	sTerrain.setOBJ(object);
	sTerrain.setMaterial(material);
	sTerrain.setTextureId(texture);
	sTerrain.setGameObject(terrainObject);
}

void Scene::setDecoration(std::vector<Entity> decoration) {
	sDecoration = decoration;
}

void Scene::setLights(vector<Light> lights) {
	sLights = lights;
}

// Getters
Entity Scene::getTerrain() {
	return sTerrain;
}

Entity Scene::getSkyBox() {
	return sSkybox;
}

std::vector<Entity> Scene::getDecoration() {
	return sDecoration;
}

vector<Light> Scene::getLights() {
	return sLights;
}

void Scene::addBodyToDynamicWorld(btRigidBody * body) {
	wDynamicWorld->addRigidBody(body);
}

void Scene::clean() {
	if (wDynamicWorld) delete wDynamicWorld;

}

// 
void Scene::update() {
	wDynamicWorld->stepSimulation(1/60.0f);
}