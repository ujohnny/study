#include "serializer.hpp"

Serializer::Serializer(const std::string& filename)
	: in_file(filename)
{
}

Serializer::Serializer(const char *filename)
	: in_file(filename)
{
}

Serializer::~Serializer() {
	in_file.close();
}

std::vector<std::vector<int> > Serializer::readMatrix() {
	int height = 0
		, width = 0;

	in_file >> height >> width;
	std::vector<std::vector<int> > matrix(height
										  , std::vector<int>(width));
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < height; j++) {
			int value = 0;
			in_file >> value;
			matrix[i][j] = value;
		}
	}
	return matrix;
}
