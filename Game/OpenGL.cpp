#include "OpenGL.h"

/*
* Constructor
*/
OpenGL::OpenGL() :gVAO(0), gVBO(0), _programID(0), _numAttributes(0) {
}

/*
* Destructor
*/
OpenGL::~OpenGL() {
	//Always remember to delete your buffers when you are done!
	if (gVAO != 0) {
		glDeleteVertexArrays(1, &gVAO);
	}

	if (gVBO != 0) {
		glDeleteBuffers(1, &gVBO);
	}
}
void OpenGL::clearColor() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}
/*
* Prepare the buffers based on the information that has to be rendered
*/
void OpenGL::initializeBuffers() {
	//Create VAO and VBO
	allocateVAOVBO();
	//Initialize the VAO content
	initializeVertexArrayObject();
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}


/*
* Create VAO and VBO. This step must be done outside of the constructor because the OpenGL environment must be previously initialized
*/
void OpenGL::allocateVAOVBO() {
	//Generate the VAO if it isn't already generated
	//This is for preventing a memory leak if someone calls twice the initializeVertexArrayObject method
	if (gVAO == 0) {
		glGenVertexArrays(1, &gVAO);
	}

	//Generate the VBO if it isn't already generated
	//This is for preventing a memory leak if someone calls twice the init method
	if (gVBO == 0) {
		glGenBuffers(1, &gVBO);
	}
}

/*
* Create the Vertex Array Object
* @param _coloProgram is the object that manages the data related to the shaders
*/
void OpenGL::initializeVertexArrayObject() {
	// Bind the VAO. All subsequent opengl calls will modify it's state.
	glBindVertexArray(gVAO);

	//Bind the buffer object. YOU MUST BIND the buffer vertex object before binding attributes
	glBindBuffer(GL_ARRAY_BUFFER, gVBO);

	//Connect the xyz to the "vertexPosition" attribute of the vertex shader
	glEnableVertexAttribArray(getAttribLocation("vertexPosition"));
	//Connect the uv to the "vertexUV" attribute of the vertex shader
	glEnableVertexAttribArray(getAttribLocation("vertexUV"));
	glEnableVertexAttribArray(getAttribLocation("vertexNormal"));


	glVertexAttribPointer(getAttribLocation("vertexPosition"), 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position));

	glVertexAttribPointer(getAttribLocation("vertexUV"), 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, uv));

	glVertexAttribPointer(getAttribLocation("vertexNormal"), 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal));

	// unbind the VAO and VBO
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}



/*
* Send the information to the GPU
* @param data is an array that contains a set of vertices
* @param numVertices is the number of vertices to render
*/
void OpenGL::sendDataToGPU(Vertex * data, int numVertices) {
	//Bind the vertex array object
	glBindVertexArray(gVAO);

	//Bind the vertex buffer object
	glBindBuffer(GL_ARRAY_BUFFER, gVBO);

	// Put all the vertices into the VBO
	glBufferData(GL_ARRAY_BUFFER, numVertices * sizeof(Vertex), data, GL_DYNAMIC_DRAW);

	//Draw a set of elements(numVertices) from the VBO as GL_TRIANGLES. The first vertex is in the 0th position
	glDrawArrays(GL_TRIANGLES, 0, numVertices);

	//Unbind the VBO and VAO
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

}

