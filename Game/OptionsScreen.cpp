#include "OptionsScreen.h"




void OptionsScreen::init() {
	optionsScene = new Scene();
	SceneCreator::Instance().createScene("./resources/scenes/Scene1.json", *optionsScene);

	 vector<Button> OptionButtons = SceneCreator::Instance().createButtons("./resources/scenes/option_buttons.json");
	
	 BManager.setButtons(OptionButtons);
	 BManager.init();

	 gamePad = new GamePad();
	 gamePad->gameController = SDL_GameControllerOpen(0);
}

void OptionsScreen::input() {
	// update the gamepad state
	InputManager::Instance().handleInput(*gamePad);

	if (InputManager::Instance().isKeyPressed(SDLK_UP) || 
		InputManager::Instance().isKeyPressed(gamePad->dPadUp)) {
		BManager.upButton();
	}
	if (InputManager::Instance().isKeyPressed(SDLK_DOWN) ||
		InputManager::Instance().isKeyPressed(gamePad->dPadDown)) {
		BManager.downButton();
	}
	if (InputManager::Instance().isKeyPressed(SDLK_RETURN) ||
		InputManager::Instance().isKeyPressed(gamePad->buttonA)) {
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
		if (currentButton.compare("fullscreen") == 0) {
			cout << "Fullscreen" << endl;
			TurriFramework::Instance().addFlagscreen((int)WindowFlags::FULLSCREEN);
		}
		if (currentButton.compare("back") == 0) {
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
		TurriFramework::Instance().renderEntity(&buttons.at(i));
	}
	TurriFramework::Instance().renderScene(optionsScene);

	// Render the skybox without lights
	TurriFramework::Instance().disableLights();
	TurriFramework::Instance().renderEntity(&optionsScene->getSkyBox());


	TurriFramework::Instance().stopRender();
}

void OptionsScreen::clean() {
	SDL_GameControllerClose(gamePad->gameController);
	gamePad->clean();
	delete gamePad;
}