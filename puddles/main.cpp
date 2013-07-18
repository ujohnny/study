#include <fstream>
#include "serializer.hpp"
#include "algorithm.hpp"
#include "common.hpp"

int main(int argc, char **argv) {
	Serializer s(std::make_shared<std::fstream>("puddles.in", std::fstream::in));
	Matrix<int> v;
	Points<int, int> t;
	s.readMatrix(v, t);


	Algorithm a;
	Matrix<int> b = a.execute(v, t);

	for (auto el : v) {
		for (auto val : el) {
			std::cout << val << " ";
		}
		std::cout << std::endl;
	}

	for (auto el : t) {
		std::cout << std::get<0>(el) << std::endl;
	}
}
