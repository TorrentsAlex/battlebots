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
	OBJ fbxObject;
	
	// Create an instance of the Importer class
	Assimp::Importer importer;
	// And have it read the given file with some example postprocessing
	// Usually - if speed is not the most important aspect for you - you'll 
	// propably to request more postprocessing than we do in this example.
	const aiScene* scene = importer.ReadFile(file,
		aiProcess_Triangulate |
		aiProcess_JoinIdenticalVertices |
		aiProcess_RemoveComponent |
		aiProcess_SortByPType);

	// If the import failed, report it
	if (!scene) {
		cout << "error loading file: " << file << " Error:"
			<< importer.GetErrorString() << endl;
		return fbxObject;
	}

	// get ONLY the first mesh 
	
	const aiMesh* mesh = scene->mMeshes[0];
	
	// init a zero3D vector if not exist some values
	const aiVector3D Zero3D(0.0f, 0.0f, 0.0f);
	fbxObject.numVertices = mesh->mNumVertices;
	// Load all vertexs, normal, and texture coordinates
	for (int i = 0; i < mesh->mNumVertices; i++) {
		if (mesh->mNumVertices >= 1000) {
			std::cout << " " << endl;
		}

		const aiVector3D* pPos = &(mesh->mVertices[i]);
		const aiVector3D* pNormal = mesh->HasNormals() ? &(mesh->mNormals[i]): &Zero3D;
		const aiVector3D* pTexCoord = mesh->HasTextureCoords(0) ? &(mesh->mTextureCoords[0][i]) : &Zero3D;
		
		fbxObject.vertexs.push_back(glm::vec3(pPos->x, pPos->y, pPos->z));
		fbxObject.vertex_normals.push_back(glm::vec3(pNormal->x, pNormal->y, pNormal->z));
		fbxObject.textures_coord.push_back(glm::vec3(pTexCoord->x, pTexCoord->y, pTexCoord->z));
	
	}
	
	// Load the faces of the model
	for (int i = 0; i < mesh->mNumFaces; i++) {
		const aiFace& face = mesh->mFaces[i];
		fbxObject.faces.push_back(face.mIndices[0]);
		// And load the model
		fbxObject.uv.push_back(face.mIndices[1]);

		fbxObject.normals.push_back(face.mIndices[2]);
	}

	// Load the MESH

	fbxObject.mesh = new Vertex[fbxObject.faces.size()];
	for (int i = 0; i < fbxObject.faces.size(); i++) {
		float vPos = fbxObject.faces.at(i);
		float vUV = fbxObject.uv.at(i);
		float vNorm = fbxObject.normals.at(i);

		fbxObject.mesh[i].setPosition(fbxObject.vertexs.at(vPos).x, fbxObject.vertexs.at(vPos).y, fbxObject.vertexs.at(vPos).z);
		fbxObject.mesh[i].setUV(fbxObject.textures_coord.at(vUV).x, fbxObject.textures_coord.at(vUV).y);
		fbxObject.mesh[i].setNormal(fbxObject.vertex_normals.at(vNorm).x, fbxObject.vertex_normals.at(vNorm).y, fbxObject.vertex_normals.at(vNorm).z);
	}
	return fbxObject;
}

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
	// Calculate the max and the minim vertex
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