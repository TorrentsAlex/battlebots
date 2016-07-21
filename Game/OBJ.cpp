#include "OBJ.h"

OBJ::OBJ() {
}

OBJ::~OBJ() {
}
// Private Methods

void OBJ::createModel(glm::vec3 color) {

	// Create the object with the vertices and faces  
	oMesh = new Vertex[oFaces.size()];
	oNumVertices = oFaces.size();

	int v1;
	for (int i = 0; i < oFaces.size(); i++) {
		v1 = oFaces.at(i);

		oMesh[i].setPosition(oVertexs.at(v1).x, oVertexs.at(v1).y, oVertexs.at(v1).z);
		oMesh[i].setColor(color.x, color.y, color.z, 255);
	}
}

// Public methods
void OBJ::setMesh(Vertex* mesh, glm::vec3 color) {
	oMesh = mesh;
	createModel(glm::vec3 color);
}