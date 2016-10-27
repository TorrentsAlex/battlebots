#pragma once

#include "Camera.h"
#include "Window.h"
#include "OpenGLManagement.h"
#include "InputManager.h"
#include "FPSLimiter.h"

#include "Scene.h"
#include "TurriIncludes.h"
#ifndef M_PI	
#define M_PI	3.14159265358979323846   // pi
#endif

#define RAD2DEG (180.0f / M_PI)
#define DEG2RAD (M_PI / 180.0f)

class TurriFramework {
private:
	Window tWindow;
	Camera tCamera;
	OpenGLManagement tOpenGL;
	FPSLimiter tFPS;

	TurriFramework() {};

	bool running;

	void clearMaps();

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

	void renderEntity(Entity entity);
	void renderScene(Scene scene);

	void renderLights(vector<Light> lights);
	void disableLights();
	
	void renderCamera();
	void setScreenSize(int widthScreen, int heightScreen);
	void addFlagscreen(unsigned int currentFlag);
	
	// Camera methods
	void setCameraPosition(glm::vec3 position);
	void setCameraLookAt(glm::vec3 lookAt);
	glm::vec3 getCameraPosition();

	// Input methods 
	void executeInput(Character& character);
	void quit();

};

