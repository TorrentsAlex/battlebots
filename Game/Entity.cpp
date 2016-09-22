#include "Entity.h"



Entity::Entity() {
}


Entity::~Entity() {
}

Entity::Entity(OBJ* mesh, GameObject gameObject) {
	sMesh = mesh;
	sGameObject = gameObject;
	sBoundingBox.calculateBoundingBoxes(mesh);

	sBoundingBox.setCenter(sGameObject._translate.x, sGameObject._translate.y);
}

// Setters
void Entity::setOBJ(OBJ* mesh) {
	sMesh = mesh;
	sBoundingBox.calculateBoundingBoxes(mesh);
}

void Entity::setGameObject(GameObject gameObject) {
	sGameObject = gameObject;
	sBoundingBox.setCenter(sGameObject._translate.x, sGameObject._translate.y);
}

void Entity::setSquareBoundingBox() {
	haveSquareBBox = true;
	sSquareBoundingBox.setCenter(sGameObject._translate.x, sGameObject._translate.y);
	sSquareBoundingBox.setSize(sMesh->width.y - sMesh->width.x, sMesh->lenght.y - sMesh->lenght.x);
}

void Entity::setPosition(glm::vec3 newPos) {
	sGameObject._translate.x = newPos.x;
	sGameObject._translate.y = newPos.y;
	
}
void Entity::setPosition(glm::vec2 newPos) {
	sGameObject._translate.x = newPos.x;
	sGameObject._translate.y = newPos.y;

}
void Entity::setTextureId(string texturePath) {
	oTexturePath = texturePath;
}

void Entity::setTextureId(GLuint textureId) {
	oTextureId = textureId;
}

void Entity::setMaterial(Material material) {
	oMaterial = material;
}
// Getters
Vertex* Entity::getMesh() {
	return sMesh->mesh;
}

int Entity::getNumVertices() {
	return sMesh->numVertices;
}

GameObject Entity::getGameObject() {
	return sGameObject;
}

Material Entity::getMaterial() {
	return oMaterial;
}

glm::vec3 Entity::getPosition() {
	return sGameObject._translate;
}

float Entity::getXPosition() {
	return sGameObject._translate.x;
}

float Entity::getYPosition() {
	return sGameObject._translate.y;
}

glm::vec3 Entity::getScale() {
	return sGameObject._scale;
}

Sphere Entity::getBoundingBox() {
	return sBoundingBox;
}

Box Entity::getSquareBoundingBox() {
	return sSquareBoundingBox;
}

GLuint Entity::getTextureId() {
	return oTextureId;
}

// x y z angle
glm::vec4 Entity::getRotation() {
	glm::vec4 rotation(sGameObject._rotation, sGameObject._angle);
	return rotation;
}

// logistic methods

void Entity::update() {}