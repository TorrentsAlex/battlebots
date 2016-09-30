#pragma once

#include "Camera.h"
#include "Window.h"
#include "OpenGLManagement.h"
#include "InputManager.h"
#include "FPSLimiter.h"

#include "Scene.h"

class TurriFramework {
private:
	Window tWindow;
	Camera tCamera;
	OpenGLManagement tOpenGL;
	FPSLimiter tFPS;

	TurriFramework() {};

	bool running;

public:

	static TurriFramework& Instance() {
		static TurriFramework instance;
		return instance;
	}
	TurriFramework(TurriFramework const&) = delete;
	void operator=(TurriFramework const&) = delete;

	void init(string name, int screenWidth, int screenheight, bool enableLimiterFPS, int maxFPS, bool printFPS);
	
	bool isRunning();

	// FPS methods
	void startSync();
	void endSync();

	// Render methods
	void update();
	void startRender();
	void stopRender();

	void renderEntity(Entity robot);
	void renderScene(Scene scene);
	// Camera methods
	void renderCamera();

	// Input methods 
	void quit();

};

