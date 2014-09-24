#pragma once
#include "Matrix.h"
namespace Test {
	template<class T> class LowerTriangularMatrix : public Matrix<T> {
	public:
		LowerTriangularMatrix(size_t rows, size_t cols);
		~LowerTriangularMatrix(void) {}
		T & operator()(size_t r, size_t c);
		T operator()(size_t r, size_t c) const;
	};

	template<class T> LowerTriangularMatrix<T>::LowerTriangularMatrix(size_t rows, size_t cols)
	{
		if (rows <= 0) throw invalid_argument(String::Format("Invalid rows %d", rows));
		if (cols <= 0) throw invalid_argument(String::Format("Invalid cols %d", cols));
		this->rows = rows;
		this->cols = cols;
		// if rows <= cols
		//   rows + ... + 2 + 1 = (rows + 1) * rows / 2
		// if rows > cols
		//   rows + (rows - 1) + ... + (rows - (cols - 1)) = rows * cols - (cols - 1) * cols / 2
		size_t c;
		if (rows <= cols) c = ((rows + 1) * rows) >> 1;
		else c = rows * cols - (((cols - 1) * cols) >> 1);
		this->buffer = new T[c];
		memset(this->buffer, 0, c * sizeof(T));
	}

	template<class T> T & LowerTriangularMatrix<T>::operator()(size_t r, size_t c)
	{
		if (r < 0 || r >= this->rows) throw invalid_argument(String::Format("Invalid r %d not in [0, %d]", r, this->rows - 1));
		if (c < 0 || c >= this->cols) throw invalid_argument(String::Format("Invalid c %d not in [0, %d]", c, this->cols - 1));
		if (r < c) throw invalid_argument(String::Format("r %d is smaller than c %d", r, c));
		// if rows <= cols
		//   1 + 2 + ... + i + j = (i + 1) * i / 2 + j
		// if rows > cols
		//   if i <= cols - 1
		//     1 + 2 + ... + i + j = (i + 1) * i / 2 + j
		//   if cols <= i <= rows - 1
		//     1 + 2 + ... + cols + ((i - 1) - (cols - 1)) * cols  + j = (cols + 1) * cols / 2 + (i - cols) * cols + j
		int index;
		if (this->cols <= r && r < this->rows)
			index = (((this->cols + 1) * this->cols) >> 1) + (r - this->cols) * this->cols + c;
		else
			index = (((r + 1) * r) >> 1) + c;
		T & value = *(this->buffer + index);
		return value;
	}

	template<class T> T LowerTriangularMatrix<T>::operator()(size_t r, size_t c) const
	{
		if (r < 0 || r >= this->rows) throw invalid_argument(String::Format("Invalid r %d not in [0, %d]", r, this->rows - 1));
		if (c < 0 || c >= this->cols) throw invalid_argument(String::Format("Invalid c %d not in [0, %d]", c, this->cols - 1));
		if (r < c) return (T)0;
		return this->operator()(r, c);
	}
}