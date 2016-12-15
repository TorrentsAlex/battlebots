#include "InitScreen.h"


void InitScreen::init() {
	menuScene = new Scene();
	SceneCreator::Instance().createScene("./resources/scenes/Scene1.json", *menuScene);
	//SceneCreator::Instance().createScene("./resources/scenes/Scene1.json", *SceneObjects::Instance().getCurrentScene());

	vector<Button> iButtons = SceneCreator::Instance().createButtons("./resources/scenes/menu_buttons.json");
	
	iBManager.setButtons(iButtons);
	iBManager.init();


	TurriFramework::Instance().setCameraLookAt(glm::vec3(0, 0, 20));
	TurriFramework::Instance().setCameraPosition(glm::vec3(-46, -50, 20));
	//
	gamePad = new GamePad();
	gamePad->gameController = SDL_GameControllerOpen(0);

}

void InitScreen::input() {
	// update the gamepad state
	InputManager::Instance().handleInput(*gamePad);

	if (InputManager::Instance().isKeyPressed(SDLK_UP) ||
		InputManager::Instance().isKeyPressed(gamePad->dPadUp)) {
		iBManager.upButton();
		cout << "up button" << endl;
	} 
	if (InputManager::Instance().isKeyPressed(SDLK_DOWN) ||
		InputManager::Instance().isKeyPressed(gamePad->dPadDown)) {
		iBManager.downButton();
		cout << "down button" << endl;
	}
	if (InputManager::Instance().isKeyPressed(SDLK_RETURN) ||
		InputManager::Instance().isKeyPressed(gamePad->buttonA)) {
		string currentButton = iBManager.getCurrentButton();

		if (currentButton.compare("start") == 0) {
			GameController::Instance().changeState(GameState::PLAYERS); 
			return;
		}// goToPlayers;
		if (currentButton.compare("options") == 0) {
			GameController::Instance().changeState(GameState::OPTIONS); 
			return;
		}// goToOptions;
		if (currentButton.compare("exit") == 0) {
			GameController::Instance().changeState(GameState::EXIT);
			return;
		}
	}

	////

	//
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

void InitScreen::update() {

}

void InitScreen::render() {

	TurriFramework::Instance().startRender();
	// Render camera and projections views
	TurriFramework::Instance().renderCamera();
	
	// send the lights to shaders
	TurriFramework::Instance().renderLights(menuScene->getLights());

	TurriFramework::Instance().renderScene(menuScene);

	vector<Button> buttons = iBManager.getButtons();
	for (int i = 0; i < buttons.size(); i++) {
		TurriFramework::Instance().renderEntity(&buttons.at(i));
	}

	// Render the skybox without lights
	TurriFramework::Instance().disableLights();

	TurriFramework::Instance().renderEntity(&menuScene->getSkyBox());

	TurriFramework::Instance().stopRender();
}

void InitScreen::clean() {
	SDL_GameControllerClose(gamePad->gameController);
	gamePad->clean();
	delete gamePad;
}
