#pragma once

#include "TurriFramework.h"

#include "BaseScreen.h"
#include "StateManager.h"

#include "SceneCreator.h"

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
#include "TextureManager.h"
#include "MaterialManager.h"
#include <glm/gtx/rotate_vector.hpp>

#include "Scene.h"
