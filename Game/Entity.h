#pragma once
#include "Vertex.h"

class Entity {
protected:
	Vertex* eVertex;
	int eNumVertices;

	ObjectTransformation eObjTransform;


public:
	Entity();
	Entity(Vertex* vertex);
	~Entity();

	void setVertexPosition(GLfloat x, GLfloat y, GLfloat z);
	void setVertexPosition(glm::vec3 pos);

	void setVertexUV(GLfloat u, GLfloat v);
	void setVertexUV(glm::vec3 uv);

	void setVertexNormal(GLfloat x, GLfloat y, GLfloat z);
	void setVertexNormal(glm::vec3 normal);

	void setNumVertices(int numVertices);

	// Transformation methods
	void setPosition(glm::vec3 pos);
	void setPosition(float x, float y, float z);

	void setScale(glm::vec3 scale);
	void setScale(float x, float y, float z);

	void setRotation(glm::vec3 rot, float angle);
	void setRotation(float x, float y, float z, float angle);

	Vertex& getVertexData();
	int getNumVertices();
	ObjectTransformation getTransformation();

};

