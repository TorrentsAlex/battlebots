#include "GameController.h"


bool GameController::isRunning() {
	if (gGameState == GameState::EXIT) {
		return false;
	}
	return true;
}

void GameController::changeState(GameState nextstate) {
	switch(nextstate) {
	case GameState::MENU:
		gCurrentScreen.changestate(new InitScreen());
		break;
	case GameState::PLAY:
		gCurrentScreen.changestate(new Game());
		break;
	case GameState::OPTIONS:
		gCurrentScreen.changestate(new OptionsScreen());
		break;
	case GameState::PLAYERS:
		gCurrentScreen.changestate(new PlayersScreen());
		break;
	case GameState::MODE:
		gCurrentScreen.changestate(new ModeScreen());
		break;
	case GameState::ARENA:
		gCurrentScreen.changestate(new ArenaScreen());
		break;
	}

}

void GameController::init() {
	changeState(GameState::MENU);
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