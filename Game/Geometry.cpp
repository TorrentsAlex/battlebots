#include "Geometry.h"
#include "ErrorManagement.h"
#include <iostream>
#include <fstream>

using namespace std;


OBJ Geometry::LoadModelFromFile(std::string file) {
	float xMin = 5000, xMax = 0, yMin = 50000, yMax = 0;
	glm::vec3 currentVertex;
	// read the file and add the vertex and the faces into the object
	OBJ object = FileReader::LoadOBJFromFile(file);

	// Create the object with the vertices and faces  
	object.mesh = new Vertex[object.faces.size()];
	object.numVertices = object.faces.size();
	float v1, vt1, vn1;
	int iDebug;

	try {
		for (int i = 0; i < object.faces.size(); i++) {
			iDebug = i;
			v1 = object.faces.at(i);
			vt1 = object.uv.at(i);
			vn1 = object.normals.at(i);

			object.mesh[i].setPosition(object.vertexs.at(v1).x, object.vertexs.at(v1).y, object.vertexs.at(v1).z);
			object.mesh[i].setUV(object.textures_coord.at(vt1).x, object.textures_coord.at(vt1).y);
			object.mesh[i].setNormal(object.vertex_normals.at(vn1).x, object.vertex_normals.at(vn1).y, object.vertex_normals.at(vn1).z);
		}
	} catch (std::exception e) {
		std::cerr << "ERROR: " << iDebug << " i " << e.what() << std::endl;
	}
	// We only need to know the vertex, the faces don't 
	for (int i = 0; i < object.vertexs.size(); i++) {
		currentVertex = object.vertexs.at(i);
		if (currentVertex.z < 1) {
			// X 
			if (currentVertex.x > xMax) {
				xMax = currentVertex.x;
			}
			if (currentVertex.x < xMin) {
				xMin = currentVertex.x;
			}
			// Y
			if (currentVertex.y > yMax) {
				yMax = currentVertex.y;
			}
			if (currentVertex.y < yMin) {
				yMin = currentVertex.y;
			}
		}
	}
	object.width.x = xMin;
	object.width.y = xMax;
	object.lenght.x = yMin;
	object.lenght.y = yMax;

	return object;
}

std::vector<GameObject> Geometry::LoadGameElements(std::string file) {
	vector<GameObject> vGObject;
	GameObject tempObject;

	//TODO: Read the content and add it into the data structure
	vector<vector<float>> data = FileReader::LoadArrayFromFile(file);

	for (vector<float> d : data) {
		tempObject._translate = glm::vec3(d.at(0), d.at(1), d.at(2));
		tempObject._angle = d.at(3);
		tempObject._rotation = glm::vec3(d.at(4), d.at(5), d.at(6));
		tempObject._scale = glm::vec3(d.at(7), d.at(8), d.at(9));
		tempObject._textureRepetition = false;
		vGObject.push_back(tempObject);
	}
	return vGObject;
}