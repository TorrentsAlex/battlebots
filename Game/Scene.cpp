#include "Scene.h"

Scene::Scene() {
}


Scene::~Scene() {
}

void Scene::setSkyBox(OBJ object, GLuint texture) {
	sSkybox.setOBJ(object);
	sSkybox.setTextureId(texture);
}

void Scene::setRobots(Entity robots) {
	sRobot1 = robots;
}

void Scene::setTerrain(OBJ object, GLuint texture, Material material) {
	sTerrain.setOBJ(object);
	sTerrain.setMaterial(material);
	sTerrain.setTextureId(texture);
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