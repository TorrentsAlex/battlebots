#include "InitScreen.h"


void InitScreen::init() {
	menuScene = new Scene();
	SceneCreator::Instance().createScene("./resources/scenes/Scene1.json", *menuScene);
	//SceneCreator::Instance().createScene("./resources/scenes/Scene1.json", *SceneObjects::Instance().getCurrentScene());

	vector<Button> iButtons = SceneCreator::Instance().createButtons("./resources/scenes/menu_buttons.json");
	
	iBManager.setButtons(iButtons);
	iBManager.init();


	TurriFramework::Instance().setCameraPosition(glm::vec3(0, -100, 70));
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