void OpenGL::fillMode() {
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

void OpenGL::wireFrameMode() {
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
}
// SHADERS


/*
* Add a shader into the queu for being compiled
*/
void OpenGL::addShader(GLenum shaderType, const std::string& shaderPathFileName) {
	_listOfShaders[shaderType] = shaderPathFileName;
}

//Adds an attribute to our shader. Should be called between compiling and linking.
void OpenGL::addAttribute(const string & attributeName) {
	//Bind the variables used in the GLSL source code with our program data
	//Parameters: 
	//1st parameter: _programID is the program we are compiling and linking
	//2nd parameter: attributeID is the attribute of the GLSL source code.
	//3rd parameter: name of the attribute as a char *				
	glBindAttribLocation(_programID, _numAttributes, attributeName.c_str());
	_numAttributes++;
}

//enable the shader, and all its attributes
void OpenGL::use() {
	glUseProgram(_programID);
	for (int i = 0; i < _numAttributes; i++) {
		glEnableVertexAttribArray(i);
	}
}

//disable the shader
void OpenGL::unuse() {
	glUseProgram(0);
	for (int i = 0; i < _numAttributes; i++) {
		glDisableVertexAttribArray(i);
	}
}

//Compiles the shaders into a form that your GPU can understand
void OpenGL::compileShaders() {
	GLenum shaderType;
	string shaderPathFileName;
	GLint shaderID;

	//Get a program object.
	_programID = glCreateProgram();

	//Compile each shader that you intend to use
	for (auto it = _listOfShaders.begin(); it != _listOfShaders.end(); it++) {
		//Get the first shader
		shaderType = it->first;
		shaderPathFileName = it->second;

		//Create the shader object, and store its ID
		shaderID = glCreateShader(shaderType);
		if (shaderID == 0) {
			ErrorManagement::errorRunTime(shaderPathFileName + " failed to be created!");
		}
		//Compile each shader
		compileShader(shaderID, shaderPathFileName);
		_listOfShaderID.push_back(shaderID);
	}
}

//Compiles a single shader file
void OpenGL::compileShader(GLenum shaderType, const string & shaderFileName) {

	//Open, read, send to openGl and compile the GLSL source code for the vertex shader
	//Open the file
	ifstream shaderFile(shaderFileName);
	if (shaderFile.fail()) {
		//Get additional information related to the error
		perror(shaderFileName.c_str());
		ErrorManagement::errorRunTime("Failed to open " + shaderFileName);
	}

	//File contents stores all the text in the file
	string fileContents = "";
	//line is used to grab each line of the file
	string line;
	//Get all the lines in the file and add it to the contents
	while (getline(shaderFile, line)) {
		fileContents += line + "\n";
	}
	//Close the file
	shaderFile.close();

	//Send to code to OpenGL.
	//Parameters:
	//Object that will store the shader: id
	//Number of strings that contain the code:1 
	//Array of lines that contains the code. We only have one string with everything so we pass an array with one c_str
	//The length​ can be either NULL or an array of count​ integers. These are the lengths of the corresponding strings in the string​ array. This allows you to use non-NULL-terminated strings. If you pass NULL, then OpenGL will assume all of the strings are NULL-terminated and will therefore compute the length in the usual way.
	//get a pointer to our file contents c string;
	const char *contentsPtr = fileContents.c_str();
	//tell opengl that we want to use fileContents as the contents of the shader file
	glShaderSource(shaderType, 1, &contentsPtr, nullptr);
	//Compile the shader
	glCompileShader(shaderType);

	//Check for errors
	GLint isCompiled = 0;
	glGetShaderiv(shaderType, GL_COMPILE_STATUS, &isCompiled);

	if (isCompiled == GL_FALSE) {
		//Get the error message. First we get the length and next we read the content
		GLint maxLength = 0;
		glGetShaderiv(shaderType, GL_INFO_LOG_LENGTH, &maxLength);

		// The maxLength includes the NULL character
		std::vector<GLchar> errorLog(maxLength);
		glGetShaderInfoLog(shaderType, maxLength, &maxLength, &errorLog[0]);

		// Don't leak the shader.
		glDeleteShader(shaderType);

		// Exit with failure.		
		printf("%s\n", &(errorLog[0]));
		ErrorManagement::errorRunTime("Shader " + shaderFileName + " failed to compile");
	}
	// Shader compilation is successful.
}

void OpenGL::linkShaders() {
	//Shaders are successfully compiled.
	//Now time to link them together into a program.

	//Attach our shaders to our program
	for (unsigned int i = 0; i < _listOfShaderID.size(); i++) {
		glAttachShader(_programID, _listOfShaderID[i]);
	}

	//Link our program
	glLinkProgram(_programID);

	//Note the different functions here: glGetProgram* instead of glGetShader*.
	GLint isLinked = 0;
	glGetProgramiv(_programID, GL_LINK_STATUS, (int *)&isLinked);
	if (isLinked == GL_FALSE) {
		GLint maxLength = 0;
		glGetProgramiv(_programID, GL_INFO_LOG_LENGTH, &maxLength);

		//The maxLength includes the NULL character
		std::vector<char> errorLog(maxLength);
		glGetProgramInfoLog(_programID, maxLength, &maxLength, &errorLog[0]);

		//We don't need the program anymore.
		glDeleteProgram(_programID);
		//Don't leak shaders either.
		for (unsigned int i = 0; i < _listOfShaderID.size(); i++) {
			//Don't leak shaders either.
			glDeleteShader(_listOfShaderID[i]);
		}

		// Exit with failure.		
		printf("%s\n", &(errorLog[0]));
		ErrorManagement::errorRunTime("Shaders failed to link");
	}


	for (unsigned int i = 0; i < _listOfShaderID.size(); i++) {
		//Always detach shaders after a successful link.
		glDetachShader(_programID, _listOfShaderID[i]);
		//Don't leak shaders either.
		glDeleteShader(_listOfShaderID[i]);
	}
}

//Get the value of a uniform value from the GLSL program
GLint OpenGL::getUniformLocation(const string & uniformName) {
	GLint location = glGetUniformLocation(_programID, uniformName.c_str());
	if (location == GL_INVALID_INDEX) {
		ErrorManagement::errorRunTime("Uniform " + uniformName + " not found in shader!");
	}
	return location;
}

//Get the position of a variable from the GLSL program
GLint OpenGL::getAttribLocation(const string & attribName) {
	GLint attrib = glGetAttribLocation(_programID, attribName.c_str());
	if (attrib == GL_INVALID_INDEX)
		ErrorManagement::errorRunTime("Attribute " + attribName + " not found in shader!");

	return attrib;
}


// Send the uniforms to shaders
void OpenGL::sendUniform(GLint location, int value) {
	glUniform1i(location, value);
}

void OpenGL::sendUniform(GLint location, float value) {
	glUniform1f(location, value);
}

void OpenGL::sendUniform(GLint location, bool value) {
	if (value) {
		sendUniform(location, 1);
	} else {
		sendUniform(location, 0);
	}
}

void OpenGL::sendUniform(GLint location, glm::vec2 value) {
	glUniform2f(location, value.x, value.y);
}

void OpenGL::sendUniform(GLint location, glm::vec3 value) {
	glUniform3fv(location, 1, glm::value_ptr(value));
}

void OpenGL::sendUniform(GLint location, glm::mat3 value) {
	glUniformMatrix3fv(location, 1, GL_FALSE, glm::value_ptr(value));
}

void OpenGL::sendUniform(GLint location, glm::mat4 value) {
	glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(value));
}

void OpenGL::activateTexture(int TEXTURE_GL) {
	glActiveTexture(TEXTURE_GL);
}

void OpenGL::sendTexture(int TEXTURE_GL, GLint location ,GLuint texture, int unit) {
	glActiveTexture(TEXTURE_GL);
	glBindTexture(GL_TEXTURE_2D, texture);
	glUniform1i(location, unit);
}

void OpenGL::unbindTexture(int TEXTURE_GL) {
	glActiveTexture(TEXTURE_GL);
	glBindTexture(GL_TEXTURE_2D, 0);
}
