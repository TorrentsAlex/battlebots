#include "Entity.h"



Entity::Entity() {
}

Entity::Entity(Vertex* vertex) {
	eVertex = vertex;
}

Entity::~Entity() {
	delete eVertex;
}


// Set The vertex position
void Entity::setVertexPosition(GLfloat x, GLfloat y, GLfloat z) {
	eVertex->setPosition(x, y, z);
}

void Entity::setVertexPosition(glm::vec3 pos) {
	eVertex->setPosition(pos.x, pos.y, pos.z);
}

// Set the vertex uv
void Entity::setVertexUV(GLfloat u, GLfloat v) {
	eVertex->setUV(u, v);
}

void Entity::setVertexUV(glm::vec3 uv) {
	eVertex->setUV(uv.x, uv.y);
}

// Set the vertex Normal
void Entity::setVertexNormal(GLfloat x, GLfloat y, GLfloat z) {
	eVertex->setNormal(x, y, z);
}

void Entity::setVertexNormal(glm::vec3 normal) {
	eVertex->setNormal(normal.x, normal.y, normal.z);
}

void Entity::setNumVertices(int numVertices) {
	eNumVertices = numVertices;
}

// Transformation Methods
void Entity::setPosition(glm::vec3 pos) {
	eObjTransform.position = pos;
}

void Entity::setPosition(float x, float y, float z) {
	eObjTransform.position = glm::vec3(x, y, z);
}

void Entity::setScale(glm::vec3 scale) {
	eObjTransform.scale = scale;
}

void Entity::setScale(float x, float y, float z) {
	eObjTransform.scale = glm::vec3(x, y, z);
}

void Entity::setRotation(glm::vec3 rot, float angle) {
	eObjTransform.scale = rot;
	eObjTransform.angle = angle;
}

void Entity::setRotation(float x, float y, float z, float angle) {
	eObjTransform.rotation = glm::vec3(x, y, z);
	eObjTransform.angle = angle;
}

// Getters
Vertex& Entity::getVertexData() {
	return *eVertex;
}

int Entity::getNumVertices() {
	return eNumVertices;
}

ObjectTransformation Entity::getTransformation() {
	return eObjTransform;
}