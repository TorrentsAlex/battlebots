#include "ModeScreen.h"


void ModeScreen::init() {
//	modeScreen = SceneCreator::Instance().createScene("./resources/scenes/Scene2.json");
}

void ModeScreen::input() {

}

void ModeScreen::update() {

}

void ModeScreen::render() {

	TurriFramework::Instance().startRender();

	TurriFramework::Instance().renderCamera();


	TurriFramework::Instance().renderScene(modeScreen);
	TurriFramework::Instance().stopRender();
	// Mode Selector
	// RENDER
	SDL_Delay(3000);
	goToArena();

}

void ModeScreen::clean() {

}

void ModeScreen::goToArena() {
	GameController::Instance().changeState(GameState::ARENA);
}
