#pragma once

#include "Camera.h"
#include "Window.h"
#include "OpenGLManagement.h"
#include "InputManager.h"
#include "FPSLimiter.h"

enum class TurriState { MENU, GAME, EXIT };

class TurriFramework {
private:
	Camera tCamera;
	Window tWindow;
	OpenGLManagement tOpenGL;
	InputManager tInput;
	FPSLimiter tFPS;
	TurriState tGameState;
public:
	//static TurriFramework& getInstance();
	TurriFramework();

	TurriFramework(std::string name, int width, int height);
	~TurriFramework();
	void startLoop();
	void endLoop();

	void update();
	void render();

	unsigned int keyPressed();

	void setGameState(TurriState newState);
	TurriState getGameState();
};

