#include "GameController.h"



bool GameController::isRunning() {
	return running;
}

void GameController::init(string name, int screenWidth, int screenheight, bool enableLimiterFPS, int maxFPS, bool printFPS) {
	running = true;
	TurriFramework::Instance().init();
}

void GameController::input() {}

void GameController::update() {}

void GameController::render() {}