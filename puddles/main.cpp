#include <fstream>
#include "serializer.hpp"
#include "algorithm.hpp"
#include "common.hpp"

int main(int argc, char **argv) {
	Serializer s(std::make_shared<std::fstream>("puddles.in", std::fstream::in));
	Matrix<int> v;
	Points<int> t;
	s.readMatrix(v, t);

	Algorithm a;
	Matrix<int> b = a.execute(v, t);

	std::cout << b << std::endl;
}
