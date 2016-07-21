#include "OpenGLManagement.h"


OpenGLManagement::OpenGLManagement() :
	oGLBuffer() {

	// Set up the OpenGL buffers
}


OpenGLManagement::~OpenGLManagement() {
}

void OpenGLManagement::start() {
	oGLBuffer.clearColor();
	oGLBuffer.use();
}

void OpenGLManagement::end() {
	oGLBuffer.unuse();
}
// Send the ViewMatrix and projection Matrix
void OpenGLManagement::sendUnitaryViewMatrix() {
	glm::mat4 unitaryMatrix;
	oGLBuffer.sendUniform(uniform_viewMatrix, unitaryMatrix);
	oGLBuffer.sendUniform(uniform_projectionMatrix, unitaryMatrix);
}

void OpenGLManagement::sendViewTransformationMatrix(glm::mat4 viewMatrix, glm::mat4 projectionMatrix) {
	oGLBuffer.sendUniform(uniform_viewMatrix, viewMatrix);
	oGLBuffer.sendUniform(uniform_projectionMatrix, projectionMatrix);
}

void OpenGLManagement::sendViewerPosition(glm::vec3 viewerPosition) {
	oGLBuffer.sendUniform(uniform_viewerPosition, viewerPosition);
}

// Materials
void OpenGLManagement::sendMaterial(Material material) {
	// Material components
	oGLBuffer.sendUniform(uniform_ambient, material.ambient);
	oGLBuffer.sendUniform(uniform_diffuse, material.diffuse);
	oGLBuffer.sendUniform(uniform_specular, material.specular);
	oGLBuffer.sendUniform(uniform_shininess, material.shininess);

	oGLBuffer.sendUniform(uniform_shininess, material.shininess);
	// Material Maps
	// Texture of the object
	oGLBuffer.sendTexture(GL_TEXTURE0, uniform_textureMap, material.textureMap, 0);
	
	// Specular map
	if (material.specularMap != -1) {
		oGLBuffer.sendUniform(uniform_hasSpecularMap, true);
		oGLBuffer.sendTexture(GL_TEXTURE1, uniform_specularMap, material.specularMap, 1);
	} else {
		oGLBuffer.sendUniform(uniform_hasSpecularMap, false);
	}

	// Normal map
	if (material.normalMap != -1) {
		oGLBuffer.sendUniform(uniform_hasNormalMap, true);
		oGLBuffer.sendTexture(GL_TEXTURE2, uniform_normalMap, material.textureMap, 2);
	} else {
		oGLBuffer.sendUniform(uniform_hasNormalMap, false);
	}

	oGLBuffer.sendUniform(uniform_textureScale, material.scale);

	// Materials map
	//GLuint uniform_normalMap;
	// Material bools 
	//GLuint uniform_hasNormalMap;
}

void OpenGLManagement::unbindMaps() {
	oGLBuffer.unbindTexture(GL_TEXTURE0);
	oGLBuffer.unbindTexture(GL_TEXTURE1);
	oGLBuffer.unbindTexture(GL_TEXTURE2);
}

// Lights
void OpenGLManagement::sceneWithLights(bool value) {
	oGLBuffer.sendUniform(uniform_lightEnabled, value);
}

void OpenGLManagement::sendLight(std::vector<Light> light) {

	for (int i = 0; i < light.size(); i++) {
		oGLBuffer.sendUniform(uniform_lightAmbient[i], light.at(i).getAmbient());
		oGLBuffer.sendUniform(uniform_lightDiffuse[i], light.at(i).getDiffuse());
		oGLBuffer.sendUniform(uniform_lightSpecular[i], light.at(i).getSpecular());

		oGLBuffer.sendUniform(uniform_lightDirection[i], light.at(i).getDirection());
		oGLBuffer.sendUniform(uniform_lightType[i], light.at(i).getType());
	}
}

// Calculate the transformation of the entity and send to OPENGL
void OpenGLManagement::sendObject(Vertex * data, GameObject object, int numVertices) {

	glm::mat4 modelMatrix;
	glm::mat3 normalMatrix;

	modelMatrix = glm::translate(modelMatrix, object._translate);
	if (object._angle != 0) {
		modelMatrix = glm::rotate(modelMatrix, glm::radians(object._angle), object._rotation);
	}
	modelMatrix = glm::scale(modelMatrix, object._scale);
	normalMatrix = glm::mat3(glm::transpose(glm::inverse(modelMatrix)));

	oGLBuffer.sendUniform(uniform_modelMatrix, modelMatrix);
	oGLBuffer.sendUniform(uniform_modelNormalMatrix, normalMatrix);

	oGLBuffer.sendDataToGPU(data, numVertices);
}

