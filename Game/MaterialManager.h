#pragma once
#include <GL/glew.h>

#include <glm/glm.hpp>			//OpenGL Mathematics 
#include <string>

#define METAL 0
#define TERRAIN 1 
#define ENEMY 2
#define GLASS 3
#define NUMMATERIALS 4
struct Material {
	glm::vec3 ambient;
	glm::vec3 diffuse;
	glm::vec3 specular;
	float shininess;
	glm::vec3 direction;
	glm::vec3 position;

	GLuint textureMap;
	GLuint normalMap = -1;
	GLuint specularMap = -1;

	glm::vec2 scale = glm::vec2(1.0f);
};

class MaterialManager {
private:
	Material _materialData[NUMMATERIALS];
	std::string _materialType[NUMMATERIALS];
	void createMaterialDefinitions();
public:
	MaterialManager();
	~MaterialManager();
	Material getMaterialComponents(int materialID);
	int getMaterialID(std::string materialName);
};

