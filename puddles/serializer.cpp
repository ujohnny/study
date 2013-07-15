#include "serializer.hpp"

Serializer::Serializer(std::shared_ptr<std::iostream> ios)
	: _stream(ios)
{
}

void Serializer::readMatrix(std::vector<std::vector<int> >& matrix
							, std::vector<std::tuple<int, int, int> >& tuples)
{
	int height = 0
		, width = 0;

	(*_stream) >> height >> width;

	matrix = std::vector<std::vector<int> >(height
											, std::vector<int>(width));

	for (int i = 0; i < height; i++) {
		for (int j = 0; j < height; j++) {
			int value = 0;
			(*_stream) >> value;
			matrix[i][j] = value;
			tuples.push_back(std::make_tuple(value, i, j));
		}
	}
}
