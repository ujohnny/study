#pragma once

#include <vector>
#include <stack>
#include <tuple>

#include "common.hpp"

class Algorithm {

public:
	Matrix<int> execute(const Matrix<int>& matrix
						, const Points<int>& tuples);

private:
	int walk(const Matrix<int>& matrix, int x, int y);

	void addNeighbours(const Matrix<int>& matrix
					   , const Point& start
					   , const Point& point
					   , std::stack<Point >& stack);

	void fillWay(const Matrix<int>& Matrix
				 ,const std::vector<Point >& way, int min);

	int recalcMin(const Matrix<int>& matrix, int min
				 , const Point& start, const Point& p);

	void revertStack(std::stack<Point >& s
					 , const Matrix<int>& matrix
					 , int min);


	inline bool checkPoint(const Matrix<int>& matrix
						   , const Point& start
						   , const Point& target) {
		int x1 = start.first;
		int y1 = start.second;

		int x2 = target.first;
		int y2 = target.second;

		return (matrix[x2][y2] <= matrix[x1][y1] && _used[x2][y2] != _mark);
	}

	inline bool isBound(const Matrix<int>& matrix
						, const Point& p) {
		return (p.first == 0 || p.second == 0
				|| p.first == matrix.size() - 1
				|| p.second == matrix[matrix.size() - 1].size() - 1); //HOLY SHIT!
	}

	inline void markPoint(const Point& p) {
		_used[p.first][p.second] = _mark;
	}

	inline Point top(const Point& p) {
		return std::make_pair(p.first - 1, p.second);
	}

	inline Point bottom(const Point& p) {
		return std::make_pair(p.first + 1, p.second);
	}

	inline Point left(const Point& p) {
		return std::make_pair(p.first, p.second - 1);
	}

	inline Point right(const Point& p) {
		return std::make_pair(p.first, p.second + 1);
	}

	Matrix<unsigned> _used;
	Matrix<int> _puddles;
	int _mark;
};
