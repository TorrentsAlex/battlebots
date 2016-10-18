#include "PlayersScreen.h"

#include "InputManager.h"
#include "SceneObjects.h"

void PlayersScreen::init() {
	playersScene = SceneCreator::Instance().createScene("./resources/scenes/Scene2.json");

	InputManager::Instance().getGameController(*SceneObjects::Instance().getPlayerAt(0)->getGamePad());
	InputManager::Instance().getGameController(*SceneObjects::Instance().getPlayerAt(1)->getGamePad());
	InputManager::Instance().getGameController(*SceneObjects::Instance().getPlayerAt(2)->getGamePad());
	InputManager::Instance().getGameController(*SceneObjects::Instance().getPlayerAt(3)->getGamePad());

}


void PlayersScreen::input() {
	if (InputManager::Instance().isKeyPressed(*SceneObjects::Instance().getPlayerAt(0)->getGamePad(), SDL_CONTROLLER_BUTTON_START)) {
		// player 1 in game
		SceneObjects::Instance().getPlayerAt(0)->inGame = true;
	}
	if (InputManager::Instance().isKeyPressed(*SceneObjects::Instance().getPlayerAt(1)->getGamePad(), SDL_CONTROLLER_BUTTON_START)) {
		// player 2 in game
		SceneObjects::Instance().getPlayerAt(1)->inGame = true;
	}
	if (InputManager::Instance().isKeyPressed(*SceneObjects::Instance().getPlayerAt(2)->getGamePad(), SDL_CONTROLLER_BUTTON_START)) {
		// player 3 in game
		SceneObjects::Instance().getPlayerAt(2)->inGame = true;
	}
	if (InputManager::Instance().isKeyPressed(*SceneObjects::Instance().getPlayerAt(3)->getGamePad(), SDL_CONTROLLER_BUTTON_START)) {
		// player 4 in game
		SceneObjects::Instance().getPlayerAt(3)->inGame = true;
	}
}

void PlayersScreen::update() {

}

void PlayersScreen::render() {

	TurriFramework::Instance().startRender();

	TurriFramework::Instance().renderCamera();


	TurriFramework::Instance().renderScene(playersScene);
	TurriFramework::Instance().stopRender();
	// Players Selector
	// RENDER
}

void PlayersScreen::clean() {

}

void PlayersScreen::goToMode() {
	GameController::Instance().changeState(GameState::MODE);
}


