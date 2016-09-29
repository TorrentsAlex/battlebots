#include "PlayersScreen.h"


void PlayersScreen::init() {
	playersScene = SceneCreator::Instance().createScene("./resources/scenes/Scene2.json");
}


void PlayersScreen::input() {

}

void PlayersScreen::update() {

}

void PlayersScreen::render() {

	TurriFramework::Instance().startRender();

	TurriFramework::Instance().renderCamera();


	TurriFramework::Instance().renderScene(playersScene);
	TurriFramework::Instance().stopRender();
	// Players Selector
	// RENDER
	SDL_Delay(3000);
	goToMode();

}

void PlayersScreen::clean() {

}

void PlayersScreen::goToMode() {
	GameController::Instance().changeState(GameState::MODE);
}


