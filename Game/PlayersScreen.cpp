#include "PlayersScreen.h"

#include "InputManager.h"
#include "SceneObjects.h"

void PlayersScreen::init() {

	SceneCreator::Instance().createScene("./resources/scenes/Scene2.json", *SceneObjects::Instance().getCurrentScene());
	
	SceneCreator::Instance().createCharacters("./resources/scenes/character.json", 
		*SceneObjects::Instance().getPlayerAt(0),
		*SceneObjects::Instance().getPlayerAt(1), 
		*SceneObjects::Instance().getPlayerAt(2), 
		*SceneObjects::Instance().getPlayerAt(3));

	InputManager::Instance().getGameController(*SceneObjects::Instance().getPlayerAt(0)->getGamePad());
	InputManager::Instance().getGameController(*SceneObjects::Instance().getPlayerAt(1)->getGamePad());
	InputManager::Instance().getGameController(*SceneObjects::Instance().getPlayerAt(2)->getGamePad());
	InputManager::Instance().getGameController(*SceneObjects::Instance().getPlayerAt(3)->getGamePad());

}


void PlayersScreen::input() {
	if (InputManager::Instance().isKeyPressed(*SceneObjects::Instance().getPlayerAt(0)->getGamePad(), SDL_CONTROLLER_BUTTON_START)) {
		// player 1 in game
		SceneObjects::Instance().getPlayerAt(0)->inGame = true;
		SceneObjects::Instance().addCharacterToRender(*SceneObjects::Instance().getPlayerAt(0));
	}
	if (InputManager::Instance().isKeyPressed(*SceneObjects::Instance().getPlayerAt(1)->getGamePad(), SDL_CONTROLLER_BUTTON_START)) {
		// player 2 in game
		SceneObjects::Instance().getPlayerAt(1)->inGame = true;
		SceneObjects::Instance().addCharacterToRender(*SceneObjects::Instance().getPlayerAt(1));
	}
	if (InputManager::Instance().isKeyPressed(*SceneObjects::Instance().getPlayerAt(2)->getGamePad(), SDL_CONTROLLER_BUTTON_START)) {
		// player 3 in game
		SceneObjects::Instance().getPlayerAt(2)->inGame = true;
		SceneObjects::Instance().addCharacterToRender(*SceneObjects::Instance().getPlayerAt(2));
	}
	if (InputManager::Instance().isKeyPressed(*SceneObjects::Instance().getPlayerAt(3)->getGamePad(), SDL_CONTROLLER_BUTTON_START)) {
		// player 4 in game
		SceneObjects::Instance().getPlayerAt(3)->inGame = true;
		SceneObjects::Instance().addCharacterToRender(*SceneObjects::Instance().getPlayerAt(3));
	}
	
	// PLAY!!
	if (InputManager::Instance().isKeyPressed(*SceneObjects::Instance().getPlayerAt(0)->getGamePad(), SDL_CONTROLLER_BUTTON_X)) {
		GameController::Instance().changeState(GameState::PLAY);
	}
}

void PlayersScreen::update() {

}

void PlayersScreen::render() {

	SceneObjects::Instance().render();
}

void PlayersScreen::clean() {

}