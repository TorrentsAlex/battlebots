#include "Game.h"

#include "WorldObjects.h"

void Game::init() {
	cout << "init game" << endl;
	
}

void Game::input() {
	WorldObjects::Instance().handleInputs();
}

void Game::update() {
	WorldObjects::Instance().update();
}

void Game::render() {

	WorldObjects::Instance().render();

}

void Game::clean() {
}

