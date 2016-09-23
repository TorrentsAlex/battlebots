#include "Game.h"

/**
* Constructor
* Note: It uses an initialization list to set the parameters
* @param windowTitle is the window title
* @param screenWidth is the window width
* @param screenHeight is the window height
*/
Game::Game(std::string windowTitle, int screenWidth, int screenHeight, bool enableLimiterFPS, int maxFPS, bool printFPS) :
	_windowTitle(windowTitle),
	_screenWidth(screenWidth),
	_screenHeight(screenHeight),
	_gameState(GameState::INIT),
	_fpsLimiter(enableLimiterFPS, maxFPS, printFPS),
	gCar(),
	textureMode(1),
	bManager(),
	gMaterialManager(),
	gDirectionalLight(),
	gSunLight(),
	gNightLight(),
	gRightFlashLight() {
		camera = new Camera();
		drawMode = DrawMode::FILL;
}

/**
* Destructor
*/
Game::~Game() {
	delete camera;
}

void Game::start() {
	while (_gameState != GameState::EXIT) {
		switch (_gameState) {
		case GameState::INIT:
			//Create an Opengl window using SDL
			_window.create(_windowTitle, _screenWidth, _screenHeight, 0);

			//System initializations
			initSystems();
			load3DObjects();

			loadGameObjects();
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

	_gameState = GameState::EXIT;
}

void Game::load3DObjects() {
	GameObject gameObject;
	gameObject._translate = glm::vec3(43.8919, 19.3604, 0);
	gameObject._rotation = glm::vec3(0, 0, 1);
	gameObject._angle = 0;
	gameObject._textureRepetition = false;
	gameObject._scale = glm::vec3(1, 1, 1);

	cout << "Loading objects..." << endl;
	gOBJTree = Geometry::LoadModelFromFile("./resources/tree_texturized.obj");
	cout << "Tree loaded" << endl;

	gOBJBarrel = Geometry::LoadModelFromFile("./resources/barrel.obj");

	gCar.setGameObject(gameObject);
	gCar.setOBJ(Geometry::LoadModelFromFile("./resources/objects/car.obj", true));

	cout << "Car loaded" << endl;
	// Load the trees, object and the scene
	gOBJRock = Geometry::LoadModelFromFile("./resources/lantern.obj");
	cout << "rock loaded" << endl;

	gOBJTerrain = Geometry::LoadModelFromFile("./resources/objects/terrain.obj");
	cout << "Terrain loaded" << endl;
	gOBJPerson = Geometry::LoadModelFromFile("./resources/zombie.obj");
	cout << "zombie loaded" << endl;

	GameObject terrainObject;
	terrainObject._translate = glm::vec3(0, 0, 0);
	terrainObject._rotation = glm::vec3(0, 0, 0);
	terrainObject._angle = 0;
	terrainObject._scale = glm::vec3(1, 1, 1);
	terrainObject._textureRepetition = true;
	terrainObject.xTil = 80;
	terrainObject.yTil = 80;
	gTerrain.setGameObject(terrainObject);
	gTerrain.setOBJ(gOBJTerrain);
	
	// Sky 
	GameObject skyObject;
	skyObject._translate = glm::vec3(0, 0, 0);
	skyObject._rotation = glm::vec3(0, 0, 0);
	skyObject._angle = 0;
	skyObject._scale = glm::vec3(4, 4, 4);
	skyObject._textureRepetition = false;
	gSkyBox.setGameObject(skyObject);
	gSkyBox.setOBJ(Geometry::LoadModelFromFile("./resources/skybox2.obj"));
	
	// OBject for text  
	gOBJRectangle = Geometry::LoadModelFromFile("./resources/rectangle.obj");
	cout << "Objects Loaded\n" << endl;
}

void Game::loadGameObjects() {
	TextureManager;

	bManager.initButtons();
	// Load TEXTURES
	GLuint carTexture = TextureManager::Instance().getTextureID("./resources/images/car.png");
	GLuint treeTexture = TextureManager::Instance().getTextureID("./resources/images/tree_texturea.png");
	GLuint rockTexture = TextureManager::Instance().getTextureID("./resources/images/lantern.png");
	GLuint terrainTexture = TextureManager::Instance().getTextureID("./resources/images/terrain_green.png");
	GLuint skyTexture = TextureManager::Instance().getTextureID("./resources/images/blue_light.png");
	GLuint zombieTexture = TextureManager::Instance().getTextureID("./resources/images/zombie.png");
	GLuint barrelTexture = TextureManager::Instance().getTextureID("./resources/images/barrel.png");

	// Specular maps
	barrelSpecular = TextureManager::Instance().getTextureID("./resources/images/barrelS.png");
	lanternSpecular = TextureManager::Instance().getTextureID("./resources/images/lanternS.png");
	// normal map
	barrelNormal = TextureManager::Instance().getTextureID("./resources/images/barrelNormal.png");

	// Set texttures id's
	gCar.setTextureId(carTexture);
	gTerrain.setTextureId(terrainTexture);
	gSkyBox.setTextureId(skyTexture);

	// Setting materials;
	gCar.setMaterial(gMaterialManager.getMaterialComponents(METAL));
	gTerrain.setMaterial(gMaterialManager.getMaterialComponents(TERRAIN));

	// Load Scenes
	vector<GameObject> rockObjects, personObjects, treeObjects, barrelObjects;
	rockObjects = Geometry::LoadGameElements("./resources/Scenes/lanterns_position.txt");
	treeObjects = Geometry::LoadGameElements("./resources/Scenes/treeScene.txt");
	barrelObjects = Geometry::LoadGameElements("./resources/Scenes/barrelScene.txt");
	personObjects = Geometry::LoadGameElements("./resources/Scenes/zombieScene.txt");

	// Trees
	for (GameObject tGObject : treeObjects) {
		tGObject._textureRepetition = false;
		tGObject._scale *= 20.0f;
		Immovable tree(gOBJTree, tGObject);
		tree.setTextureId(treeTexture);
		tree.setMaterial(gMaterialManager.getMaterialComponents(TERRAIN));
		gListOfTrees.push_back(tree);
	}	
	//barrel
	for (GameObject tGObject : barrelObjects) {
		tGObject._textureRepetition = false;
		tGObject._scale *= 2.0f;
		tGObject._translate.x *= 10.0f;
		tGObject._translate.y *= 10.0f;
		Immovable barrel(gOBJBarrel, tGObject);
		barrel.setTextureId(barrelTexture);
		barrel.setMaterial(gMaterialManager.getMaterialComponents(METAL));
		gListOfbarrels.push_back(barrel);
	}

	// Rocks
	for (GameObject tGObject : rockObjects) {
		tGObject._textureRepetition = false;
		tGObject._scale *= 20.0f;
		tGObject._translate.x *= 10.0f;
		tGObject._translate.y *= 10.0f;
		Immovable rock(gOBJRock, tGObject);
		rock.setTextureId(rockTexture);
		rock.setMaterial(gMaterialManager.getMaterialComponents(METAL));
		gListOfRocks.push_back(rock);
	}

	//gSunLight.setType(LIGHT_DIRECTIONAL);
	gSunLight.setAmbient(glm::vec3(1.0f, 1.0f, 1.0f));
	gSunLight.setDiffuse(glm::vec3(1.0f, 1.0f, 1.0f));
	gSunLight.setSpecular(glm::vec3(2.0f, 2.0f, 2.0f));

	gSunLight.setDirection(glm::vec3(0.8f, 0.8f, -0.8f));

	//	gSunLight.setLinear(0.014f);
	//gSunLight.setQuadratic(0.0007f);
	lights.push_back(gSunLight);

}
/*
* Initializes all the game engine components
*/
void Game::initSystems() {

	// All above is replaced with this
	tOpenGL.initializeShaders();
	// Init zBuffer;
	camera->initializeZBuffer(_window.getWindowResolution());

	// Set Perspective Camera
	camera->setPerspectiveCamera();
	camera->setViewMatrix();
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

void Game::update() {
	switch (_gameState) {
		case GameState::MENU:
			gCar.rotateCarInMenu();
			break;
		case GameState::FINISH:
			gCar.update();
		break;
		case GameState::PLAY:
			// Update the objects
			gCar.update();
			glm::vec3 newPost = camera->getPosition();
			newPost.x -= 60;
			newPost.y -= 60;
			gSkyBox.setPosition(newPost);
			break;
	}
}

/*
* Update the game objects based on the physics
*/
void Game::doPhysics() {
	switch (_gameState) {
	case GameState::MENU:
		break;
	case GameState::PLAY:;
		return;
		//Calculate the collisions only when the car is moving
		if (gCar.getVelocity() != 0) {
			for (Immovable tree : gListOfTrees) {
				glm::vec2 collision = CollisionDetector::GetCollision(gCar.getFrontBoundingBox(), tree.getBoundingBox());
				if (collision.x != 0 && collision.y != 0) {
					collision.x *= -1;
					collision.y *= -1;
					gCar.launchCar(collision);
				}
			}
			for (Immovable rock : gListOfRocks) {
				glm::vec2 collision = CollisionDetector::GetCollision(gCar.getFrontBoundingBox(), rock.getBoundingBox());
				if (collision.x != 0 && collision.y != 0) {
					collision.x *= -1;
					collision.y *= -1;
					gCar.launchCar(collision);
				}
			}
		}

		break;
	}
}


/**
* Draw the sprites on the screen
*/
void Game::renderGame() {

	tOpenGL.start();
	tOpenGL.sceneWithLights(true);
	tOpenGL.sendLight(lights);
	
	// Pass the viewer position
	tOpenGL.sendViewerPosition(camera->getPosition());
	//glUniform3fv(gViewerPositionUniform, 1, glm::value_ptr(camera->getPosition()));	
	tOpenGL.sendViewTransformationMatrix(camera->getViewMatrix(), camera->getProjectionCamera());

	// render terrain
	Material terrainMaterial = gMaterialManager.getMaterialComponents(TERRAIN);
	terrainMaterial.scale = glm::vec2(40.0f, 40.f);
	terrainMaterial.textureMap = gTerrain.getTextureId();
	tOpenGL.sendMaterial(terrainMaterial);
	tOpenGL.sendObject(gTerrain.getMesh(), gTerrain.getGameObject(), gTerrain.getNumVertices());
	tOpenGL.unbindMaps();

	// Car
	Material material = gMaterialManager.getMaterialComponents(METAL);
	material.textureMap = gCar.getTextureId();
	tOpenGL.sendMaterial(material);
	GameObject carObject = gCar.getGameObject();
	tOpenGL.sendObject(gCar.getMesh(), carObject, gCar.getNumVertices());
	tOpenGL.unbindMaps();

	// Rocks lantern
	material.textureMap = gListOfRocks.at(0).getTextureId();
	material.specularMap = lanternSpecular;
	tOpenGL.sendMaterial(material);
	for (Immovable sObject : gListOfRocks) {
		tOpenGL.sendObject(sObject.getMesh(), sObject.getGameObject(), sObject.getNumVertices());
	}
	tOpenGL.unbindMaps();
	// trees 
	material.textureMap = gListOfTrees.at(0).getTextureId();
	material.specularMap = -1;
	material.normalMap = -1;
	tOpenGL.sendMaterial(material);
	for (Immovable sObject : gListOfTrees) {
		tOpenGL.sendObject(sObject.getMesh(), sObject.getGameObject(), sObject.getNumVertices());
	}
	
	tOpenGL.unbindMaps();
	
	//Barrel
	material.textureMap = gListOfbarrels.at(0).getTextureId();
	material.specularMap = barrelSpecular;
	material.normalMap = -1;
	tOpenGL.sendMaterial(material);
	for (Immovable sObject : gListOfbarrels) {
		tOpenGL.sendObject(sObject.getMesh(), sObject.getGameObject(), sObject.getNumVertices());
	}

	tOpenGL.sceneWithLights(false);
	// SKybox
	material.textureMap = gSkyBox.getTextureId();
	material.specularMap = -1;
	tOpenGL.sendMaterial(material);
	tOpenGL.sendObject(gSkyBox.getMesh(), gSkyBox.getGameObject(), gSkyBox.getNumVertices());
	
	tOpenGL.unbindMaps();

	//Unbind the program
	tOpenGL.end();

	//Swap the display buffers (displays what was just drawn)
	_window.swapBuffer();

}