// Calculate the transformation of the entity and send to OPENGL
void OpenGLManagement::sendObject(Entity entity) {
	glm::mat4 modelMatrix;
	glm::mat3 normalMatrix;
	ObjectTransformation transformation = entity.getTransformation();

	//TODO: Compute its model transformation matrix
	modelMatrix = glm::translate(modelMatrix, transformation.position);
	if (transformation.angle != 0) {
		modelMatrix = glm::rotate(modelMatrix, glm::radians(transformation.angle), transformation.rotation);
	}

	modelMatrix = glm::scale(modelMatrix, transformation.scale);
	normalMatrix = glm::mat3(glm::transpose(glm::inverse(modelMatrix)));

	oGLBuffer.sendUniform(uniform_modelMatrix, modelMatrix);
	oGLBuffer.sendUniform(uniform_modelNormalMatrix, normalMatrix);

	//TODO: Pass the matrix as an uniform 
	//Send data to GPU
	oGLBuffer.sendDataToGPU(&entity.getVertexData(), entity.getNumVertices());
}


// INIT METHODS
void OpenGLManagement::initializeShaders() {
	//Compile the shaders
	oGLBuffer.addShader(GL_VERTEX_SHADER, "./resources/shaders/lvertex-shader.txt");
	oGLBuffer.addShader(GL_FRAGMENT_SHADER, "./resources/shaders/lfragment-shader.txt");
	oGLBuffer.compileShaders();
	//Attributes must be added before linking the code
	oGLBuffer.addAttribute("vertexPosition");
	oGLBuffer.addAttribute("vertexUV");
	oGLBuffer.addAttribute("vertexNormal");

	//Link the compiled shaders
	oGLBuffer.linkShaders();

	// vertex shader
	uniform_modelMatrix = oGLBuffer.getUniformLocation("modelMatrix");
	uniform_modelNormalMatrix = oGLBuffer.getUniformLocation("modelNormalMatrix");

	uniform_viewMatrix = oGLBuffer.getUniformLocation("viewMatrix");
	uniform_projectionMatrix = oGLBuffer.getUniformLocation("projectionMatrix");

	// fragment shader
	uniform_viewerPosition = oGLBuffer.getUniformLocation("viewerPosition");

	// Material vec3
	uniform_ambient = oGLBuffer.getUniformLocation("material.ambient");
	uniform_diffuse = oGLBuffer.getUniformLocation("material.diffuse");
	uniform_specular = oGLBuffer.getUniformLocation("material.specular");
	uniform_shininess = oGLBuffer.getUniformLocation("material.shininess");
	
	uniform_textureScale = oGLBuffer.getUniformLocation("textureScaleFactor");

	// Material bools 
	uniform_hasNormalMap = oGLBuffer.getUniformLocation("hasNormalMap");
	uniform_hasSpecularMap = oGLBuffer.getUniformLocation("hasSpecularMap");

	// Materials map
	oGLBuffer.activateTexture(GL_TEXTURE0);
	uniform_textureMap = oGLBuffer.getUniformLocation("textureData");
	
	oGLBuffer.activateTexture(GL_TEXTURE1);
	uniform_specularMap = oGLBuffer.getUniformLocation("specularMap");

	oGLBuffer.activateTexture(GL_TEXTURE2);
	uniform_normalMap = oGLBuffer.getUniformLocation("normalMap");

	// lights
	uniform_lightEnabled = oGLBuffer.getUniformLocation("lightingEnabled");

	for (int i = 0; i < LIGHTS_SCENE; i++) {
		// set up the uniform light variables
		uniform_lightAmbient[i] = oGLBuffer.getUniformLocation("pointLights[" + std::to_string(i) + "].ambient");
		uniform_lightDiffuse[i] = oGLBuffer.getUniformLocation("pointLights[" + std::to_string(i) + "].diffuse");
		uniform_lightSpecular[i] = oGLBuffer.getUniformLocation("pointLights[" + std::to_string(i) + "].specular");
		uniform_lightPosition[i] = oGLBuffer.getUniformLocation("pointLights[" + std::to_string(i) + "].position");
		uniform_lightDirection[i] = oGLBuffer.getUniformLocation("pointLights[" + std::to_string(i) + "].direction");

		uniform_lightLinear[i] = oGLBuffer.getUniformLocation("pointLights[" + std::to_string(i) + "].linear");
		uniform_lightConstant[i] = oGLBuffer.getUniformLocation("pointLights[" + std::to_string(i) + "].constant");
		uniform_lightQuadratic[i] = oGLBuffer.getUniformLocation("pointLights[" + std::to_string(i) + "].quadratic");
		uniform_lightPower[i] = oGLBuffer.getUniformLocation("pointLights[" + std::to_string(i) + "].power");
		uniform_lightCutoff[i] = oGLBuffer.getUniformLocation("pointLights[" + std::to_string(i) + "].cutoff");

		uniform_lightType[i] = oGLBuffer.getUniformLocation("pointLights[" + std::to_string(i) + "].type");
	}


	oGLBuffer.initializeBuffers();
}
