#include "OptionsScreen.h"




void OptionsScreen::init() {
	
	SceneCreator::Instance().createScene("./resources/scenes/Scene2.json", *optionsScene);

	 vector<Button> OptionButtons = SceneCreator::Instance().createButtons("./resources/scenes/option_buttons.json");
	
	 BManager.setButtons(OptionButtons);
	 BManager.init();
}

void OptionsScreen::input() {

	if (InputManager::Instance().isKeyPressed(SDLK_UP)) {
		BManager.upButton();
	}
	if (InputManager::Instance().isKeyPressed(SDLK_DOWN)) {
		BManager.downButton();
	}
	if (InputManager::Instance().isKeyPressed(SDLK_RETURN)) {
		string currentButton = BManager.getCurrentButton();

		if (currentButton.compare("1920x1080") == 0) {
			cout << "1920x1080" << endl;
			TurriFramework::Instance().setScreenSize(1920, 1080);
		}
		if (currentButton.compare("1600x900") == 0) {
			cout << "1600x900" << endl;
			TurriFramework::Instance().setScreenSize(1600, 900);
		}
		if (currentButton.compare("1280x800") == 0) {
			cout << "1280x800" << endl;
			TurriFramework::Instance().setScreenSize(1280, 800);
		}
		if (currentButton.compare("FullScreen") == 0) {
			cout << "Fullscreen" << endl;
			TurriFramework::Instance().addFlagscreen((int)WindowFlags::FULLSCREEN);
		}
		if (currentButton.compare("Return") == 0) {
			cout << "Return to Menu" << endl;
			GameController::Instance().changeState(GameState::MENU);
		}
	}

}

void OptionsScreen::update() {

}

void OptionsScreen::render() {

	TurriFramework::Instance().startRender();
	// Render camera and projections views
	TurriFramework::Instance().renderCamera();

	// send the lights to shaders
	TurriFramework::Instance().renderLights(optionsScene->getLights());

	vector<Button> buttons = BManager.getButtons();
	for (int i = 0; i < buttons.size(); i++) {
		TurriFramework::Instance().renderEntity(buttons.at(i));
	}
	TurriFramework::Instance().renderScene(*optionsScene);

	// Render the skybox without lights
	TurriFramework::Instance().disableLights();
	TurriFramework::Instance().renderEntity(optionsScene->getSkyBox());


	TurriFramework::Instance().stopRender();
}

void OptionsScreen::clean() {

}