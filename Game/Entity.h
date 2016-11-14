#pragma once
#include "GameObject.h"
#include "OBJ.h"
#include "Sphere.h"
#include "Box.h"
#include "TextureManager.h"
#include "MaterialManager.h"
#include <iostream>

class Entity {
protected:
	OBJ eMesh;
	GameObject eGameObject;

	bool haveSquareBBox;
	
	Material eMaterial;

public:
	Entity();
	Entity(OBJ mesh, GameObject gameObject);
	~Entity();

	// Setters
	void setOBJ(OBJ mesh);
	void setGameObject(GameObject gameObject);

	void setSquareBoundingBox();
	
	void setTextureId(GLuint textureId);
	void setTextureSpecular(GLuint specularId);

	void setPosition(glm::vec3 newPos);
	void setPosition(glm::vec2 newPos);
	void setMaterial(Material material);

	GLuint getTextureId();
	// Getters
	Vertex* getMesh();
	GameObject getGameObject();
	int getNumVertices();
	Material getMaterial();

	glm::vec3 getPosition();
	float getXPosition();
	float getYPosition();
	glm::vec3 getScale();
	// x y z angle
	glm::vec4 getRotation();
protected:
	virtual void update() {
		std::cout << "update" << endl;
	}

};

