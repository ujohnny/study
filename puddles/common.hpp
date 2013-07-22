#pragma once

#include <iostream>

typedef std::pair<int, int> Point;

template <typename T>
using Matrix = std::vector<std::vector<T> >;

template <typename T>
using Points = std::vector<std::tuple<T, int, int> >;

template<typename T>
std::ostream& operator<<(std::ostream& os, const Matrix<T>& matrix) {
	for (auto v : matrix) {
		for (auto el : v) {
			os << el << " ";
		}
		os << "\n";
	}
	return os;
}
