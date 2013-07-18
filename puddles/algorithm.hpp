#pragma once

#include <vector>
#include <queue>
#include <tuple>

#include "common.hpp"

class Algorithm {

public:
	Matrix<int> execute(const Matrix<int>& matrix
										   , const Points<int, int>& tuples);

private:
	int walk(const Matrix<int>& matrix, int x, int y);

	bool isBound(const std::pair<int, int>& p) {};
	void addNeighbours(const std::pair<int, int>& p
					   , const std::queue<std::pair<int, int> >& q) {};
	void fillWay(const std::vector<std::pair<int, int> >& way, int min);


	Matrix<unsigned> _used;
	Matrix<int> _puddles;
	int _mark;
};
