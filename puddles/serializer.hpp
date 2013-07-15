#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <tuple>

class Serializer {

public:
	Serializer(std::shared_ptr<std::iostream> ios);
	void readMatrix(std::vector<std::vector<int> >& matrix
								, std::vector<std::tuple<int, int, int> >& tuples);

private:

	Serializer();
	std::shared_ptr<std::iostream> _stream;

};
