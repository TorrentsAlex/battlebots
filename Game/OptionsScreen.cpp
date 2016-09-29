#include "OptionsScreen.h"



OptionsScreen::OptionsScreen()
{
}


OptionsScreen::~OptionsScreen()
{
}

void OptionsScreen::init() {

}

void OptionsScreen::input() {

}

void OptionsScreen::update() {

}

void OptionsScreen::render() {
	// Resolution + Volumen
	// RENDER
	SDL_Delay(500);
	goToMenu();

}

void OptionsScreen::clean() {

}

void OptionsScreen::goToMenu() {
	GameController::Instance().changeState(GameState::MENU);
}