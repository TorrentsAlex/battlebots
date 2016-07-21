#include "TurriFramework.h"



TurriFramework::TurriFramework() :
	tFPS(false, 60, true) {

}


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

TurriFramework::~TurriFramework() {
}
/*
TurriFramework& TurriFramework::getInstance() {
	static TurriFramework turri;
	return turri;
}*/

void TurriFramework::startLoop() {
	tFPS.startSynchronization();
}

void TurriFramework::endLoop() {
	tFPS.forceSynchronization();
}

void TurriFramework::update() {
	// Update Inputs
	tInput.update();
}

void TurriFramework::render() {
	tOpenGL.start();

	tOpenGL.end();
	tWindow.swapBuffer();
}

unsigned int TurriFramework::keyPressed() {
	return tInput.keyPressed();
}

void TurriFramework::setGameState(TurriState newState) {
	tGameState = newState;
}

TurriState TurriFramework::getGameState() {
	return tGameState;
}