#pragma once

#include "OBJ.h"
#include "TextureManager.h"
#include "MaterialManager.h"

#include <iostream>

#include <btBulletCollisionCommon.h>

struct GameObject {
	glm::vec3 translate;
	float angle;
	glm::vec3 rotation;
	glm::vec3 scale;
	btCollisionObject* collisionObject;

};

class Entity {
protected:
	string id;

	OBJ eMesh;
	GameObject eGameObject;
	
	Material eMaterial;

	btScalar eWidthVolume; // X 
	btScalar eHightVolume; // Y 
	btScalar eHeightVolume; // Z

private:
	void calculateVolume();

public:
	Entity();
	Entity(OBJ mesh, GameObject gameObject);
	~Entity();

	// Setters
	void setOBJ(OBJ mesh);
	void setGameObject(GameObject gameObject);

	void setCollisionObject(btCollisionObject*  btObject);
	
	void setTextureId(GLuint textureId);
	void setTextureSpecular(GLuint specularId);

	void setPosition(glm::vec3 newPos);
	void setPosition(glm::vec2 newPos);
	void setMaterial(Material material);

	GLuint getTextureId();
	// Getters
	Vertex* getMesh();
	GameObject getGameObject();
	OBJ getOBJ();
	int getNumVertices();
	Material getMaterial();
	btCollisionObject& getCollisionObject();

	glm::vec3 getPosition();
	float getXPosition();
	float getYPosition();
	glm::vec3 getScale();

	glm::vec3 getCollisionVolume();

	// x y z angle
	glm::vec4 getRotation();
protected:
	virtual void update() {
		std::cout << "update" << endl;
	}

};

