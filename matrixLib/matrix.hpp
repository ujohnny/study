#pragma once
#include <vector>
#include <cstddef>
#include <iostream>
#include <cmath>
#include <iomanip>

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

	Matrix& operator=(const Matrix& rhs) {
		_rows = rhs.rows();
		_columns = rhs.columns();
		_matrix = new std::vector<std::vector<T> >(*rhs.matrix());
	}

	const Matrix operator+(const Matrix& rhs) const {
		Matrix<T> res(_rows, _columns);
		for (size_t i = 0; i < _rows; i++) {
			for (size_t j = 0; j < _columns; j++) {
				res[i][j] = (*_matrix)[i][j] + rhs[i][j];
			}
		}
		return res;
	}

	const Matrix operator-(const Matrix& rhs) const {
		Matrix<T> res(_rows, _columns);
		for (size_t i = 0; i < _rows; i++) {
			for (size_t j = 0; j < _columns; j++) {
				res[i][j] = (*_matrix)[i][j] - rhs[i][j];;
			}
		}
		return res;
	}

	const Matrix operator*(T scalar) {
		Matrix<T> res(_rows, _columns);
		for (size_t i = 0; i < _rows; i++) {
			for (size_t j = 0; j < _columns; j++) {
				res[i][j] = (*_matrix)[i][j] * scalar;
			}
		}
		return res;
	}

	const Matrix operator*(const Matrix& rhs) {
		Matrix<T> result(_rows, rhs.columns());

		for (size_t i = 0; i < _rows; i++) {
			for (size_t j = 0; j < rhs.columns(); j++) {
				T tmp = 0;
				for (size_t k = 0; k < _columns; k++) {
					tmp += (*_matrix)[i][k] * rhs[k][j];
				}
				result[i][j] = tmp;
			}
		}
		return result;
	}

	T determinant() const {
		if (_rows == 2)
			return ((*_matrix)[0][0] * (*_matrix)[1][1]) - ((*_matrix)[0][1] * (*_matrix)[1][0]);
		T result = 0;
		for (size_t i = 0; i < _columns; i++) {
			Matrix<T> tmp(*this);
			result += (*_matrix)[0][i] * pow(-1, i) * (tmp.removeRow(0).removeColumn(i).determinant());
		}
		return result;
	}

	std::vector<T> getColumn(size_t col) const {
		std::vector<T> column;
		for (auto it = (*_matrix).begin(); it < (*_matrix).end(); it++) {
			column.push_back((*it)[col]);
		}
		return column;
	}

	std::vector<T> getRow(size_t row) const {
		return (*_matrix)[row];
	}

	std::vector<T>& operator[](size_t row) const {
		return (*_matrix)[row];
	}

	std::pair<size_t, size_t> getDimensions() const {
		return std::make_pair(rows, columns);
	}

	inline const size_t rows() const {
		return _rows;
	}
	inline const size_t columns() const {
		return _columns;
	}
	inline std::vector<std::vector<T> >* matrix() const {
		return _matrix;
	}

	inline void setRows(size_t rows) {
		_rows = rows;
	}
	inline void setColumns(size_t columns) {
		_columns = columns;
	}

	Matrix& removeRow(size_t row) {
		_matrix->erase(_matrix->begin() + row);
		--_rows;
		return *this;
	}

	Matrix& removeColumn(size_t column) {
		for (auto it = _matrix->begin(); it < _matrix->end(); it++) {
			it->erase(it->begin() + column);
		}
		--_columns;
		return *this;
	}

	Matrix transpose() const {
		Matrix<T> result(_columns, _rows);

		for (size_t i = 0; i < _columns; i++) {
			for (size_t j = 0; j < _rows; j++) {
				result[i][j] = (*_matrix)[j][i];
			}
		}
		return result;
	}

	void print(std::ostream& out = std::cout ) const {
		for (auto row_it = _matrix->begin(); row_it < _matrix->end(); row_it++) {
			for (auto column_it = row_it->begin(); column_it < row_it->end(); column_it++) {
				out << (*column_it) << "\t";
			}
			out << std::endl;
		}
	}

	void swapRows(size_t first, size_t second) {
		std::swap((*_matrix)[first], (*_matrix)[second]);
	}

	void swapColumns(int first, int second) {
		for (auto it = _matrix->begin(); it < _matrix->end(); it++) {
			std::swap((*it)[first], (*it)[second]);
		}
	}

	void insertRow(int pos, std::vector<T> row) {
		typename std::vector<std::vector<T> >::iterator it = _matrix->begin();
		_matrix->insert(it + pos, row);
		_rows++;
	}

	void insertColumn(int pos, std::vector<T> column) {
		for (auto it = _matrix->begin(), col_it = column.begin(); it < _matrix->end(); it++, col_it++) {
			auto row_it = it->begin();
			it->insert(row_it + pos, *col_it);
		}
		_columns++;
	}

	void replaceRow(int pos, std::vector<T> row) {
		insertRow(pos, row);
		removeRow(pos + 1);
	}

	void replaceColumn(int pos, std::vector<T> column) {
		insertColumn(pos, column);
		removeColumn(pos + 1);
	}

	void replaceRow(int pos, const Matrix& m) {
		if (m.rows() != 1) {
			return;
		}
		typename std::vector<T> row = (*m.matrix())[0];
		replaceRow(pos, row);
	}

	void replaceColumn(int pos, const Matrix& m) {
		if (m.columns() != 1) {
			return;
		}

		typename std::vector<T> column;

		for (auto it = m.matrix()->begin(); it < m.matrix()->end(); it++) {
			column.push_back((*it)[0]);
		}
		replaceColumn(pos, column);
	}

	T pNorm(int p) const {
		T result = 0;
		switch (p) {
		case 1:
			for (int i = 0; i < _columns; i++) {
				T tmp = 0;
				for (auto row_it = _matrix->begin(); row_it < _matrix->end(); row_it++) {
					tmp += fabs((*row_it)[i]);
				}
				result = (tmp > result) ? tmp : result;
			}
			break;
		case 2:
			for (int i = 0; i < _columns; i++) {
				T tmp = 0;
				for (auto row_it = _matrix->begin(); row_it < _matrix->end(); row_it++) {
					tmp += pow(fabs((*row_it)[i]), 2);
				}
				tmp = sqrt(tmp);
				result = (tmp > result) ? tmp : result;
			}

			break;
		case 3:
			for (auto row_it = _matrix->begin(); row_it < _matrix->end(); row_it++) {
				T tmp = 0;
				for (auto col_it = row_it->begin(); col_it < row_it->end(); col_it++) {
					tmp += fabs(*col_it);
				}

				result = (tmp > result) ? tmp : result;
			}
			break;
		}
		return result;
	}

	T operator^(const Matrix& rhs) {
		T res = 0;
		for (int i = 0; i < _columns; i++) {
			res += (*this)[0][i] * rhs[0][i];
		}
		return res;
	}

	friend std::ostream& operator<< (std::ostream& out, const Matrix& m) {
		std::vector<std::vector<T> > *matrix = m.matrix();
		for (auto row_it = matrix->begin(); row_it < matrix->end(); row_it++) {
			for (auto column_it = row_it->begin(); column_it < row_it->end(); column_it++) {
				out << std::setw(15) << std::left << (*column_it);
			}
			out << std::endl;
		}
		return out;
	}

private:
	int _columns;
	int _rows;
	std::vector<std::vector<T> > *_matrix;
};
