#pragma once

#include <string>
#include <vector>

//Third-party libraries
#include <GL/glew.h>			//The OpenGL Extension Wrangler
#include <glm/glm.hpp>			//OpenGL Mathematics 


struct GLTexture {
	GLuint id;
	int width;
	int height;
};

//This class manages all the data related to the different textures used in the game
class TextureManager {
public:
	TextureManager();
	~TextureManager();
	GLuint getTextureID(std::string filePath);

private:
	GLuint loadTexture(std::string filePath);
	std::vector <GLTexture> _textureData;
	std::vector <std::string> _listOfTextures;
};

