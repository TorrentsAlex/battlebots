#pragma once
#include <iostream>
#include <glm/glm.hpp>
#include <GL/glew.h>
#include <glm/glm.hpp>			//OpenGL Mathematics 
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

enum class CameraMode { PERSPECTIVE, ORTHOGRAPHIC, EDITOR};
class Camera {
private: 
	float cAspectRatio;
	glm::mat4 cProjectionMatrix;
	glm::mat4 cViewMatrix;
	float cFOV;
	float cFar;
	float cNear;
	float cProjectionWidth;
	float cProjectionHeight;
	glm::vec3 cCameraPos;
	glm::vec3 cCameraFront;
	glm::vec3 cCameraUp;
	float armLenght;
	CameraMode cCameraMode;
	glm::vec3 cCameraPosOrtho;
	glm::vec3 cCameraPosPersp;
	glm::vec3 cCameraPosEditor;

	float cAngle;

public:
	Camera();
	Camera(Camera& c);
	~Camera();
	void initializeZBuffer(glm::vec2 windowResolution);
	void setPerspectiveCamera();
	void setOrthoCamera();
	void setEditorCamera();
	void setAngle(float angle);

	void setViewMatrix();
	void setCameraPosition(glm::vec3 pos);
	void setCameraFront(glm::vec3 front);
	void setCameraZeditor(float pos);
	float getCameraZeditor();
	float getAngle();

	glm::vec3 getPosition();
	glm::mat4 getProjectionCamera();
	glm::mat4 getViewMatrix();
	float getArmLenght();
};

