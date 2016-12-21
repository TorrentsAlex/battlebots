#include "Entity.h"



Entity::Entity() {
}


Entity::~Entity() {
}

Entity::Entity(OBJ mesh, GameObject gameObject) {
	eMesh = mesh;
	eGameObject = gameObject;
	calculateVolume();
}

// Private Methods

void Entity::calculateVolume() {
	eWidthVolume = eMesh.width.y - eMesh.width.x;
	eHightVolume = eMesh.lenght.y - eMesh.lenght.x;
	eHeightVolume = eMesh.high.y - eMesh.high.x;
}


// Setters
void Entity::setOBJ(OBJ mesh) {
	eMesh = mesh;
	calculateVolume();
}

void Entity::setGameObject(GameObject gameObject) {
	eGameObject = gameObject;
}

void Entity::setCollisionObject(btCollisionObject * btObject) {
	eGameObject.collisionObject = btObject;
}

// Entity transformations
void Entity::setPosition(glm::vec3 newPos) {
	eGameObject.translate.x = newPos.x;
	eGameObject.translate.y = newPos.y;
	
}
void Entity::setPosition(glm::vec2 newPos) {
	eGameObject.translate.x = newPos.x;
	eGameObject.translate.y = newPos.y;
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

OBJ Entity::getOBJ() {
	return eMesh;
}

Material Entity::getMaterial() {
	return eMaterial;
}

btCollisionObject & Entity::getCollisionObject() {
	return *eGameObject.collisionObject;
}

glm::vec3 Entity::getPosition() {
	return eGameObject.translate;
}

float Entity::getXPosition() {
	return eGameObject.translate.x;
}

float Entity::getYPosition() {
	return eGameObject.translate.y;
}

glm::vec3 Entity::getScale() {
	return eGameObject.scale;
}

GLuint Entity::getTextureId() {
	return eMaterial.textureMap;
}

// x y z angle
glm::vec4 Entity::getRotation() {
	glm::vec4 rotation(eGameObject.rotation, eGameObject.angle);
	return rotation;
}

glm::vec3 Entity::getCollisionVolume() {
	return glm::vec3(eWidthVolume, eHightVolume, eHeightVolume);
}