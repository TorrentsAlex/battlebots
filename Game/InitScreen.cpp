#include "InitScreen.h"


void InitScreen::init() {
	menuScene = SceneCreator::Instance().createScene("./resources/scenes/Scene2.json");
}

void InitScreen::input() {

}

void InitScreen::update() {

}

void InitScreen::render() {

	TurriFramework::Instance().startRender();

	TurriFramework::Instance().renderCamera();


	TurriFramework::Instance().renderScene(menuScene);
	TurriFramework::Instance().stopRender();
	// 2 botons: Start + Options
	// RENDER
	SDL_Delay(3000);
	goToPlayers();

}

void InitScreen::clean() {

}

void InitScreen::goToOptions() {
	GameController::Instance().changeState(GameState::OPTIONS);
}

void InitScreen::goToPlayers() {
	GameController::Instance().changeState(GameState::PLAY);
}