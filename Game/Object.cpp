#include "Object.h"



Object::Object() {
}


Object::~Object() {
}

Object::Object(OBJ* mesh, GameObject gameObject) {
	sMesh = mesh;
	sGameObject = gameObject;
	sBoundingBox.calculateBoundingBoxes(mesh);

	sBoundingBox.setCenter(sGameObject._translate.x, sGameObject._translate.y);
}

// Setters
void Object::setOBJ(OBJ* mesh) {
	sMesh = mesh;
	sBoundingBox.calculateBoundingBoxes(mesh);
}

void Object::setGameObject(GameObject gameObject) {
	sGameObject = gameObject;
	sBoundingBox.setCenter(sGameObject._translate.x, sGameObject._translate.y);
}

void Object::setSquareBoundingBox() {
	haveSquareBBox = true;
	sSquareBoundingBox.setCenter(sGameObject._translate.x, sGameObject._translate.y);
	sSquareBoundingBox.setSize(sMesh->width.y - sMesh->width.x, sMesh->lenght.y - sMesh->lenght.x);
}

void Object::setPosition(glm::vec3 newPos) {
	sGameObject._translate.x = newPos.x;
	sGameObject._translate.y = newPos.y;
	
}
void Object::setPosition(glm::vec2 newPos) {
	sGameObject._translate.x = newPos.x;
	sGameObject._translate.y = newPos.y;

}
void Object::setTextureId(string texturePath) {
	oTexturePath = texturePath;
}

void Object::setTextureId(GLuint textureId) {
	oTextureId = textureId;
}

void Object::setMaterial(Material material) {
	oMaterial = material;
}
// Getters
Vertex* Object::getMesh() {
	return sMesh->mesh;
}

int Object::getNumVertices() {
	return sMesh->numVertices;
}

GameObject Object::getGameObject() {
	return sGameObject;
}

Material Object::getMaterial() {
	return oMaterial;
}

glm::vec3 Object::getPosition() {
	return sGameObject._translate;
}

float Object::getXPosition() {
	return sGameObject._translate.x;
}

float Object::getYPosition() {
	return sGameObject._translate.y;
}

glm::vec3 Object::getScale() {
	return sGameObject._scale;
}

Sphere Object::getBoundingBox() {
	return sBoundingBox;
}

Box Object::getSquareBoundingBox() {
	return sSquareBoundingBox;
}

GLuint Object::getTextureId() {
	return oTextureId;
}


// x y z angle
glm::vec4 Object::getRotation() {
	glm::vec4 rotation(sGameObject._rotation, sGameObject._angle);
	return rotation;
}

// logistic methods

void Object::update() {}