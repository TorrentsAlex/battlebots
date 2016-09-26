#pragma once


//Third-party libraries
#include <GL/glew.h>			//The OpenGL Extension Wrangler
#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>			//OpenGL Mathematics 
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/vector_angle.hpp>
#include <iostream>
#include <thread>
#include <ctime>

#include "Window.h"
#include "FPSLimiter.h"
#include "Vertex.h"
#include "Geometry.h"
#include "InputManager.h"
#include "Camera.h"
#include "CollisionDetector.h"
#include "Car.h"
#include "TextureManager.h"
#include "ButtonManager.h"
#include "MaterialManager.h"
#include <glm/gtx/rotate_vector.hpp>

#include "DirectionalLight.h"
#include "PointLight.h"
#include "SpotLight.h"
using namespace std;

#include "BaseMode.h"
#include "OpenGLManagement.h"
#include "TurriFramework.h"
#include "Scene.h"
#include "Robot.h"

//Game has four possible states: INIT (Preparing environment), PLAY (Playing), EXIT (Exit from the game) or MENU (Game menu)
enum class KeyPressed { NONE, UP, DOWN, RIGHT, LEFT };
enum class DrawMode {FILL, LINE};

//This class manages the game execution
class Game {
public:
	Game();	
	~Game();	

private:
	Scene gScene;
	Robot robot1;

};