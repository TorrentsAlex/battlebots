#include "Scene.h"

Scene::Scene() {
}


Scene::~Scene() {
}

void Scene::setRobots(Entity robots) {
	sRobot1 = robots;
}

void Scene::setTerrain(Entity terrain) {
	sTerrain = terrain;
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

std::vector<Entity> Scene::getDecoration() {
	return sDecoration;
}

// 
void Scene::update() {


}