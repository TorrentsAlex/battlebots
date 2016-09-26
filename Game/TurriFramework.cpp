#include "TurriFramework.h"


void TurriFramework::init(string name, int screenWidth, int screenheight, bool enableLimiterFPS, int maxFPS, bool printFPS) {
	tFPS.init(true, 60, false);
	// Up SDL window
	tWindow.create(name, screenWidth, screenheight, 0);

	// Up shaders
	tOpenGL.initializeShaders();

	// Up Camera
	tCamera.initializeZBuffer(tWindow.getWindowResolution());
	tCamera.setPerspectiveCamera();
	tCamera.setViewMatrix();
}

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

	// Terrain
	Entity terrain = scene.getTerrain();

	// send material
	tOpenGL.sendMaterial(terrain.getMaterial());
	tOpenGL.sendObject(terrain.getMesh(), terrain.getGameObject(), terrain.getNumVertices());

	// Decoration
	vector<Entity> vectorDecoration = scene.getDecoration();

	tOpenGL.sendMaterial(vectorDecoration.at(0).getMaterial());
	for (Entity nextDecoration : vectorDecoration) {
		tOpenGL.sendObject(nextDecoration.getMesh(), nextDecoration.getGameObject(), nextDecoration.getNumVertices());
	}

	// SkyBox
	Entity skyBox = scene.getSkyBox();
	tOpenGL.sendMaterial(skyBox.getMaterial());
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