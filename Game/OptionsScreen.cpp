#include "OptionsScreen.h"




void OptionsScreen::init() {
	optionsScene = SceneCreator::Instance().createScene("./resources/scenes/Scene2.json");
}

void OptionsScreen::input() {

}

void OptionsScreen::update() {

}

void OptionsScreen::render() {

	TurriFramework::Instance().startRender();

	TurriFramework::Instance().renderCamera();


	TurriFramework::Instance().renderScene(optionsScene);
	TurriFramework::Instance().stopRender();
	// Resolution + Volumen
	// RENDER
	SDL_Delay(3000);
	goToMenu();

}

void OptionsScreen::clean() {

}

void OptionsScreen::goToMenu() {
	GameController::Instance().changeState(GameState::MENU);
}