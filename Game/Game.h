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
// new includes
#include "OpenGLManagement.h"
#include "TurriFramework.h"

//Game has four possible states: INIT (Preparing environment), PLAY (Playing), EXIT (Exit from the game) or MENU (Game menu)
enum class GameState { INIT, PLAY, EXIT, MENU, WIN, LOSE, FINISH };
enum class KeyPressed { NONE, UP, DOWN, RIGHT, LEFT };
enum class DrawMode {FILL, LINE};


//This class manages the game execution
class Game {
public:
	Game(std::string windowTitle, int screenWidth, int screenHeight, bool enableLimiterFPS, int maxFPS, bool printFPS);	//Constructor
	~Game();					//Destructor
	void start();//Game execution
	void load3DObjects();
	void loadGameObjects();

private:
	//Attributes	
	std::string _windowTitle;		//Window Titale
	int _screenWidth;				//Screen width in pixels				
	int _screenHeight;				//Screen height in pixels				
	GameState _gameState;			//It describes the game state				
	Window _window;					//Manage the OpenGL context
	FPSLimiter _fpsLimiter;			//Manage the synchronization between frame rate and refresh rate
	InputManager _inputManager;		//Manage the input devices		
	ButtonManager bManager;
	MaterialManager gMaterialManager;
	
	KeyPressed keyPressed;
	KeyPressed keyRotated;

	Camera* camera;
	DrawMode drawMode;
	int textureMode;

	GLuint barrelSpecular;
	GLuint lanternSpecular;
	GLuint barrelNormal;
	
	// Objects
	Car gCar;

	DirectionalLight gDirectionalLight;
	Light gSunLight;
	PointLight gNightLight;
	PointLight gRedLight;
	PointLight gRedLeftLight;
	PointLight gRightFlashLight;
	PointLight gLeftFlashLight;

	std::vector <Light> lights;
 
	
	///////////////////////////
	bool startGame = false;
	glm::ivec2 mousePosition;
	//Internal methods
	void initSystems();
	void processInput();
	void doPhysics();
	void update();
	void executePlayerCommands();
	void renderGame();

	void run();

	bool isRunning();

	// news 
	OpenGLManagement tOpenGL;
	//TurriFramework tFramework;
};