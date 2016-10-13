#include "TurriFramework.h"


void TurriFramework::init(string name, int screenWidth, int screenheight, bool enableLimiterFPS, int maxFPS, bool printFPS) {
	tFPS.init(enableLimiterFPS, maxFPS, printFPS);
	// Up SDL window
	tWindow.create(name, screenWidth, screenheight, 0x2);

	// init input manager
	InputManager::Instance().init();

	// Up shaders
	tOpenGL.initializeShaders();

	// Up Camera
	tCamera.initializeZBuffer(tWindow.getWindowResolution());
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

// Input methods


// Finish the game loop
void TurriFramework::quit() {
	running = false;
}