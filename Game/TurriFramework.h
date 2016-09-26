#pragma once

#include "Camera.h"
#include "Window.h"
#include "OpenGLManagement.h"
#include "InputManager.h"
#include "FPSLimiter.h"

#include "Scene.h"

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

	void setGameState(TurriState newState);
	TurriState getGameState();
};

