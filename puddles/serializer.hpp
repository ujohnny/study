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
	void readMatrix(std::vector<std::vector<int> >& matrix
								, Points<int, int> & tuples);

private:

	Serializer();
	std::shared_ptr<std::iostream> _stream;

};
