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
	
	//gamePad = new GamePad();
	//gamePad->gameController = SDL_GameControllerOpen(0);

}

void InitScreen::input() {

	if (InputManager::Instance().isKeyPressed(SDLK_UP)) {
		iBManager.upButton();
	} 
	if (InputManager::Instance().isKeyPressed(SDLK_DOWN)) {
		iBManager.downButton();
	}
	if (InputManager::Instance().isKeyPressed(SDLK_RETURN)) {
		string currentButton = iBManager.getCurrentButton();

		if (currentButton.compare("start") == 0) {
			GameController::Instance().changeState(GameState::PLAYERS);
		}// goToPlayers;
		if (currentButton.compare("options") == 0) {
			GameController::Instance().changeState(GameState::OPTIONS);
		}// goToOptions;
		if (currentButton.compare("exit") == 0) {
			GameController::Instance().changeState(GameState::EXIT);
		}
	}

	////
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
	//cout << position.x << "/" << position.y << "/" << position.z << endl;

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

	TurriFramework::Instance().renderScene(*menuScene);

	vector<Button> buttons = iBManager.getButtons();
	for (int i = 0; i < buttons.size(); i++) {
		TurriFramework::Instance().renderEntity(buttons.at(i));
	}

	// Render the skybox without lights
	TurriFramework::Instance().disableLights();

	TurriFramework::Instance().renderEntity(menuScene->getSkyBox());

	TurriFramework::Instance().stopRender();
}

void InitScreen::clean() {

}
