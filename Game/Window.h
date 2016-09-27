#pragma once

#include <iostream>
#include <SDL/SDL.h>
#include <GL/glew.h>
using namespace std;
#include <glm/glm.hpp>
#include <string>
//This class manages the window input/output using the SDL library

//Create flags for the management of the window properties
enum class WindowFlags { INVISIBLE = 0x1, FULLSCREEN = 0x2, BORDERLESS = 0x3 };


class Window 	{
public:
	Window();
	~Window();

	int create(std::string windowName, int screenWidth, int screenHeight, unsigned int currentFlags);
	int getScreenWidth() { return _screenWidth; }
	int getScreenHeight() { return _screenHeight; }
	void swapBuffer();		
	
	glm::vec2 getWindowResolution();
private:
	SDL_DisplayMode currentMode;
	//TTF_Font* g_font;
	SDL_Color windowBackGroundColor;
	int _windowHeight, _windowWidth;
	int _windowHeightFullScreen, _windowWidthFullScreen;

	SDL_Window * _sdlWindow;
	int _screenHeight;
	int _screenWidth;

};
