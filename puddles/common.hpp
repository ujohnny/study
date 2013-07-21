#pragma once

#include <iostream>

template <typename T>
using Matrix = std::vector<std::vector<T> >;

template <typename T1, typename T2>
using Points = std::vector<std::tuple<T1, T2, T2> >;

template <typename T>
using Point = std::pair<T, T>;

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
