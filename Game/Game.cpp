#include "Game.h"

/**
* Constructor
* Note: It uses an initialization list to set the parameters
* @param windowTitle is the window title
* @param screenWidth is the window width
* @param screenHeight is the window height
*/
Game::Game() {

}

/**
* Destructor
*/
Game::~Game() {
}

void Game::start() {
	while (_gameState != GameState::EXIT) {
		switch (_gameState) {
		case GameState::INIT:
			//Create an Opengl window using SDL
			_window.create(_windowTitle, _screenWidth, _screenHeight, 0);

			//System initializations
			initSystems();
			_gameState = GameState::PLAY;
			cout << "p : play" << endl;
			cout << "e : editor" << endl;
			break;
		case GameState::MENU:
		case GameState::PLAY:
			run();
			break;
		}
	}
}

/*
* Game execution
*/
void Game::run() {

	//Start the game if all the elements are ready
	while (_gameState != GameState::EXIT) {
		//Start synchronization between refresh rate and frame rate
		_fpsLimiter.startSynchronization();
		//Process the input information (keyboard and mouse)
		processInput();
		//Execute the player actions (keyboard and mouse)
		executePlayerCommands();
		// update the scene
		update();
		//Update the game status
		doPhysics();
		//Draw the objects on the screen
		renderGame();
		//Force synchronization
		_fpsLimiter.forceSynchronization();
	}
	TextureManager::Instance().deleteTextures();
	//_gameState = GameState::EXIT;
}


/*
* Processes input with SDL
*/
void Game::processInput() {
	_inputManager.update();
	//Review https://wiki.libsdl.org/SDL_Event to see the different kind of events
	//Moreover, table show the property affected for each event type
	SDL_Event evnt;
	//Will keep looping until there are no more events to process
	while (SDL_PollEvent(&evnt)) {
		switch (evnt.type) {
		case SDL_QUIT:
			_gameState = GameState::EXIT;
			break;
		case SDL_MOUSEMOTION:
			_inputManager.setMouseCoords(evnt.motion.x, evnt.motion.y);
			break;
		case SDL_KEYDOWN:
			_inputManager.pressKey(evnt.key.keysym.sym);
			break;
		case SDL_KEYUP:
			_inputManager.releaseKey(evnt.key.keysym.sym);
			break;
		case SDL_MOUSEBUTTONDOWN:
			_inputManager.pressKey(evnt.button.button);
			break;
		case SDL_MOUSEBUTTONUP:
			_inputManager.releaseKey(evnt.button.button);
			break;
		default:
			break;
		}
	}

}

/**
* Executes the actions sent by the user by means of the keyboard and mouse
*/
void Game::executePlayerCommands() {

	switch (_gameState) {
	case GameState::MENU:
		if (_inputManager.isKeyPressed(SDLK_p)) {
			_gameState = GameState::PLAY;
			gCar.restartPosition();

			cout << "play" << endl;
		}
		break;
	case GameState::PLAY:
		//Move the player
		if (_inputManager.isKeyDown(SDLK_w)) {
			keyPressed = KeyPressed::UP;
			gCar.accelerate();
		} else if (_inputManager.isKeyDown(SDLK_s)) {
			gCar.brake();
			gRedLeftLight.setPower(3.0f);
			gRedLight.setPower(3.0f);
		} else {
			gCar.desaccelerate();
			gRedLeftLight.setPower(0.0f);
			gRedLight.setPower(0.0f);
		}
		
		if (_inputManager.isKeyDown(SDLK_a)) {
			gCar.left();
		}
		if (_inputManager.isKeyDown(SDLK_d)) {
			gCar.right();
		}
		//gCar.rotate(_inputManager.getAxis());
		// Change Cameras
		if (_inputManager.isKeyPressed(SDLK_o)) {
			camera->setOrthoCamera();
		}
		if (_inputManager.isKeyPressed(SDLK_p)) {
			camera->setPerspectiveCamera();
		}
		// where the fuck am i???
		if (_inputManager.isKeyPressed(SDLK_z)) {
			glm::vec3 position = gCar.getPosition();
			cout << "x:" << position.x << "  y: " << position.y << endl;
		}

		// Draw Mode
		if (_inputManager.isKeyPressed(SDLK_l)) {
			drawMode = drawMode == DrawMode::FILL ? DrawMode::LINE : DrawMode::FILL;
		}
		if (_inputManager.isKeyPressed(SDLK_k)) {
			textureMode = (textureMode + 1) % 3;
		}
		break;

	case GameState::FINISH:

		//Play again
		if (_inputManager.isKeyPressed(SDLK_p)) {
			gCar.restartPosition();
			gCar.restartLife();
			camera->setPerspectiveCamera();
			_gameState = GameState::PLAY;
		}
		break;
	}

}

void Game::renderGame() {

}