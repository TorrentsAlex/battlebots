#include "Geometry.h"
#include "ErrorManagement.h"
#include <iostream>
#include <fstream>

using namespace std;

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <assimp/vector3.h>

OBJ Geometry::LoadModelFBXFromFile(std::string file) {
	OBJ newOBJ;
	
	// Create an instance of the Importer class
	Assimp::Importer importer;
	// And have it read the given file with some example postprocessing
	// Usually - if speed is not the most important aspect for you - you'll 
	// propably to request more postprocessing than we do in this example.
	const aiScene* scene = importer.ReadFile(file,
		aiProcess_CalcTangentSpace |
		aiProcess_Triangulate |
		aiProcess_JoinIdenticalVertices |
		aiProcess_SortByPType);

	// If the import failed, report it
	if (!scene) {
		cout << "error loading file: " << file << " Error:"
			<< importer.GetErrorString() << endl;
		return newOBJ;
	}
	std::vector<Vertex> vertices;
	std::vector<Vertex> indices;

	// get ONLY the first mesh 
	const aiMesh* mesh = scene->mMeshes[0];

	// init a zero3D vector if not exist some values
	const aiVector3D Zero3D(0.0f, 0.0f, 0.0f);
	for (int i = 0; i < mesh->mNumVertices; i++) {

		const aiVector3D* pPos = &(mesh->mVertices[i]);
		const aiVector3D* pNormal = mesh->HasNormals() ? &(mesh->mNormals[i]): &Zero3D;
	const aiVector3D* pTexCoord = mesh->HasTextureCoords(0) ? &(mesh->mTextureCoords[0][i]) : &Zero3D;
	/*
		Vertex v(Vector3f(pPos->x, pPos->y, pPos->z),
			Vector2f(pTexCoord->x, pTexCoord->y),
			Vector3f(pNormal->x, pNormal->y, pNormal->z));

		vertices.push_back(v);
	*/}
	/*
	    for (unsigned int i = 0 ; i < paiMesh->mNumVertices ; i++) {
        const aiVector3D* pPos = &(paiMesh->mVertices[i]);
        const aiVector3D* pNormal = &(paiMesh->mNormals[i]) : &Zero3D;
        const aiVector3D* pTexCoord = paiMesh->HasTextureCoords(0) ? &(paiMesh->mTextureCoords[0][i]) : &Zero3D;

        Vertex v(Vector3f(pPos->x, pPos->y, pPos->z),
                Vector2f(pTexCoord->x, pTexCoord->y),
                Vector3f(pNormal->x, pNormal->y, pNormal->z));

        Vertices.push_back(v);
    }
    ...
Here we prepare the contents of the vertex buffer by populating the Vertices vector. We use the following attributes of the aiMesh class:
mNumVertices - the number of vertices.
mVertices - an array of mNumVertices vectors that contain the position.
mNormals - an array of mNumVertices vectors that contain the vertex normals.
mTextureCoords - an array of mNumVertices vectors that contain the texture coordinates. 
This is actualy a two dimensional array because each vertex can hold several texture coordinates.
	*/
	// We're done. Everything will be cleaned up by the importer destructor
	return newOBJ;
}

OBJ Geometry::LoadModelFromFile(std::string file) {
	float xMin = 5000, xMax = 0, yMin = 50000, yMax = 0, zMin = 50000, zMax = 0;
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
		// Z
		if (currentVertex.z > zMax) {
			zMax = currentVertex.z;
		}
		if (currentVertex.z < zMin) {
			zMin = currentVertex.z;
		}

	}
	object.width.x = xMin;
	object.width.y = xMax;
	object.lenght.x = yMin;
	object.lenght.y = yMax;
	object.high.x = zMin;
	object.high.y = zMax;

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
		vGObject.push_back(tempObject);
	}
	return vGObject;
}