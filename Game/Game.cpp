#include "Game.h"

#include "SceneObjects.h"

void Game::init() {
	cout << "init game" << endl;
	
}

void Game::input() {
	SceneObjects::Instance().handleInputs();
}

void Game::update() {
	SceneObjects::Instance().update();
}

void Game::render() {

	SceneObjects::Instance().render();

}

void Game::clean() {
}

