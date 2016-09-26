#include "TurriFramework.h"



TurriFramework::TurriFramework() :
	tWindow(),
	tOpenGL(),
	tCamera(),
	tFPS(false, 60, true) {
	tWindow.create("Turri Engine", 800, 800, 0);

	tOpenGL.initializeShaders();

	tCamera.initializeZBuffer(tWindow.getWindowResolution());
	tCamera.setPerspectiveCamera();
	tCamera.setViewMatrix();
	tCamera.setCameraPosition(glm::vec3(0.0));

	tGameState = TurriState::GAME;
}

/*
TurriFramework::TurriFramework(std::string name, int width, int height) :
	tWindow(),
	tOpenGL(),
	tCamera(),
	tFPS(false, 60, true) {

	tWindow.create("Turri Engine", 800, 800, 0);

	tOpenGL.initializeShaders();

	tCamera.initializeZBuffer(tWindow.getWindowResolution());
	tCamera.setPerspectiveCamera();
	tCamera.setViewMatrix();
	tCamera.setCameraPosition(glm::vec3(0.0));
	
	tGameState = TurriState::GAME;
}
*/
TurriFramework::~TurriFramework() {
}
/*
TurriFramework& TurriFramework::getInstance() {
	static TurriFramework turri;
	return turri;
}*/

void TurriFramework::startSync() {
	tFPS.startSynchronization();
}

void TurriFramework::endSync() {
	tFPS.forceSynchronization();
}

void TurriFramework::update() {
	// Update Inputs
	tInput.update();
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

void TurriFramework::renderRobots(Entity robot) {
	
	tOpenGL.sendMaterial(robot.getMaterial());
	tOpenGL.sendObject(robot.getMesh(), robot.getGameObject(), robot.getNumVertices());
}

void TurriFramework::renderScene(std::vector<Light> lights, Scene scene) {
	tOpenGL.sceneWithLights(true);
	tOpenGL.sendLight(lights);

	// send material

	// Terrain
	Entity terrain = scene.getTerrain();
	tOpenGL.sendObject(terrain.getMesh(), terrain.getGameObject(), terrain.getNumVertices());

	// Decoration
	vector<Entity> vectorDecoration = scene.getDecoration();

	for (Entity nextDecoration : vectorDecoration) {
		tOpenGL.sendObject(nextDecoration.getMesh(), nextDecoration.getGameObject(), nextDecoration.getNumVertices());
	}

	// SkyBox
	Entity skyBox = scene.getSkyBox();
	tOpenGL.sendObject(skyBox.getMesh(), skyBox.getGameObject(), skyBox.getNumVertices());

}

// send Camera values
void TurriFramework::renderViewerPosition(glm::vec3 cameraPosition) {
	tOpenGL.sendViewerPosition(cameraPosition);
}

void TurriFramework::renderViewTransformation(glm::mat4 viewMatrix, glm::mat4 projectionMatrix) {
	tOpenGL.sendViewTransformationMatrix(viewMatrix, projectionMatrix);
}

// .....
unsigned int TurriFramework::keyPressed() {
	return tInput.keyPressed();
}

void TurriFramework::setGameState(TurriState newState) {
	tGameState = newState;
}

TurriState TurriFramework::getGameState() {
	return tGameState;
}