#include <algorithm>

#include "serializer.hpp"

Serializer::Serializer(std::shared_ptr<std::iostream> ios)
	: _stream(ios)
{
}

void Serializer::readMatrix(Matrix<int>& matrix
							, Points<int>& tuples)
{
	int height = 0
		, width = 0;

	(*_stream) >> height >> width;

	matrix = Matrix<int>(height
						 , std::vector<int>(width));

	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			int value = 0;
			(*_stream) >> value;
			matrix[i][j] = value;
			tuples.push_back(std::make_tuple(value, i, j));
		}
	}

	auto comparator = [](const std::tuple<int, int, int>& lhs
						 , const std::tuple<int, int, int> & rhs) {
		return (std::get<0>(lhs) > std::get<0>(rhs));
	};

	std::sort(tuples.begin(), tuples.end(), comparator);
}
