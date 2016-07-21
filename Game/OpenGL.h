#pragma once
//Third-party libraries
#include <GL/glew.h>			//The OpenGL Extension Wrangler
#include <glm/glm.hpp>	
#include <glm/gtc/type_ptr.hpp> //OpenGL Mathematics 
#include <iostream>
#include <cstddef>
#include <string>
#include <fstream>

#include "unordered_map"
#include "ErrorManagement.h"
#include "Vertex.h"

using namespace std;

class OpenGL {
private:
	GLuint gVAO;			//Vertex Array Object
	GLuint gVBO;			//Vertex Buffer Object

							// Shaders part
	std::unordered_map<GLenum, string> _listOfShaders;
	std::vector<GLuint> _listOfShaderID;
	GLuint _programID;
	int _numAttributes;
	void compileShader(GLenum shaderType, const string& shaderFileName);

public:
	OpenGL();
	~OpenGL();
	void initializeBuffers();
	void allocateVAOVBO();
	void initializeVertexArrayObject();
	void sendDataToGPU(Vertex * data, int numVertex);

	// Shaders part
	void addShader(GLenum shaderType, const string& shaderPathFileName);
	void compileShaders();
	void addAttribute(const string & attributeName);
	void linkShaders();
	void clearColor();
	void use();
	void unuse();
	GLint getUniformLocation(const string & uniformName);
	GLint getAttribLocation(const string & attribName);

	// Pass the uniforms to shaders
	void sendUniform(GLint location, int value);
	void sendUniform(GLint location, float value);
	void sendUniform(GLint location, bool value);

	void sendUniform(GLint location, glm::mat3 value);
	void sendUniform(GLint location, glm::mat4 value);

	void sendUniform(GLint location, glm::vec2 value);
	void sendUniform(GLint location, glm::vec3 value);

	// Pass Textures
	void activateTexture(int TEXTURE_GL);
	void sendTexture(int TEXTURE_GL, GLint location, GLuint texture, int unit);
	void unbindTexture(int TEXTURE_GL);
};

