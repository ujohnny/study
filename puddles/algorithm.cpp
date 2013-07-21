#include "algorithm.hpp"

Matrix<int> Algorithm::execute(const Matrix<int>& matrix
												  , const Points<int, int>& tuples) {
	int height = matrix.size();
	int width = matrix[height - 1].size();

	_mark = 1;
	_puddles = Matrix<int>(height, std::vector<int>(width, -1));
	_used = Matrix<unsigned>(height, std::vector<unsigned>(width, 0));

	for (auto el : tuples) {
		int x = std::get<1>(el);
		int y = std::get<2>(el);

		if (_puddles[x][y] != -1) {
			continue;
		}

		_puddles[x][y] = walk(matrix, x, y);
		++_mark;
	}
	return _puddles;
}

int Algorithm::walk(const Matrix<int>& matrix, int x, int y) {
	int min = 1 << 30;

	_used[x][y] = _mark;
	Point<int> start = std::make_pair(x, y);
	std::vector<Point<int> > way;

	std::stack<Point<int> > s;
	s.push(start);

	while (!s.empty()) {
		Point<int> p = s.top();
		s.pop();

		if (isBound(matrix, p)) {
			while (!s.empty()) {
				auto el = s.top();
				s.pop();

				int i = el.first;
				int j = el.second;
				if (matrix[i][j] - min > 0 )
					_puddles[i][j] = 0;
			}
			return 0;
		}

		way.push_back(p);

		if (matrix[p.first - 1][p.second] > matrix[x][y])
			min = (matrix[p.first - 1][p.second] < min)
				? matrix[p.first - 1][p.second] : min;

		if (matrix[p.first + 1][p.second] > matrix[x][y])
			min = (matrix[p.first + 1][p.second] < min)
				? matrix[p.first + 1][p.second] : min;

		if (matrix[p.first][p.second - 1] > matrix[x][y])
			min = (matrix[p.first][p.second - 1] < min)
				? matrix[p.first][p.second - 1] : min;

		if (matrix[p.first][p.second + 1] > matrix[x][y])
			min = (matrix[p.first][p.second + 1] < min)
				? matrix[p.first][p.second + 1] : min;


		addNeighbours(matrix, start, p, s);
	}
	fillWay(matrix, way, min);
	return (min - matrix[x][y]);
}

void Algorithm::fillWay(const Matrix<int>& matrix
						, const std::vector<Point<int> >& way, int min) {
	for (auto el : way) {
		int x = el.first;
		int y = el.second;

		_puddles[x][y] = (min - matrix[x][y] > 0) ? (min - matrix[x][y]) : 0;
	}
}

void Algorithm::addNeighbours(const Matrix<int>& matrix
							  , const Point<int>& start
							  , const Point<int>& point
							  , std::stack<Point<int> >& stack)
{
	if (checkPoint(matrix, start, left(point))) {
		stack.push(left(point));
		_used[point.first][point.second - 1] = _mark;
	}
	if (checkPoint(matrix, start, right(point))) {
		stack.push(right(point));
		_used[point.first][point.second + 1] = _mark;
	}
	if (checkPoint(matrix, start, top(point))) {
		stack.push(top(point));
		_used[point.first - 1][point.second] = _mark;
	}
	if (checkPoint(matrix, start, bottom(point))) {
		stack.push(bottom(point));
		_used[point.first + 1][point.second] = _mark;
	}
}
