#pragma once
#include <functional>
#include <stdexcept>
#include "String.h"
using namespace std;
namespace Test {
	template<class T> class Matrix {
	protected:
		T * buffer;
		size_t rows;
		size_t cols;
		// Default constructor for inheritance
		Matrix(void) : rows(0), cols(0), buffer(nullptr) {}
	public:
		Matrix(size_t rows, size_t cols);
		virtual ~Matrix(void);

		virtual T & operator()(size_t r, size_t c);
		virtual T operator()(size_t r, size_t c) const { return this->operator()(r, c); }
		const size_t Rows(void) const { return this->rows; }
		const size_t Cols(void) const { return this->cols; }
	};

	template<class T> Matrix<T>::Matrix(size_t rows, size_t cols)
	{
		if (rows <= 0) throw invalid_argument(String::Format("Invalid rows %d", rows));
		if (cols <= 0) throw invalid_argument(String::Format("Invalid cols %d", cols));
		this->rows = rows;
		this->cols = cols;
		size_t c = rows * cols;
		this->buffer = new T[c];
		memset(this->buffer, 0, c * sizeof(T));
	}

	template<class T> Matrix<T>::~Matrix(void)
	{
		if (this->buffer != nullptr) {
			delete[] this->buffer;
			this->buffer = nullptr;
			this->rows = 0;
			this->cols = 0;
		}
	}

	template<class T> T & Matrix<T>::operator()(size_t r, size_t c)
	{
		if (r < 0 || r >= this->rows) throw invalid_argument(String::Format("Invalid r %d not in [0, %d]", r, this->rows - 1));
		if (c < 0 || c >= this->cols) throw invalid_argument(String::Format("Invalid c %d not in [0, %d]", c, this->cols - 1));
		T & value = *(this->buffer + r * this->cols + c);
		return value;
	}
}