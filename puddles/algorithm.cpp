#include "algorithm.hpp"

Matrix<int> Algorithm::execute(const Matrix<int>& matrix
												  , const Points<int, int>& tuples) {
	int height = matrix.size();
	int width = matrix[height - 1].size();

	_mark = 0;
	_puddles = Matrix<int>(height, std::vector<int>(width, -1));
	_used = Matrix<unsigned>(height, std::vector<unsigned>(width, 0));

	for (auto el : tuples) {
		int x = std::get<1>(el);
		int y = std::get<2>(el);

		if (_puddles[x][y] != 1) {
			continue;
		}

		_puddles[x][y] = walk(matrix, x, y);
		++_mark;
	}
}

int Algorithm::walk(const Matrix<int>& matrix, int x, int y) {
	int min = 1 << 30;

	_used[x][y] = _mark;
	std::queue<std::pair<int, int> > q;
	q.push(std::make_pair(x, y));
	std::vector<std::pair<int, int> > way;

	while (!q.empty()) {
		std::pair<int, int> p = q.front();
		q.pop();
		way.push_back(p);

		if (matrix[p.first][p.second] < min) {
			min = matrix[p.first][p.second];
		}

		if (isBound(p)) {
			fillWay(way, min);
			return 0;
		}

		addNeighbours(p, q);
	}
	fillWay(way, min);
	return (min - matrix[x][y]);
}

void Algorithm::fillWay(const std::vector<std::pair<int, int> >& way, int min) {
	for (auto el : way) {

	}
}
