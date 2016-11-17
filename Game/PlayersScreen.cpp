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
	TurriFramework::Instance().setCameraPosition(glm::vec3(0, -170, 100));
	WorldObjects::Instance().getPlayerAt(0)->inGame = true;
	WorldObjects::Instance().setCollisionsToWorld();
}


void PlayersScreen::input() {
	InputManager::Instance().handleInput(*WorldObjects::Instance().getPlayerAt(0)->getGamePad());
	InputManager::Instance().handleInput(*WorldObjects::Instance().getPlayerAt(1)->getGamePad());
	InputManager::Instance().handleInput(*WorldObjects::Instance().getPlayerAt(2)->getGamePad());
	InputManager::Instance().handleInput(*WorldObjects::Instance().getPlayerAt(3)->getGamePad());

	if (InputManager::Instance().isKeyPressed(WorldObjects::Instance().getPlayerAt(0)->getGamePad()->start)) {
		// player 1 in game


		WorldObjects::Instance().addCharacterToRender(*WorldObjects::Instance().getPlayerAt(0));
	}
	if (InputManager::Instance().isKeyPressed(WorldObjects::Instance().getPlayerAt(1)->getGamePad()->start)) {
		// player 2 in game
		WorldObjects::Instance().getPlayerAt(1)->inGame = true;
		WorldObjects::Instance().addCharacterToRender(*WorldObjects::Instance().getPlayerAt(1));
	}
	if (InputManager::Instance().isKeyPressed(WorldObjects::Instance().getPlayerAt(2)->getGamePad()->start)) {
		// player 3 in game
		WorldObjects::Instance().getPlayerAt(2)->inGame = true;
		WorldObjects::Instance().addCharacterToRender(*WorldObjects::Instance().getPlayerAt(2));
	}
	if (InputManager::Instance().isKeyPressed(WorldObjects::Instance().getPlayerAt(3)->getGamePad()->start)) {
		// player 4 in game
		WorldObjects::Instance().getPlayerAt(3)->inGame = true;
		WorldObjects::Instance().addCharacterToRender(*WorldObjects::Instance().getPlayerAt(3));
	}
	
	// PLAY!!
	if (InputManager::Instance().isKeyPressed(WorldObjects::Instance().getPlayerAt(0)->getGamePad()->buttonY)) {
		cout << "play!!!" << endl;
		GameController::Instance().changeState(GameState::PLAY);
	}

	// MOVING CAMERA

	//GamePad* gamePad = WorldObjects::Instance().getPlayerAt(0)->getGamePad();
	//glm::vec3 position = TurriFramework::Instance().getCameraPosition();
	//if (InputManager::Instance().isKeyPressed(*gamePad, SDL_CONTROLLER_BUTTON_DPAD_UP)) {
	//	position.y += 1;
	//}
	//if (InputManager::Instance().isKeyPressed(*gamePad, SDL_CONTROLLER_BUTTON_DPAD_DOWN)) {
	//	position.y -= 1;
	//}
	//if (InputManager::Instance().isKeyPressed(*gamePad, SDL_CONTROLLER_BUTTON_DPAD_LEFT)) {
	//	position.x -= 1;
	//}
	//if (InputManager::Instance().isKeyPressed(*gamePad, SDL_CONTROLLER_BUTTON_DPAD_RIGHT)) {
	//	position.x += 1;
	//}
	//if (InputManager::Instance().isKeyPressed(*gamePad, SDL_CONTROLLER_BUTTON_RIGHTSHOULDER)) {
	//	position.z += 1;
	//}
	//if (InputManager::Instance().isKeyPressed(*gamePad, SDL_CONTROLLER_BUTTON_LEFTSHOULDER)) {
	//	position.z -= 1;
	//}

	//TurriFramework::Instance().setCameraPosition(position);

}

void PlayersScreen::update() {
	WorldObjects::Instance().update();
}

void PlayersScreen::render() {

	WorldObjects::Instance().render();
}

void PlayersScreen::clean() {

}