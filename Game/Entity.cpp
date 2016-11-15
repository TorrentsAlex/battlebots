#include "Entity.h"



Entity::Entity() {
}


Entity::~Entity() {
}

Entity::Entity(OBJ mesh, GameObject gameObject) {
	eMesh = mesh;
	eGameObject = gameObject;

}

// Setters
void Entity::setOBJ(OBJ mesh) {
	eMesh = mesh;
}

void Entity::setGameObject(GameObject gameObject) {
	eGameObject = gameObject;
}

void Entity::setCollisionObject(btCollisionObject * btObject) {
	collisionObject = btObject;
}

// Entity transformations
void Entity::setPosition(glm::vec3 newPos) {
	eGameObject._translate.x = newPos.x;
	eGameObject._translate.y = newPos.y;
	
}
void Entity::setPosition(glm::vec2 newPos) {
	eGameObject._translate.x = newPos.x;
	eGameObject._translate.y = newPos.y;
}

// Textures
void Entity::setTextureId(GLuint textureId) {
	eMaterial.textureMap = textureId;
}

void Entity::setTextureSpecular(GLuint specularId) {
	eMaterial.specularMap = specularId;
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

btCollisionObject & Entity::getCollisionObject() {
	return *collisionObject;
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

GLuint Entity::getTextureId() {
	return eMaterial.textureMap;
}

// x y z angle
glm::vec4 Entity::getRotation() {
	glm::vec4 rotation(eGameObject._rotation, eGameObject._angle);
	return rotation;
}
