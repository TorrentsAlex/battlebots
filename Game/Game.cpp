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
	editor(),
	gCar(),
	tManager(),
	textureMode(1),
	gPSystem(),
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
			//gCar.restartPosition();
			menu();
			break;
		case GameState::PLAY:
			run();
			break;
		case GameState::WIN:
			win();
			break;
		case GameState::LOSE:
			lose();
			break;
		case GameState::EDITOR:
			runEditor();
			break;
		}
	}
}

void Game::menu() {
	processInput();
	
	executePlayerCommands();
	update();
	renderMenu();
}

void Game::win() {
}
void Game::lose() {}

void Game::runEditor() {
	processInput();
	executePlayerCommands();
}

/*
* Game execution
*/
void Game::run() {

	//Start the game if all the elements are ready
	gameLoop();

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
	gOBJTree = Geometry::LoadModelFromFile("./resources/tree_texturized.obj", glm::vec3(0, 200, 0));
	cout << "Tree loaded" << endl;

	gOBJBarrel = Geometry::LoadModelFromFile("./resources/barrel.obj", glm::vec3(0, 200, 0));

	gCar.setGameObject(gameObject);
	gCar.setOBJ(Geometry::LoadModelFromFile("./resources/bmw.obj", glm::vec3(125, 125, 125)));

	cout << "Car loaded" << endl;
	// Load the trees, object and the scene
	gOBJRock = Geometry::LoadModelFromFile("./resources/lantern.obj", glm::vec3(0, 100, 200));
	cout << "rock loaded" << endl;

	gOBJTerrain = Geometry::LoadModelFromFile("./resources/terrain3.obj", glm::vec3(7, 100, 35));
	cout << "Terrain loaded" << endl;
	gOBJPerson = Geometry::LoadModelFromFile("./resources/zombie.obj", glm::vec3(200, 0, 37));
	cout << "zombie loaded" << endl;

	GameObject terrainObject;
	terrainObject._translate = glm::vec3(-20, -20, 0);
	terrainObject._rotation = glm::vec3(0, 0, 1);
	terrainObject._angle = 5;
	terrainObject._scale = glm::vec3(3, 3, 3);
	terrainObject._textureRepetition = true;
	terrainObject.xTil = 80;
	terrainObject.yTil = 80;
	gTerrain.setGameObject(terrainObject);
	gTerrain.setOBJ(gOBJTerrain);

	// Loading the finish object
	gOBJFinish = Geometry::LoadModelFromFile("./resources/finish.obj", glm::vec3(255, 250, 5));
	cout << "Finish loaded" << endl;
	GameObject finishObject;
	finishObject._translate = glm::vec3(25, 65, 0);
	finishObject._rotation = glm::vec3(0, 0, 0);
	finishObject._angle = 0;
	finishObject._scale = glm::vec3(1, 1, 1);
	finishObject._textureRepetition = false;
	gFinish.setGameObject(finishObject);
	gFinish.setOBJ(gOBJFinish);
	// set the square bounding box
	gFinish.setSquareBoundingBox();
	
	// Sky 
	GameObject skyObject;
	skyObject._translate = glm::vec3(0, 0, 0);
	skyObject._rotation = glm::vec3(0, 0, 1);
	skyObject._angle = 5;
	skyObject._scale = glm::vec3(1, 1, 1);
	skyObject._textureRepetition = false;
	gSkyBox.setGameObject(skyObject);
	gSkyBox.setOBJ(Geometry::LoadModelFromFile("./resources/skybox2.obj", glm::vec3(255, 250, 5)));

	// Rain
	gOBJDrop = Geometry::LoadModelFromFile("./resources/droptriangle.obj", glm::vec3(255, 250, 5));
	gPSystem.setOBJ(gOBJDrop);
	gPSystem.initParticleSystem(gCar.getPosition());
	
	// OBject for text  
	gOBJRectangle = Geometry::LoadModelFromFile("./resources/rectangle.obj", glm::vec3(255,255,255));
	cout << "Objects Loaded\n" << endl;
}

