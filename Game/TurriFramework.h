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

	TurriFramework();

public:

	static TurriFramework& Instance() {
		static TurriFramework instance;
		return instance;
	}
	TurriFramework(TurriFramework const&) = delete;
	void operator=(TurriFramework const&) = delete;
	~TurriFramework();
	
	
	void startLoop();
	void endLoop();

	void update();
	void render();

	unsigned int keyPressed();

	void setGameState(TurriState newState);
	TurriState getGameState();
};

