#pragma once

#include <fstream>
#include <string>
#include <vector>

class Serializer {

public:

	Serializer(const std::string& filename);
	Serializer(const char* filename);
	~Serializer();
	std::vector<std::vector<int> > readMatrix();

private:

	Serializer();
	std::ifstream in_file;

};
