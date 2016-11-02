#include "TextureManager.h"

#include <SOIL/SOIL.h>

#include "ErrorManagement.h"



void TextureManager::deleteTextures() {
	for (unsigned int i = 0; i < _textureData.size(); i++) {
		glDeleteTextures(1, &_textureData[i].id);
	}
}

/*
* Load a texture from a file
* @param filePath is the filename of the texture
* @return GLuint is the texture ID
*/
GLuint TextureManager::loadTexture(std::string filePath) {
	GLTexture _texture;
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	//Like any of the previous objects in OpenGL, textures are referenced with an ID
	//The glGenTextures function first takes as input how many textures we want to generate and stores them in a GLuint array given as its second argument
	glGenTextures(1, &_texture.id);

	//We need to bind it so any subsequent texture commands will configure the currently bound texture
	glBindTexture(GL_TEXTURE_2D, _texture.id);

	// Set the texture wrapping parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// Set texture wrapping to GL_REPEAT (usually basic wrapping method)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// Set texture filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	/*
	Load the image
	1st parameter: The location of an image file.
	2nd parameter: Width of the image
	3rd parameter: Height of the image
	4th parameter: The number of channels the image has, but we're just going to leave this at 0.
	5th parameter: It tells SOIL how it should load the image. We're only interested in the RGB values of the image.
	The result is then stored in a large char / byte array.
	*/
	unsigned char* image = SOIL_load_image(filePath.c_str(), &_texture.width, &_texture.height, 0, SOIL_LOAD_RGBA);

	if (image == NULL) {
		ErrorManagement::errorRunTime("System was not able to load the following texture:" + filePath);
	}


	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, _texture.width, _texture.height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);

	//This will automatically generate all the required mipmaps for the currently bound texture.
	glGenerateMipmap(GL_TEXTURE_2D);

	//After we're done generating the texture and its corresponding mipmaps,
	//it is good practice to free the image memory and unbind the texture object:
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0);

	_textureData.push_back(_texture);
	_listOfTextures.push_back(filePath);

	return _texture.id;
}

/**
* Return the textureID of a texture. If the requested texture doesn't exist, it will load it
* @param filePath is the filename of the texture
* @return the texture ID
*/
GLuint TextureManager::getTextureID(std::string filePath) {
	for (unsigned int i = 0; i < _listOfTextures.size(); i++) {
		if (_listOfTextures[i] == filePath) {
			return _textureData[i].id;
		}
	}
	return loadTexture(filePath);
}