void Game::loadGameObjects() {

	bManager.initButtons();
	// Load TEXTURES
	GLuint carTexture = tManager.getTextureID("./resources/images/car.png");
	GLuint treeTexture = tManager.getTextureID("./resources/images/tree_texturea.png");
	GLuint rockTexture = tManager.getTextureID("./resources/images/lantern.png");
	GLuint finishTexture = tManager.getTextureID("./resources/images/finish.png");
	GLuint terrainTexture = tManager.getTextureID("./resources/images/terrain_green.png");
	GLuint skyTexture = tManager.getTextureID("./resources/images/blue_light.png");
	GLuint zombieTexture = tManager.getTextureID("./resources/images/zombie.png");
	GLuint dropTexture = tManager.getTextureID("./resources/images/water_drops.png");
	GLuint barrelTexture = tManager.getTextureID("./resources/images/barrel.png");

	// Specular maps
	barrelSpecular = tManager.getTextureID("./resources/images/barrelS.png");
	lanternSpecular = tManager.getTextureID("./resources/images/lanternS.png");
	// normal map
	barrelNormal = tManager.getTextureID("./resources/images/barrelNormal.png");

	// Sett texttures id's
	gCar.setTextureId(carTexture);
	gFinish.setTextureId(finishTexture);
	gTerrain.setTextureId(terrainTexture);
	gSkyBox.setTextureId(skyTexture);
	gPSystem.setTextureId(dropTexture);

	// Setting materials;
	gCar.setMaterial(gMaterialManager.getMaterialComponents(METAL));
	gFinish.setMaterial(gMaterialManager.getMaterialComponents(METAL));
	gTerrain.setMaterial(gMaterialManager.getMaterialComponents(TERRAIN));

	// Load Scenes
	vector<GameObject> rockObjects, personObjects, treeObjects, barrelObjects;
	rockObjects = Geometry::LoadGameElements("./resources/Scenes/rockScene.txt");
	treeObjects = Geometry::LoadGameElements("./resources/Scenes/treeScene.txt");
	barrelObjects = Geometry::LoadGameElements("./resources/Scenes/barrelScene.txt");
	personObjects = Geometry::LoadGameElements("./resources/Scenes/zombieScene.txt");

	// Trees
	for (GameObject tGObject : treeObjects) {
		tGObject._textureRepetition = false;
		//tGObject._scale *= 2.0f;
		Immovable tree(gOBJTree, tGObject);
		tree.setTextureId(treeTexture);
		tree.setMaterial(gMaterialManager.getMaterialComponents(TERRAIN));
		gListOfTrees.push_back(tree);
	}	
	//barrel
	for (GameObject tGObject : barrelObjects) {
		tGObject._textureRepetition = false;
		tGObject._scale *= 2.0f;
		Immovable barrel(gOBJBarrel, tGObject);
		barrel.setTextureId(barrelTexture);
		barrel.setMaterial(gMaterialManager.getMaterialComponents(METAL));
		gListOfbarrels.push_back(barrel);
	}

	// Rocks
	for (GameObject tGObject : rockObjects) {
		tGObject._textureRepetition = false;
		tGObject._scale *= 2.0f;
		Immovable rock(gOBJRock, tGObject);
		rock.setTextureId(rockTexture);
		rock.setMaterial(gMaterialManager.getMaterialComponents(METAL));
		gListOfRocks.push_back(rock);
	}
	// Persons
	for (GameObject pGObject : personObjects) {
		pGObject._textureRepetition = false;
		Movable person(gOBJPerson, pGObject);
		person.setTextureId(zombieTexture);
		person.setMaterial(gMaterialManager.getMaterialComponents(TERRAIN));
		gListOfPerson.push_back(person);
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
* Initialize the shaders:
* Compiles, sets the variables between C++ and the Shader program and links the shader program
*/
void Game::initShaders() {
	
}

/*
* Game execution: Gets input events, processes game logic and draws sprites on the screen
*/
void Game::gameLoop() {
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
	if (_inputManager.isKeyPressed(SDL_BUTTON_LEFT)) {
		glm::vec2 mouseCoords = _inputManager.getMouseCoords();
		mousePosition = glm::vec2(mouseCoords.x, mouseCoords.y);
		clicked = true;

	}
	switch (_gameState) {
	case GameState::MENU:
		if (_inputManager.isKeyPressed(SDLK_e)) {
			_gameState = GameState::EDITOR;
			camera->setEditorCamera();
			camera->setViewMatrix();	
			loadGameObjects();

			cout << "run editor" << endl;
		}
		if (_inputManager.isKeyPressed(SDLK_p)) {
			_gameState = GameState::PLAY;
			gCar.restartPosition();
			// Start the miracle of rain
			gPSystem.startRain();

			cout << "play" << endl;
		}
		break;
	case GameState::EDITOR:
		editor.playerCommands(_inputManager);
		if (_inputManager.isKeyDown(SDL_BUTTON_LEFT)) {
			glm::vec2 mouseCoords = _inputManager.getMouseCoords();
			mouseCoords.x /= 7.0f;
			mouseCoords.y /= 7.0f;
			editor.newCoord(glm::vec2(mouseCoords.x, mouseCoords.y));
		}
		if (_inputManager.isKeyPressed(SDLK_RETURN)) {

			editor.saveCurrentObjects();
		}

		if (_inputManager.isKeyPressed(SDLK_p)) {
			_gameState = GameState::PLAY;
			loadGameObjects();
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

		// Wind 
		if (_inputManager.isKeyPressed(SDLK_q)) {
			sunsetActivated = sunsetActivated ? false : true;
			if (_inputManager.isKeyDown(SDL_BUTTON_LEFT)) {
				gPSystem.moreXWind();
			} else if (_inputManager.isKeyDown(SDL_BUTTON_RIGHT)) {
				gPSystem.lessXWind();
			}
		}
		if (_inputManager.isKeyDown(SDLK_e)) {
			if (_inputManager.isKeyDown(SDL_BUTTON_LEFT)) {
				gPSystem.moreYWind();
			} else if (_inputManager.isKeyDown(SDL_BUTTON_RIGHT)) {
				gPSystem.lessYWind();
			}
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

			// Lose
			if (gCar.getLife() <= 0) {
				c_end = std::clock();
				float totalTime = 1000.0 * (c_end * c_start) / CLOCKS_PER_SEC;
				cout << "Total time: " << totalTime << "ms" << endl;
				cout << "Life: " << gCar.getLife();
				cout << "Lose" << endl;
				_gameState = GameState::FINISH;
				gCar.restartPosition();
			}
			// Update the camera 
			glm::vec3 forwardCar = gCar.getForwardVector();
			forwardCar *= -1; // get the back vector
			glm::vec3 pos = gCar.getGameObject()._translate;
			camera->setCameraFront(pos); // where the camera points

			pos.x += forwardCar.x * camera->getArmLenght();
			pos.y += forwardCar.y * camera->getArmLenght();
			if (!rotateCamera) {
				camera->setCameraPosition(pos);
			}
			
			// set the center of storm and update
			gPSystem.updateCenterOfRain(gCar.getPosition());
			gPSystem.update();
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
		
		for (int i = 0; i < gListOfPerson.size(); i++) {
			// Detect collision with others enemies
			for (int j = 0; j < gListOfPerson.size(); j++) {
				//If no the same enemy
				if (j != i) {
					glm::vec2 coll = CollisionDetector::GetCollision(gListOfPerson.at(i).getBoundingBox(), gListOfPerson.at(j).getBoundingBox());
					if (coll.x != 0 && coll.y != 0) {
						coll.x = gListOfPerson.at(i).getXPosition() + coll.x - 0.1;
						coll.y = gListOfPerson.at(i).getYPosition() + coll.y - 0.1;

						gListOfPerson.at(i).setPosition(coll);
					}
				}
			}

				// Check with the bigger sphere
				glm::vec2 collision = CollisionDetector::GetCollision(gCar.getBoundingBox(), gListOfPerson.at(i).getBoundingBox());
				if (collision.x != 0 && collision.y != 0) {
					for (int i = 0; i < gListOfPerson.size(); i++) {
						// check with the all 3 sphere collisions of the car
						glm::vec2 frontCollision = CollisionDetector::GetCollision(gCar.getFrontBoundingBox(), gListOfPerson.at(i).getBoundingBox());
						glm::vec2 middleCollision = CollisionDetector::GetCollision(gCar.getMiddleBoundingBox(), gListOfPerson.at(i).getBoundingBox());
						glm::vec2 backCollision = CollisionDetector::GetCollision(gCar.getBackBoundingBox(), gListOfPerson.at(i).getBoundingBox());
						if (frontCollision.x != 0 && frontCollision.y != 0) {
							// launch zombie 
							frontCollision.x *= -1;
							frontCollision.y *= -1;
							//gCar.launchCar();
						}
						// check with de middle and back collision 
						if ((backCollision.x != 0 && backCollision.y != 0) ||
							(middleCollision.x != 0 && middleCollision.y != 0)) {
							// launch char with the higher vector 
							collision.x = backCollision.x != 0 ? backCollision.x : middleCollision.x;
							collision.y = backCollision.y != 0 ? backCollision.y : middleCollision.y;
							collision.y *= -1;
							collision.x *= -1;
							gCar.substractLife(5);
							gCar.launchCar(collision);
						}
					}
				}
			}
		
		
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

			// collision with the finish box only when car is near
			if (gCar.getYPosition() > 40) {
				glm::vec2 collision = CollisionDetector::GetCollision(gCar.getFrontBoundingBox(), gFinish.getSquareBoundingBox());
				if (collision.x != 0 && collision.y != 0) {
					c_end = std::clock();
					float totalTime = 1000.0 * (c_end * c_start) / CLOCKS_PER_SEC;
					cout << "Total time: " << totalTime << "ms" << endl;
					cout << "Life: " << gCar.getLife();
					cout << "win" << endl;
					_gameState = GameState::FINISH;
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

void Game::renderMenu() {

}
