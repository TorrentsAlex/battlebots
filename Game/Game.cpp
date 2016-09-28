#include "Game.h"

void Game::init() {
	cout << "init game" << endl;
	gScene = SceneCreator::Instance().createScene("./resources/scenes/Scene2.json");
}


void Game::input() {
}

void Game::update() {
	gScene.update();
}

void Game::render() {
	TurriFramework::Instance().startRender();

	TurriFramework::Instance().renderCamera();

	TurriFramework::Instance().renderScene(gScene);
	TurriFramework::Instance().stopRender();

}

void Game::clean() {
	gScene.clean();
}

