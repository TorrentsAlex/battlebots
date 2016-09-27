#include "Game.h"

void Game::init() {
	cout << "init game" << endl;
	gScene = SceneCreator::Instance().createScene("./resources/scenes/Scene1.json");

	// ADd some lights
	Light light;
	light.setAmbient(glm::vec3(0.2f, 0.5f, 0.3f));
	light.setDiffuse(glm::vec3(0.2f, 0.5f, 0.3f));
	light.setSpecular(glm::vec3(0.2f, 0.5f, 0.3f));
	lights.push_back(light);
}


void Game::input() {
}

void Game::update() {
	gScene.update();
}

void Game::render() {
	TurriFramework::Instance().startRender();

	TurriFramework::Instance().renderScene(lights, gScene);
	TurriFramework::Instance().stopRender();

}

void Game::clean() {
	
}

