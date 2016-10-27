#include "TurriFramework.h"


void TurriFramework::init(string name, int screenWidth, int screenheight, bool enableLimiterFPS, int maxFPS, bool printFPS) {
	tFPS.init(enableLimiterFPS, maxFPS, printFPS);
	// Up SDL window
	tWindow.create(name, screenWidth, screenheight, 0);

	// init input manager
	InputManager::Instance().init();

	// Up shaders
	tOpenGL.initializeShaders();

	// Up Camera
	tCamera.initializeZBuffer(glm::vec2(screenWidth, screenheight)); 

	tCamera.setPerspectiveCamera();
	tCamera.setViewMatrix();
	running = true;
}

bool TurriFramework::isRunning() {
	return running;
}

void TurriFramework::startSync() {
	tFPS.startSynchronization();
}

void TurriFramework::endSync() {
	tFPS.forceSynchronization();
}

void TurriFramework::update() {
	// Update Inputs
	//InputManager::Instance().update();
}

// Render methods
void TurriFramework::startRender() {
	tOpenGL.start();
}

void TurriFramework::stopRender() {
	
	tOpenGL.sceneWithLights(false);

	tOpenGL.end();
	tWindow.swapBuffer();
}

void TurriFramework::clearMaps() {
	tOpenGL.unbindMaps();
}

void TurriFramework::renderLights(vector<Light> lights) {
	tOpenGL.sceneWithLights(true);
	tOpenGL.sendLight(lights);
}

void TurriFramework::disableLights() {
	tOpenGL.sceneWithLights(false);
}

void TurriFramework::renderEntity(Entity entity) {
	
	tOpenGL.sendMaterial(entity.getMaterial());
	tOpenGL.sendObject(entity.getMesh(), entity.getGameObject(), entity.getNumVertices());
	clearMaps();
}

void TurriFramework::renderScene(Scene scene) {
	// Terrain
	Entity terrain = scene.getTerrain();
	tOpenGL.sendMaterial(terrain.getMaterial());
	tOpenGL.sendObject(terrain.getMesh(), terrain.getGameObject(), terrain.getNumVertices());

	clearMaps();

	// Decoration
	vector<Entity> vectorDecoration = scene.getDecoration();

	tOpenGL.sendMaterial(vectorDecoration.at(0).getMaterial());
	for (Entity nextDecoration : vectorDecoration) {
		tOpenGL.sendObject(nextDecoration.getMesh(), nextDecoration.getGameObject(), nextDecoration.getNumVertices());
	}

	clearMaps();
}

// send Camera values
void TurriFramework::renderCamera() {
	tOpenGL.sendViewerPosition(tCamera.getPosition());

	tOpenGL.sendViewTransformationMatrix(tCamera.getViewMatrix(), tCamera.getProjectionCamera());
}

void TurriFramework::setScreenSize(int widthScreen, int heightScreen) {
	glm::vec2 newResolution = glm::vec2(widthScreen, heightScreen);

	tWindow.setScreenSize(newResolution.x, newResolution.y);
	tCamera.initializeZBuffer(newResolution);

	tCamera.setPerspectiveCamera();
	tCamera.setViewMatrix();
}

void TurriFramework::addFlagscreen(unsigned int currentFlag) {
	
	if (currentFlag == (int)WindowFlags::FULLSCREEN) {
		tWindow.setFullScreen();
		tCamera.initializeZBuffer(tWindow.getNativeResolution());

		tCamera.setPerspectiveCamera();
		tCamera.setViewMatrix();
	}
	if (currentFlag == (int)WindowFlags::BORDERLESS) {
		tWindow.setWindowedScreen();
	}
}

// Camera 
void TurriFramework::setCameraPosition(glm::vec3 position) {
	tCamera.setCameraPosition(position);
}

void TurriFramework::setCameraLookAt(glm::vec3 lookAt) {
	tCamera.setCameraFront(lookAt);
}

glm::vec3 TurriFramework::getCameraPosition() {
	return tCamera.getPosition();
}

// Input methods
void TurriFramework::executeInput(Character& character) {
	// Joystick
	std::vector<JoystickCommand*> joystickComm = InputManager::Instance().getGamePadJoysticks(*character.getGamePad());
	for (JoystickCommand* jcom : joystickComm) {
		if (jcom) {
			jcom->execute(character);
		}
	}
	// Buttons
	std::vector<Command*> commands = InputManager::Instance().getGamePadCommand(*character.getGamePad());
	for (Command* com : commands) {
		if (com) {
			com->execute(character);
		}
	}

}

// Finish the game loop
void TurriFramework::quit() {
	running = false;
}