#include "GameController.h"

void GameController::init() {
	changeState(GameState::MENU);
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
	case GameState::EXIT:
		TurriFramework::Instance().quit();
	}

}

void GameController::input() {
	InputManager::Instance().handleInput();
	gCurrentScreen.input();
}

void GameController::update() {
	gCurrentScreen.update();
}

void GameController::render() {
	gCurrentScreen.render();
}