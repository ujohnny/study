#pragma once
#include <vector>
#include <cstddef>
#include <iostream>
#include <cmath>

template <typename T>
class Matrix {
public:
	Matrix(int rows, int columns) : _rows(rows)
								  , _columns(columns)
		{
			_matrix = new std::vector<std::vector<T> >(rows, std::vector<T>(columns));
		}

	Matrix(int rows, int columns
		   , std::vector<std::vector<T> > matrix) : _rows(rows)
												  , _columns(columns)
		{
			_matrix = new std::vector<std::vector<T> >(matrix);
		}

	Matrix(const Matrix<T>& matrix) : _rows(matrix.rows())
									, _columns(matrix.columns())
		{
			_matrix = new std::vector<std::vector<T> >(*matrix.matrix());
		}

	~Matrix() {
		delete _matrix;
	};

	const Matrix operator+(const Matrix& rhs) const {
		Matrix res(_rows, _columns);
		for (size_t i = 0; i < _rows; i++) {
			for (size_t j = 0; j < _columns; j++) {
				res[i][j] = (*_matrix)[i][j] + rhs[i][j];
			}
		}
		return res;
	}

	const Matrix operator-(const Matrix& rhs) const {
		Matrix res(_rows, _columns);
		for (size_t i = 0; i < _rows; i++) {
			for (size_t j = 0; j < _columns; j++) {
				res[i][j] = (*_matrix)[i][j] - rhs[i][j];;
			}
		}
		return res;
	}

	const Matrix& operator*(int scalar) {
		for (size_t i = 0; i < _rows; i++) {
			for (size_t j = 0; j < _columns; j++) {
				(*_matrix)[i][j] *= scalar;
			}
		}
		return (*this);
	}

	const Matrix operator*(const Matrix& rhs) {
		Matrix result(_rows, rhs.columns());
		for (size_t i = 0; i < _rows; i++) {
			for (size_t j = 0; j < rhs.columns(); j++) {
				int tmp = 0;
				for (size_t k = 0; k < _columns; k++) {
					tmp += (*_matrix)[i][k] * rhs[k][j];
				}
				result[i][j] = tmp;
			}
		}
		return result;
	}

	T determinant() {
		if (_rows == 2)
			return ((*_matrix)[0][0] * (*_matrix)[1][1]) - ((*_matrix)[0][1] * (*_matrix)[1][0]);
		T result = 0;
		for (size_t i = 0; i < _columns; i++) {
			result += (*_matrix)[0][i] * pow(-1, i) * (this->removeRow(0).removeColumn(i).determinant());
		}
		return result;

	}

	std::vector<T> getColumn(int col) const {
		std::vector<T> column;
		for (auto it = (*_matrix).begin(); it < (*_matrix).end(); it++) {
			column.push_back((*it)[col]);
		}
		return column;
	}

	std::vector<T> getRow(int row) const {
		return (*_matrix)[row];
	}

	std::vector<T>& operator[](int row) const {
		return (*_matrix)[row];
	}

	std::pair<int, int> getDimensions() const {
		return std::make_pair(rows, columns);
	}

	inline const int rows() const {
		return _rows;
	}
	inline const int columns() const {
		return _columns;
	}
	inline std::vector<std::vector<T> >* matrix() const {
		return _matrix;
	}

	inline void setRows(int rows) {
		_rows = rows;
	}
	inline void setColumns(int columns) {
		_columns = columns;
	}

	Matrix& removeRow(int row) {
		--row;
		_matrix->erase(_matrix->begin() + row);
		--_rows;
		return *this;
	}

	Matrix& removeColumn(int column) {
		--column;
		for (auto it = _matrix->begin(); it < _matrix->end(); it++) {
			it->erase(it->begin() + column);
		}
		--_columns;
		return *this;
	}

	Matrix& transpose() {
		for (size_t i = 0; i < _columns; i++) {
			for (size_t j = 0; j < i; j++) {
				T tmp = _matrix[i][j];
				_matrix[i][j] = _matrix[j][i];
				_matrix[j][i] = tmp;
			}
		}
		return (*this);
	}

	void print(std::ostream& out = std::cout ) {
		for (auto row_it = _matrix->begin(); row_it < _matrix->end(); row_it++) {
			for (auto column_it = row_it->begin(); column_it < row_it->end(); column_it++) {
				out << (*column_it) << "\t";
			}
			out << std::endl;
		}
	}

	void replaceRows(int first, int second) {
		std::vector<int> tmp = (*_matrix)[first];
		(*_matrix)[first] = (*_matrix)[second];
		(*_matrix)[second] = tmp;
	}

	void replaceColumns(int first, int second) {
		for (auto it = _matrix->begin(); it < _matrix->end(); it++) {
			int tmp = (*it)[first];
			(*it)[first] = (*it)[second];
			(*it)[second] = tmp;
		}
	}

	void insertRow(int pos, std::vector<T> row) {
		--pos;
		typename std::vector<std::vector<T> >::iterator it = _matrix->begin();
		_matrix->insert(it + pos, row);
		_rows++;
	}

	void insertColumn(int pos, std::vector<T> column) {
		--pos;
		for (auto it = _matrix->begin(), col_it = column.begin(); it < _matrix->end(); it++, col_it++) {
			auto row_it = it->begin();
			it->insert(row_it + pos, *col_it);
		}
	}

	void replaceRow(int pos, std::vector<T> row) {
		insertRow(pos, row);
		removeRow(pos + 1);
	}

	int pNorm(int p) {
		int result = 0;
		switch (p) {
		case 1:
			for (int i = 0; i < _columns; i++) {
				int tmp = 0;
				for (auto row_it = _matrix->begin(); row_it < _matrix->end(); row_it++) {
					tmp += abs((*row_it)[i]);
				}
				result = (tmp > result) ? tmp : result;
			}
			break;
		case 2:
			for (int i = 0; i < _columns; i++) {
				int tmp = 0;
				for (auto row_it = _matrix->begin(); row_it < _matrix->end(); row_it++) {
					tmp += pow(abs((*row_it)[i]), 2);
				}
				tmp = sqrt(tmp);
				result = (tmp > result) ? tmp : result;
			}

			break;
		case 3:
			for (auto row_it = _matrix->begin(); row_it < _matrix->end(); row_it++) {
				int tmp = 0;
				for (auto col_it = row_it->begin(); col_it < row_it->end(); col_it++) {
					tmp += abs(*col_it);
				}
				result = (tmp > result) ? tmp : result;
			}
			break;
		}
		return result;
	}

private:
	int _columns;
	int _rows;
	std::vector<std::vector<T> > *_matrix;
};
