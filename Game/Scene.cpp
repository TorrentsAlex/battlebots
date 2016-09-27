#include "Scene.h"

Scene::Scene() {
}


Scene::~Scene() {
}

void Scene::setSkyBox(OBJ object, GLuint texture) {
	GameObject terrainObject;
	terrainObject._angle = 0;
	terrainObject._translate = glm::vec3(0, 0, 0);
	terrainObject._scale = glm::vec3(1, 1, 1);
	terrainObject._rotation = glm::vec3(0, 0, 0);

	sSkybox.setOBJ(object);
	sSkybox.setTextureId(texture);
	sSkybox.setGameObject(terrainObject);
}

void Scene::setRobots(Entity robots) {
	sRobot1 = robots;
}

void Scene::setTerrain(OBJ object, GLuint texture, Material material) {
	GameObject terrainObject;
	terrainObject._angle = 0;
	terrainObject._translate = glm::vec3(0, 0, 0);
	terrainObject._scale = glm::vec3(1, 1, 1);
	terrainObject._rotation = glm::vec3(0, 0, 0);

	sTerrain.setOBJ(object);
	sTerrain.setMaterial(material);
	sTerrain.setTextureId(texture);
	sTerrain.setGameObject(terrainObject);
}

void Scene::setDecoration(std::vector<Entity> decoration) {
	sDecoration = decoration;
}

// Getters
Entity Scene::getRobots() {
	return sRobot1;
}

Entity Scene::getTerrain() {
	return sTerrain;
}

Entity Scene::getSkyBox() {
	return sSkybox;
}

std::vector<Entity> Scene::getDecoration() {
	return sDecoration;
}

// 
void Scene::update() {


}