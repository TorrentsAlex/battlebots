#pragma once
#include "GameObject.h"
#include "OBJ.h"
#include "Sphere.h"
#include "Box.h"
#include "TextureManager.h"
#include "MaterialManager.h"

class Object {
protected:
	OBJ* sMesh;
	GameObject sGameObject;

	Sphere sBoundingBox;
	Box sSquareBoundingBox;
	bool haveSquareBBox;

	string oTexturePath;
	GLuint oTextureId;
	
	Material oMaterial;
public:
	Object();
	Object(OBJ* mesh, GameObject gameObject);
	~Object();

	virtual void update();

	// Setters
	void setOBJ(OBJ* mesh);
	void setGameObject(GameObject gameObject);

	void setSquareBoundingBox();
	void setTextureId(string texturePath);
	void setTextureId(GLuint textureId);
	void setPosition(glm::vec3 newPos);
	void setPosition(glm::vec2 newPos);
	void setMaterial(Material material);

	GLuint getTextureId();
	// Getters
	Vertex* getMesh();
	GameObject getGameObject();
	int getNumVertices();
	Material getMaterial();

	Sphere getBoundingBox();
	Box getSquareBoundingBox();

	glm::vec3 getPosition();
	float getXPosition();
	float getYPosition();
	glm::vec3 getScale();
	// x y z angle
	glm::vec4 getRotation();

};

