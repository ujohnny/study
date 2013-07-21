#pragma once

#include <vector>
#include <stack>
#include <tuple>

#include "common.hpp"

class Algorithm {

public:
	Matrix<int> execute(const Matrix<int>& matrix
						, const Points<int, int>& tuples);

private:
	int walk(const Matrix<int>& matrix, int x, int y);

	void addNeighbours(const Matrix<int>& matrix
					   , const Point<int>& start
					   , const Point<int>& point
					   , std::stack<Point<int> >& stack);

	void fillWay(const Matrix<int>& Matrix
				 ,const std::vector<Point<int> >& way, int min);

	inline bool checkPoint(const Matrix<int>& matrix
						   , const Point<int>& start
						   , const Point<int>& target) {
		int x1 = start.first;
		int y1 = start.second;

		int x2 = target.first;
		int y2 = target.second;

		return (matrix[x2][y2] <= matrix[x1][y1] && _used[x2][y2] != _mark);
	}

	inline bool isBound(const Matrix<int>& matrix
						, const Point<int>& p) {
		return (p.first == 0 || p.second == 0
				|| p.first == matrix.size() - 1
				|| p.second == matrix[matrix.size() - 1].size() - 1); //HOLY SHIT!
	}

	inline Point<int> top(const Point<int>& p) {
		return std::make_pair(p.first - 1, p.second);
	}

	inline Point<int> bottom(const Point<int>& p) {
		return std::make_pair(p.first + 1, p.second);
	}

	inline Point<int> left(const Point<int>& p) {
		return std::make_pair(p.first, p.second - 1);
	}

	inline Point<int> right(const Point<int>& p) {
		return std::make_pair(p.first, p.second + 1);
	}

	Matrix<unsigned> _used;
	Matrix<int> _puddles;
	int _mark;
};
