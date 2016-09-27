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
	InputManager tInput;
	FPSLimiter tFPS;

	TurriFramework() {};

public:

	static TurriFramework& Instance() {
		static TurriFramework instance;
		return instance;
	}
	TurriFramework(TurriFramework const&) = delete;
	void operator=(TurriFramework const&) = delete;

	void init(string name, int screenWidth, int screenheight, bool enableLimiterFPS, int maxFPS, bool printFPS);
	
	void startSync();
	void endSync();

	void update();
	void startRender();
	void stopRender();

	void renderRobots(Entity robot);
	void renderViewerPosition(glm::vec3 cameraPosition);
	void renderViewTransformation(glm::mat4 viewMatrix, glm::mat4 projectionMatrix);
	void renderScene(std::vector<Light> lights, Scene scene);

	unsigned int keyPressed();

};

