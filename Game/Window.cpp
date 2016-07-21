#include "Window.h"
#include <SDL/SDL.h>
#include <GL/glew.h>
#include "ErrorManagement.h"


/**
* Initialize the game engine
*/
Window::Window() 	{
	//Initialize all the SDL elements, even they are not used for this example
	SDL_Init(SDL_INIT_EVERYTHING);

	//All the SDL_GL_Set attributes must be done before creating the window
	//Tell SDL that we want a double buffered window so we don't get any flickering
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

	if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1")) {
		printf("Warning: Linear texture filtering not enabled!");
	}

	int shouldBeZero = SDL_GetCurrentDisplayMode(0, &currentMode);
	if (shouldBeZero != 0) {
		ErrorManagement::errorRunTime("Couldn't get display mode for video display");
	}
}

/**
* Destructor
*/
Window::~Window() {
	for (int i = 0; i < GAME_TEXTURES; i++) {
		SDL_DestroyTexture(textures[i]);
	}
	if (_sdlWindow != 0)
		SDL_DestroyWindow(_sdlWindow);

	//Clean up SDL
	SDL_Quit();
}

int Window::create(std::string windowName, int screenWidth, int screenHeight, unsigned int currentFlags) {
	_screenWidth = screenWidth;
	_screenHeight = screenHeight;

	//Check the flags that passes the user. If we want to add more parameters, we need to extend the enum in the Window.h
	Uint32 flags = SDL_WINDOW_OPENGL;
	if (currentFlags & (unsigned int)WindowFlags::INVISIBLE) {
		flags |= SDL_WINDOW_HIDDEN;
	}
	if (currentFlags & (unsigned int)WindowFlags::FULLSCREEN) {
		flags |= SDL_WINDOW_FULLSCREEN_DESKTOP;
	}
	if (currentFlags & (unsigned int)WindowFlags::BORDERLESS) {
		flags |= SDL_WINDOW_BORDERLESS;
	}

	//Create a SDL window centered into the middle of the screen
	_sdlWindow = SDL_CreateWindow(windowName.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, _screenWidth, _screenHeight, flags);
	//Check for errors
	if (_sdlWindow == nullptr) {
		ErrorManagement::errorRunTime("SDL Window could not be created!");
	}

	//Set up our OpenGL context. It will store the OpenGL things like vertex, buffers,...
	//The context is going to be stored in the window so the local variable won't be used longer
	SDL_GLContext glContext = SDL_GL_CreateContext(_sdlWindow);
	if (glContext == nullptr) {
		ErrorManagement::errorRunTime("SDL_GL context could not be created!");
	}

	//Set up glew (optional but recommended)
	//Initialize all the extensions setup. It will help to manage things that may be are not supported by our hardware
	//GLEW obtains information on the supported extensions from the graphics driver. Experimental or pre-release drivers, however, might not report every available extension through the standard mechanism, in which case GLEW will report it unsupported. To circumvent this situation, the glewExperimental global switch can be turned on by setting it to  GL_TRUE before calling glewInit(), which ensures that all extensions with valid entry points will be exposed.
	glewExperimental = GL_TRUE;
	GLenum error = glewInit();
	if (error != GLEW_OK) {
		ErrorManagement::errorRunTime("Could not initialize glew!!");
	}

	//Check the opengl version
	printf("****** OpenGL Version %s ********", glGetString(GL_VERSION));

	//Set the color that will be set every time the color buffer is initialized
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	//Set the base depth that will be set every time the depth buffer is initialized
	glClearDepth(1.0);

	//Set VSYNC. 0 means disable, 1 means enable
	//If it's enable, it automatically syncs the fps with the monitor, so, we don't need to use SDL_Delay
	SDL_GL_SetSwapInterval(0);
	
	return 0;
}

void Window::swapBuffer() {
	SDL_GL_SwapWindow(_sdlWindow);
}



glm::vec2 Window::getWindowResolution() {
	return glm::vec2(currentMode.w, currentMode.h);
}