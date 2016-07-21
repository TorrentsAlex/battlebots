#include "TextManager.h"
#include "ErrorManagement.h"
#include <iostream>


TextManager::TextManager()
{
	//Initialize TTF fonts from SDL_ttf. Return 0 if it is successful
	if (TTF_Init() == 0) {
		_font = TTF_OpenFont("./resources/font/Roboto-Black.ttf", 30);
		if (_font == 0) {
			ErrorManagement::errorRunTime("[TextManager] The font file cannot be loaded");
		}
	}
	else {
		ErrorManagement::errorRunTime("[TextManager] SDL TTF cannot be initialized");
	}
}


TextManager::~TextManager()
{
	for (unsigned int i = 0; i < _textureData.size(); i++) {
		glDeleteTextures(1, &_textureData[i]);
	}
	TTF_CloseFont(_font);
}

/**
* Return the textureID of a texture. If the requested texture doesn't exist, it will create it
* @param message is the text to render
* @return the texture ID
*/
GLuint TextManager::getTextureID(std::string message, SDL_Color color) {
	for (unsigned int i = 0; i < _listOfTexts.size(); i++) {
		if (_listOfTexts[i] == message) {
			return _textureData[i];
		}
	}
	return createText(message, color);
}


/*
* Creates a texture based on the text
*/
GLuint TextManager::createText(std::string message, SDL_Color color) {
	glEnable(GL_BLEND); 
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	//We need to first render to a surface as that's what TTF_RenderText
	//returns, then load that surface into a texture

	SDL_Surface *surface = TTF_RenderText_Blended(_font, message.c_str(), color);
	if (surface == nullptr) {
		ErrorManagement::errorRunTime("[TextManager] The font file cannot be loaded");
	}

	GLuint textureID;

	//Like any of the previous objects in OpenGL, textures are referenced with an ID
	//The glGenTextures function first takes as input how many textures we want to generate and stores them in a GLuint array given as its second argument
	glGenTextures(1, &textureID);

	//We need to bind it so any subsequent texture commands will configure the currently bound texture
	glBindTexture(GL_TEXTURE_2D, textureID);

	// Set the texture wrapping parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// Set texture wrapping to GL_REPEAT (usually basic wrapping method)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// Set texture filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);


	/*
	Now that the texture is bound, we can start generating a texture using the previously loaded image data.
	The first argument specifies the texture target; setting this to GL_TEXTURE_2D means this operation will generate a texture on the currently bound texture object at the same target(so any textures bound to targets GL_TEXTURE_1D or G_TEXTURE_3D will not be affected).
	The second argument specifies the mipmap level for which we want to create a texture for if you want to set each mipmap level manually, but we'll leave it at the base level which is 0.
	The third argument tells OpenGL in what kind of format we want to store the texture.Our image has only RGB values so we'll store the texture with RGB values as well.
	The 4th and 5th argument sets the width and height of the resulting texture.We stored those earlier when loading the image so we'll use the corresponding variables.
	The next argument should always be 0 (some legacy stuff).
	The 7th and 8th argument specify the format and datatype of the source image.We loaded the image with RGB values and stored them as chars(bytes) so we'll pass in the corresponding values.
	The last argument is the actual image data.
	*/
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, surface->w, surface->h, 0, GL_BGRA, GL_UNSIGNED_BYTE, surface->pixels);
	glHint(GL_GENERATE_MIPMAP_HINT, GL_FASTEST);
	//This will automatically generate all the required mipmaps for the currently bound texture.
	glGenerateMipmap(GL_TEXTURE_2D);

	//After we're done generating the texture and its corresponding mipmaps,
	//it is good practice to free the image memory and unbind the texture object:
	glBindTexture(GL_TEXTURE_2D, 0);

	_textureData.push_back(textureID);
	_listOfTexts.push_back(message);

	//Clean up the surface 
	SDL_FreeSurface(surface);

	return textureID;
}