#pragma once
//Third-party libraries
#include <GL/glew.h>			//The OpenGL Extension Wrangler
#include <glm/glm.hpp>			//OpenGL Mathematics 

struct Position {
	GLfloat  x;
	GLfloat  y;
	GLfloat  z;
};

struct NormalVector {
	GLfloat  nx;
	GLfloat  ny;
	GLfloat  nz;
};

struct UV {
	GLfloat u;
	GLfloat v;
};

struct Vertex {
	Position position;
	NormalVector normal;
	UV uv;

	void setPosition(GLfloat  x, GLfloat  y, GLfloat  z) {
		position.x = x;
		position.y = y;
		position.z = z;
	}

	void setUV(float u, float v) {
		uv.u = u;
		uv.v = v;
	}

	void setNormal(GLfloat  x, GLfloat  y, GLfloat  z) {
		normal.nx = x;
		normal.ny = y;
		normal.nz = z;
	}
};

struct ObjectTransformation {
	glm::vec3 position;
	glm::vec3 scale;
	glm::vec3 rotation;
	float angle;
};