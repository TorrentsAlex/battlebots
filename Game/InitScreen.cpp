#include "InitScreen.h"


void InitScreen::init() {
	// 
	initState = InitState::START;

	menuScene = SceneCreator::Instance().createScene("./resources/scenes/Scene1.json");

	iButtons = SceneCreator::Instance().createButtons("./resources/scenes/menu_buttons.json");
	iButtons.at(1).changeState();

}

void InitScreen::input() {

	if (InputManager::Instance().isKeyPressed(SDLK_UP)) {
		if (initState == InitState::OPTIONS) {
			initState = InitState::START;
			for (int i = 0; i < iButtons.size(); i++) {
				iButtons.at(i).changeState();
			}
		}
	} 
	if (InputManager::Instance().isKeyPressed(SDLK_DOWN)) {
		if (initState == InitState::START) {
			initState = InitState::OPTIONS;
			for (int i = 0; i < iButtons.size(); i++) {
				iButtons.at(i).changeState();
			}
		}
	}
	if (InputManager::Instance().isKeyPressed(SDLK_RETURN)) {
		if (initState == InitState::START) {
			goToPlayers();
		} else {
			goToOptions();
		}
	}

}

void InitScreen::update() {

}

void InitScreen::render() {

	TurriFramework::Instance().startRender();

	TurriFramework::Instance().renderCamera();
	for (int i = 0; i < iButtons.size(); i++) {
		TurriFramework::Instance().renderEntity(iButtons.at(i));
	}
	TurriFramework::Instance().renderScene(menuScene);
	TurriFramework::Instance().stopRender();
	// 2 botons: Start + Options

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