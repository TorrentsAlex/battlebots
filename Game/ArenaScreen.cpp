#include "ArenaScreen.h"


void ArenaScreen::init() {
	arenaScene = SceneCreator::Instance().createScene("./resources/scenes/Scene2.json");
}

void ArenaScreen::input() {

}

void ArenaScreen::update() {

}

void ArenaScreen::render() {


	TurriFramework::Instance().startRender();

	TurriFramework::Instance().renderCamera();


	TurriFramework::Instance().renderScene(arenaScene);
	TurriFramework::Instance().stopRender();
	// Arena Selector
	// RENDER
	SDL_Delay(3000);
	goToPlay();


}

void ArenaScreen::clean() {

}

void ArenaScreen::goToPlay() {
	GameController::Instance().changeState(GameState::PLAY);
}