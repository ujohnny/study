#include <fstream>
#include "serializer.hpp"

int main(int argc, char **argv) {

	Serializer s(std::make_shared<std::fstream>("puddles.in", std::fstream::in));
	std::vector<std::vector<int> > v;
	std::vector<std::tuple<int, int, int> > t;
	s.readMatrix(v, t);

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
