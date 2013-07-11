#include <iostream>

#include "serializer.hpp"

int main(int argc, char **argv) {
	Serializer s("puddles.in");
	std::vector<std::vector<int> > v = s.readMatrix();
	for (auto el : v) {
		for (auto val : el) {
			std::cout << val << " ";
		}
		std::cout << std::endl;
	}
}
