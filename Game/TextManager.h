#pragma once

#include <GL/glew.h>			//The OpenGL Extension Wrangler
#include <SDL/SDL.h>
#include <SDL_ttf/SDL_ttf.h>
#include <string>
#include <vector>


class TextManager {
	TTF_Font* _font;
	std::vector <GLuint> _textureData;
	std::vector <std::string> _listOfTexts;
	GLuint createText(std::string message, SDL_Color color);

public:
	TextManager();
	~TextManager();
	GLuint TextManager::getTextureID(std::string message, SDL_Color color);
	
};

