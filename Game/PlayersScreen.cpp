#include "PlayersScreen.h"

#include "InputManager.h"
#include "WorldObjects.h"

void PlayersScreen::init() {

	SceneCreator::Instance().createScene("./resources/scenes/Scene2.json", *WorldObjects::Instance().getCurrentScene());
	
	SceneCreator::Instance().createCharacters("./resources/scenes/character.json", 
		*WorldObjects::Instance().getPlayerAt(0),
		*WorldObjects::Instance().getPlayerAt(1), 
		*WorldObjects::Instance().getPlayerAt(2), 
		*WorldObjects::Instance().getPlayerAt(3));

	InputManager::Instance().getGameController(*WorldObjects::Instance().getPlayerAt(0)->getGamePad());
	InputManager::Instance().getGameController(*WorldObjects::Instance().getPlayerAt(1)->getGamePad());
	InputManager::Instance().getGameController(*WorldObjects::Instance().getPlayerAt(2)->getGamePad());
	InputManager::Instance().getGameController(*WorldObjects::Instance().getPlayerAt(3)->getGamePad());

	TurriFramework::Instance().setCameraLookAt(glm::vec3(0, 0, 0));
	TurriFramework::Instance().setCameraPosition(glm::vec3(0, -130, 100));

}


void PlayersScreen::input() {
	if (InputManager::Instance().isKeyPressed(*WorldObjects::Instance().getPlayerAt(0)->getGamePad(), SDL_CONTROLLER_BUTTON_START)) {
		// player 1 in game

		WorldObjects::Instance().getPlayerAt(0)->inGame = true;
		WorldObjects::Instance().setCollisionsToWorld();
		WorldObjects::Instance().addCharacterToRender(*WorldObjects::Instance().getPlayerAt(0));
	}
	if (InputManager::Instance().isKeyPressed(*WorldObjects::Instance().getPlayerAt(1)->getGamePad(), SDL_CONTROLLER_BUTTON_START)) {
		// player 2 in game
		WorldObjects::Instance().getPlayerAt(1)->inGame = true;
		WorldObjects::Instance().addCharacterToRender(*WorldObjects::Instance().getPlayerAt(1));
	}
	if (InputManager::Instance().isKeyPressed(*WorldObjects::Instance().getPlayerAt(2)->getGamePad(), SDL_CONTROLLER_BUTTON_START)) {
		// player 3 in game
		WorldObjects::Instance().getPlayerAt(2)->inGame = true;
		WorldObjects::Instance().addCharacterToRender(*WorldObjects::Instance().getPlayerAt(2));
	}
	if (InputManager::Instance().isKeyPressed(*WorldObjects::Instance().getPlayerAt(3)->getGamePad(), SDL_CONTROLLER_BUTTON_START)) {
		// player 4 in game
		WorldObjects::Instance().getPlayerAt(3)->inGame = true;
		WorldObjects::Instance().addCharacterToRender(*WorldObjects::Instance().getPlayerAt(3));
	}
	
	// PLAY!!
	if (InputManager::Instance().isKeyPressed(*WorldObjects::Instance().getPlayerAt(0)->getGamePad(), SDL_CONTROLLER_BUTTON_X)) {
		GameController::Instance().changeState(GameState::PLAY);
	}
}

void PlayersScreen::update() {
	WorldObjects::Instance().update();
}

void PlayersScreen::render() {

	WorldObjects::Instance().render();
}

void PlayersScreen::clean() {

}