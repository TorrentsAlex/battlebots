#include "Scene.h"

Scene::Scene() {
}


Scene::~Scene() {
}

void Scene::setSkyBox(OBJ object, GLuint texture) {
	GameObject skyObject;
	skyObject._angle = 0;
	skyObject._translate = glm::vec3(0, 0, 0);
	skyObject._scale = glm::vec3(1, 1, 1);
	skyObject._rotation = glm::vec3(0, 0, 0);

	sSkybox.setOBJ(object);
	sSkybox.setTextureId(texture);
	sSkybox.setGameObject(skyObject);
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

void Scene::clean() {
}

// 
void Scene::update() {

}