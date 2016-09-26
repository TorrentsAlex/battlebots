#include "Entity.h"



Entity::Entity() {
}


Entity::~Entity() {
}

Entity::Entity(OBJ mesh, GameObject gameObject) {
	eMesh = mesh;
	eGameObject = gameObject;
	//sBoundingBox.calculateBoundingBoxes(mesh);

	eBoundingBox.setCenter(eGameObject._translate.x, eGameObject._translate.y);
}

// Setters
void Entity::setOBJ(OBJ mesh) {
	eMesh = mesh;
	//sBoundingBox.calculateBoundingBoxes(mesh);
}

void Entity::setGameObject(GameObject gameObject) {
	eGameObject = gameObject;
	eBoundingBox.setCenter(eGameObject._translate.x, eGameObject._translate.y);
}

void Entity::setSquareBoundingBox() {
	haveSquareBBox = true;
	eSquareBoundingBox.setCenter(eGameObject._translate.x, eGameObject._translate.y);
	eSquareBoundingBox.setSize(eMesh.width.y - eMesh.width.x, eMesh.lenght.y - eMesh.lenght.x);
}

void Entity::setPosition(glm::vec3 newPos) {
	eGameObject._translate.x = newPos.x;
	eGameObject._translate.y = newPos.y;
	
}
void Entity::setPosition(glm::vec2 newPos) {
	eGameObject._translate.x = newPos.x;
	eGameObject._translate.y = newPos.y;

}

void Entity::setTextureId(GLuint textureId) {
	eMaterial.textureMap = textureId;
}

void Entity::setMaterial(Material material) {
	eMaterial = material;
}
// Getters
Vertex* Entity::getMesh() {
	return eMesh.mesh;
}

int Entity::getNumVertices() {
	return eMesh.numVertices;
}

GameObject Entity::getGameObject() {
	return eGameObject;
}

Material Entity::getMaterial() {
	return eMaterial;
}

glm::vec3 Entity::getPosition() {
	return eGameObject._translate;
}

float Entity::getXPosition() {
	return eGameObject._translate.x;
}

float Entity::getYPosition() {
	return eGameObject._translate.y;
}

glm::vec3 Entity::getScale() {
	return eGameObject._scale;
}

Sphere Entity::getBoundingBox() {
	return eBoundingBox;
}

Box Entity::getSquareBoundingBox() {
	return eSquareBoundingBox;
}

GLuint Entity::getTextureId() {
	return eMaterial.textureMap;
}

// x y z angle
glm::vec4 Entity::getRotation() {
	glm::vec4 rotation(eGameObject._rotation, eGameObject._angle);
	return rotation;
}
