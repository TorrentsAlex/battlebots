#include "GameController.h"


bool GameController::isRunning() {
	if (gGameState == GameState::EXIT) {
		return false;
	}
	return true;
}

void GameController::init() {
	gGameState = GameState::PLAY;
	gCurrentScreen.changestate(new Game());
}

void GameController::input() {
	gCurrentScreen.input();
}

void GameController::update() {
	gCurrentScreen.update();
}

void GameController::render() {
	gCurrentScreen.render();
}