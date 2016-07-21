#include "Camera.h"

Camera::Camera(): 
	cAspectRatio(1), 
	cFOV(45.0f), 
	cFar(400.0f), 
	cNear(0.1f), 
	cProjectionWidth(5.0f), 
	cProjectionHeight(5.0f),
	cCameraUp(0.0f,0.0f,0.1f),
	armLenght(5.f),
	cCameraPosPersp(0.01f, -armLenght, 1.5f),
	cCameraPosOrtho(0.01f, 0.0f, 80.0f), 
	cCameraPosEditor(0.01f, 0.0f, 400.0f) {
}

Camera::Camera(Camera& c) {
	cAspectRatio = c.cAspectRatio;
	cFOV = c.cFOV;
	cFar = c.cFar;
	cNear = c.cNear;
	cProjectionWidth = c.cProjectionWidth;
	cProjectionHeight = c.cProjectionHeight;
	cCameraPos = c.cCameraPos;
	cCameraFront = c.cCameraFront;
	cCameraUp = c.cCameraUp;
}

Camera::~Camera() {

}


void Camera::initializeZBuffer(glm::vec2 windowResolution) {
	//Initialize the Zbuffer
	glEnable(GL_DEPTH_TEST);
	glViewport(0, 0, 1280, 800);
	cAspectRatio = 1280.0f/800.0f;
}

// Setters
void Camera::setPerspectiveCamera() {
	cProjectionMatrix = glm::perspective(cFOV,cAspectRatio,cNear,cFar);
	cCameraPos = cCameraPosPersp;
	cCameraFront = glm::vec3(0.0f, 0.0f, 0.0f);

	cCameraMode = CameraMode::PERSPECTIVE;
}

void Camera::setOrthoCamera() {
	cProjectionMatrix = glm::ortho(-cProjectionWidth / 2, cProjectionWidth / 2, -cProjectionHeight / 2, cProjectionHeight / 2, cNear, cFar);
	cCameraPos = cCameraPosOrtho;
	cCameraFront = glm::vec3(0.0f,1.0f,1.0f);

	cCameraMode = CameraMode::ORTHOGRAPHIC;
}
void Camera::setEditorCamera() {
	cProjectionMatrix = glm::ortho(-cProjectionWidth / 2, cProjectionWidth / 2, -cProjectionHeight / 2, cProjectionHeight / 2, cNear, cFar);
	cCameraPos = cCameraPosEditor;
	cCameraFront = glm::vec3(0.0f, 1.0f, 1.0f);

	cCameraMode = CameraMode::EDITOR;
}


void Camera::setViewMatrix() {
	glm::vec3 cameraDirection = glm::normalize(cCameraPos - cCameraFront);
	glm::vec3 up = glm::vec3(0.0f, 0.0f, 1.0f);
	glm::vec3 cameraRight = glm::normalize(glm::cross(up, cameraDirection));
	cCameraUp = glm::cross(cameraDirection, cameraRight);
	cViewMatrix = glm::lookAt(cCameraPos,cCameraFront,cCameraUp);
}

void Camera::setCameraPosition(glm::vec3 pos) {
	if (cCameraMode == CameraMode::PERSPECTIVE) {
		cCameraPos = glm::vec3(pos.x , pos.y, cCameraPosPersp.z);
	} else {
		cCameraPos = glm::vec3(pos.x, pos.y, cCameraPos.z);
	}
	setViewMatrix();
}

void Camera::setCameraFront(glm::vec3 front) {
	switch (cCameraMode) {
		case CameraMode::PERSPECTIVE:
			cCameraFront = glm::vec3(front.x, front.y, front.z + 1.5);
			break;
		case CameraMode::ORTHOGRAPHIC:
			cCameraFront = glm::vec3(front.x, front.y, front.z + 1.0);
			break;
	}
}

// Getters
glm::mat4 Camera::getProjectionCamera() {
	return cProjectionMatrix;
}

glm::mat4 Camera::getViewMatrix() {
	return cViewMatrix;
}

float Camera::getArmLenght() {
	return armLenght;
}

glm::vec3 Camera::getPosition() {
	return cCameraPos;
}

// Editor methtods only
void Camera::setCameraZeditor(float pos) {
	cCameraPosEditor.z = pos;
	std::cout << "z pos: " << pos << std::endl;
	cCameraPos.z = pos;
}

float Camera::getCameraZeditor() {
	return cCameraPosEditor.z; 
}

void Camera::setAngle(float angle) {
	cAngle = angle;
}
float Camera::getAngle() {
	return cAngle;
}