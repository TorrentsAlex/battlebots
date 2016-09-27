#include "Game.h"

void Game::init() {
	cout << "init game" << endl;
	gScene = SceneCreator::Instance().createScene("./resources/scenes/Scene2.json");

	// ADd some lights
	Light light;
	light.setAmbient(glm::vec3(1.4f, 1.5f, 1.4f));
	light.setDiffuse(glm::vec3(1.0f, 1.1f, 0.3f));
	light.setSpecular(glm::vec3(2.2f, 2.5f, 2.3f));
	light.setDirection(glm::vec3(0.8f, 0.8f, -0.8f));
	lights.push_back(light);
}


void Game::input() {
}

void Game::update() {
	gScene.update();
}

void Game::render() {
	TurriFramework::Instance().startRender();

	TurriFramework::Instance().renderCamera();

	TurriFramework::Instance().renderScene(lights, gScene);
	TurriFramework::Instance().stopRender();

}

void Game::clean() {
	
}

