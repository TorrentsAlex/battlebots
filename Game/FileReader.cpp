#include "FileReader.h"

FileReader::FileReader() {
}


FileReader::~FileReader() {
}


string FileReader::LoadStringFromFile(string fileName) {
	string fileString;
	string line;
	fileName.replace(0,2, "../battlebots/Game/");
	ifstream myFile(fileName);
	
	if (myFile.is_open()) {
		while (getline(myFile, line)) {

			fileString += line;
		}
		myFile.close();
	} else {
		cout << "Unable to open file!" << fileName << endl;
	}
	return fileString;
}

vector<vector<float>> FileReader::LoadArrayFromFile(string fileName) {
	string line;
	fileName.replace(0, 2, "../battlebots/Game/");

	ifstream myfile(fileName);
	vector<vector<float>> myArray;

	if (myfile.is_open()) {
		vector<float> vline;
		while (getline(myfile, line)) {
			vline = split(line, ' ');
			myArray.push_back(vline);
		}
		myfile.close();
	} else {
		cout << "Unable to open file!" << fileName << endl;
	}
	return myArray;
}

vector<glm::vec3> FileReader::LoadVec3FromFile(string fileName) {
	string line;
	fileName.replace(0, 2, "../battlebots/Game/");

	ifstream myfile(fileName);
	vector<glm::vec3> myArray;

	if (myfile.is_open()) {
		vector<float> vline;
		while (getline(myfile, line)) {
			vline = split(line, ' ');
			myArray.push_back(glm::vec3(vline.at(0), vline.at(1), vline.at(2)));
		}
		myfile.close();
	} else {
		cout << "Unable to open file!" << fileName << endl;
	}
	return myArray;
}


OBJ FileReader::LoadOBJFromFile(string fileName) {
	OBJ object;
	string line;
	fileName.replace(0, 2, "../battlebots/Game/");

	std::string vertex1, vertex2, vertex3;
	vector<float> face1, face2, face3;

	ifstream myfile(fileName);
	if (myfile.is_open()) {

		vector<float> vline;
		glm::vec3 vertex;
		while (getline(myfile, line)) {

			// Vertexs
			if (line.substr(0, 2) == "v ") {
				vline = split(line, ' ');
				vertex.x = vline.at(2);
				vertex.y = vline.at(3);
				vertex.z = vline.at(4);
				object.vertexs.push_back(vertex);
			}

			// Textures
			if (line.substr(0, 2) == "vt") {
				line = line.substr(2, line.size());
				vline = split(line, ' ');
				vertex.x = vline.at(1);
				vertex.y = vline.at(2);
				vertex.z = vline.at(3);
				object.textures_coord.push_back(vertex);
			}

			// Normals
			if (line.substr(0, 2) == "vn") {
				line = line.substr(2, line.size());
				vline = split(line, ' ');
				vertex.x = vline.at(1);
				vertex.y = vline.at(2);
				vertex.z = vline.at(3);
				object.vertex_normals.push_back(vertex);
			}

			// Faces
			if (line.substr(0, 2) == "f ") {
				line = line.substr(2, line.size());

				vector<string> faces = splitString(line, ' ');

				vertex1 = faces.at(0);
				vertex2 = faces.at(1);
				vertex3 = faces.at(2);

				face1 = split(vertex1, '/');
				face2 = split(vertex2, '/');
				face3 = split(vertex3, '/');

				// faces
				object.faces.push_back(face1.at(0) - 1);
				object.faces.push_back(face2.at(0) - 1);
				object.faces.push_back(face3.at(0) - 1);

				// uv
				object.uv.push_back(face1.at(1) - 1);
				object.uv.push_back(face2.at(1) - 1);
				object.uv.push_back(face3.at(1) - 1);

				// normals
				object.normals.push_back(face1.at(2) - 1);
				object.normals.push_back(face2.at(2) - 1);
				object.normals.push_back(face3.at(2) - 1);

			}
		}
		myfile.close();
	} else {
		cout << "Unable to open file!" << fileName << endl;
	}
	return object;
}

void FileReader::SaveArrayToFile(vector<vector<float>> vector, std::string fileName) {
	ofstream file(fileName, ofstream::app);
	if (file.is_open()) {
		for (int i = 0; i < vector.size(); i++) {
			for (int j = 0; j < vector.at(i).size(); j++) {
				file << vector.at(i).at(j);
				// Add ; all lines less the last line 
				if (j < vector.at(i).size() - 1) {
					file << " ";
				}
			}
			file << "\n";
		}
		file.close();
	} else {
		cout << "unable to open file: " << fileName << fileName << endl;
	}
}


bool FileReader::CheckExistFile(std::string fileName) {
	ifstream f(fileName);
	if (f.good()) {
		f.close();
		return true;
	} else {
		f.close();
		return false;
	}
}

// Utils
/*
*	Split the line with the delimiter ';' and put into a vector
*/
vector<float> FileReader::split(const string &line, char delim) {
	stringstream ssLine(line);
	string item;
	vector<float> tokens;
	while (getline(ssLine, item, delim)) { 
		if (item.compare("v") != 0 || item.compare("") != 0 || item.compare("f") != 0) {
			tokens.push_back(atof(item.c_str())); // Convert the string to float
		}
	}
	return tokens;
}

vector<string> FileReader::splitString(const string &line, char delim) {
	stringstream ssLine(line);
	string item;
	vector<string> tokens;
	while (getline(ssLine, item, delim)) {
		tokens.push_back(item.c_str());
	}
	return tokens;
}