#include "InitScreen.h"


void InitScreen::init() {

	menuScene = SceneCreator::Instance().createScene("./resources/scenes/Scene1.json");

	iButtons = SceneCreator::Instance().createButtons("./resources/scenes/menu_buttons.json");
	
	iBManager.setButtons(iButtons);
	iBManager.init();

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
			cout << "start" << endl;
		}// goToPlayers;
		if (currentButton.compare("options") == 0) { 
			cout << "options" << endl; 
		}// goToOptions;
		if (currentButton.compare("exit") == 0) {
			cout << "exit" << endl;
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
	TurriFramework::Instance().renderLights(menuScene.getLights());

	vector<Button> buttons = iBManager.getButtons();
		for (int i = 0; i < buttons.size(); i++) {
		TurriFramework::Instance().renderEntity(buttons.at(i));
	}
	TurriFramework::Instance().renderScene(menuScene);

	// Render the skybox without lights
	TurriFramework::Instance().disableLights();
	TurriFramework::Instance().renderEntity(menuScene.getSkyBox());


	TurriFramework::Instance().stopRender();
}

void InitScreen::clean() {

}

void InitScreen::goToOptions() {
	cout << "options" << endl;
	GameController::Instance().changeState(GameState::OPTIONS);
}

void InitScreen::goToPlayers() {
	cout << " play" << endl;
	GameController::Instance().changeState(GameState::PLAY);
}