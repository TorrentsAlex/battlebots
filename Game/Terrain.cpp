#include "Terrain.h"



Terrain::Terrain() {
}


Terrain::~Terrain() {
}
Terrain::Terrain(OBJ* obj, GameObject gameObject) : Object(obj, gameObject) {}

void Terrain::paintVertex(std::vector<glm::vec3> vertex, glm::vec3 color) {
	float radius = 1.5;
	int totalVertex = vertex.size();
	std::cout << "total vertex to draw: " << totalVertex << std::endl;
	for (int i = 0; i < vertex.size(); i++) {
		for (int j = 0; j < sMesh->faces.size(); j++) {
			// X
			if (sMesh->mesh[j].position.x < vertex.at(i).x + radius &&
				sMesh->mesh[j].position.x > vertex.at(i).x - radius) {
				// Y
				if (sMesh->mesh[j].position.y < vertex.at(i).y + radius &&
					sMesh->mesh[j].position.y > vertex.at(i).y - radius) {	

				}
			}
		}
		totalVertex -= 1;
		std::cout << "vertex remains: " << totalVertex << std::endl;
	}
}