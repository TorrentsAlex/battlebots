#include "MaterialManager.h"

MaterialManager::MaterialManager() {
	createMaterialDefinitions();
}
MaterialManager::~MaterialManager() {}

void MaterialManager::createMaterialDefinitions() {
	// We need change the ambient parameter

	_materialData[METAL].ambient = glm::vec3(0.25,0.20725,0.20725);
	_materialData[METAL].diffuse = glm::vec3(0.780392, 0.568627, 0.113725);
	_materialData[METAL].specular = glm::vec3(0.296648, 0.296648, 0.296648);
	_materialData[METAL].shininess = 32;

	_materialData[TERRAIN].ambient = glm::vec3(0.19225, 0.19225, 0.19225);
	_materialData[TERRAIN].diffuse = glm::vec3(0.8, 0.8, 0.8);
	_materialData[TERRAIN].specular = glm::vec3(0.0, 0.0, 0.0);
	_materialData[TERRAIN].shininess = 0.05f;

	_materialData[ENEMY].ambient = glm::vec3(0.25, 0.25, 0.25);
	_materialData[ENEMY].diffuse = glm::vec3(0.4, 0.4, 0.4);
	_materialData[ENEMY].specular = glm::vec3(0.774597, 0.774597, 0.774597);
	_materialData[ENEMY].shininess = 0.6f;

	_materialData[GLASS].ambient = glm::vec3(0.0, 0.0, 0.0);
	_materialData[GLASS].diffuse = glm::vec3(0.588235, 0.670588, 0.729412);
	_materialData[GLASS].specular = glm::vec3(0.9, 0.9, 0.9);
	_materialData[GLASS].shininess = 96.0f;
	//0.25	0.25	0.25	0.4	0.4	0.4	0.774597	0.774597	0.774597	0.6
}

Material MaterialManager::getMaterialComponents(int materialID) {
	return _materialData[materialID];
}

int MaterialManager::getMaterialID(std::string materialName) {
	return 0;
}