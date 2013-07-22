#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <tuple>

#include "common.hpp"

class Serializer {

public:
	Serializer(std::shared_ptr<std::iostream> ios);
	void readMatrix(Matrix<int>& matrix
								, Points<int> & tuples);

private:

	Serializer();
	std::shared_ptr<std::iostream> _stream;

};
