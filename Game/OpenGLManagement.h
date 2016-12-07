#pragma once
#include <vector>
#include <unordered_map>
#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/vector_angle.hpp>

#include "OpenGL.h"
#include "MaterialManager.h"
#include "Light.h"

#include "GameObject.h"


#define LIGHTS_SCENE 4

enum POLYGONMODE { FILL, WIREFRAME};

class OpenGLManagement {
private:
	OpenGL oGLBuffer;
	
	GLuint uniform_modelMatrix;
	GLuint uniform_modelNormalMatrix;

	GLuint uniform_viewMatrix;
	GLuint uniform_projectionMatrix;

	GLuint uniform_viewerPosition;

	GLuint uniform_textureScale;
	// Material vec3
	GLuint uniform_ambient;
	GLuint uniform_diffuse;
	GLuint uniform_specular;
	GLuint uniform_shininess;
	// Materials map
	GLuint uniform_textureMap;
	GLuint uniform_normalMap;
	GLuint uniform_specularMap;
	// Material bools 
	GLuint uniform_hasNormalMap;
	GLuint uniform_hasSpecularMap;

	// LIGHTS
	GLuint uniform_lightEnabled;

	GLuint uniform_lightAmbient[LIGHTS_SCENE];
	GLuint uniform_lightDiffuse[LIGHTS_SCENE];
	GLuint uniform_lightSpecular[LIGHTS_SCENE];

	GLuint uniform_lightPosition[LIGHTS_SCENE];
	GLuint uniform_lightDirection[LIGHTS_SCENE];

	GLuint uniform_lightLinear[LIGHTS_SCENE];
	GLuint uniform_lightConstant[LIGHTS_SCENE];
	GLuint uniform_lightQuadratic[LIGHTS_SCENE];

	GLuint uniform_lightCutoff[LIGHTS_SCENE];
	GLuint uniform_lightPower[LIGHTS_SCENE];

	GLuint uniform_lightType[LIGHTS_SCENE];

public:
	OpenGLManagement();
	~OpenGLManagement();
	void initializeShaders();

	void sendLight(std::vector<Light> light);
	void sceneWithLights(bool value);
	void sendMaterial(Material material);
	void unbindMaps();

	//void sendObject(Entity entity);
	void sendObject(Vertex * data, GameObject object, int numVertices);
	
	void setFillOrWireframe(POLYGONMODE mode);

	void start();
	void end();

	// if the view and projections are NULL, pass the unitary matrix
	void sendUnitaryViewMatrix();
	void sendViewTransformationMatrix(glm::mat4 viewMatrix, glm::mat4 projectionMatrix);
	void sendViewerPosition(glm::vec3 viewerPosition);
};

