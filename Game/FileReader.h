#pragma once
#include <string>
#include <iostream>
#include <fstream>

#include <vector>
#include <sstream>
#include "OBJ.h"

using namespace std;

class FileReader {
private:
	FileReader();
	~FileReader();
	static vector<float> split(const string &line, char delim);
	static vector<string> splitString(const string &line, char delim);

public:
	/**
	return array of in
	*/
	static vector<vector<float>> LoadArrayFromFile(std::string fileName);
	static vector<glm::vec3> LoadVec3FromFile(std::string fileName);
	static OBJ* LoadOBJFromFile(std::string fileName);

	static OBJ LoadOBJFromFile(std::string fileName, bool yes);

	static void SaveArrayToFile(vector<vector<float>> vector, std::string fileName);

	static bool CheckExistFile(string fileName);

	static string LoadStringFromFile(string fileName);
};