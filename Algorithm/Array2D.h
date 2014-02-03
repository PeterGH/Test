#pragma once
#include <stdexcept>
#include "String.h"
using namespace std;
namespace Test {
	template<class T> class Array2D {
	private:
		T * buffer;
		size_t rows;
		size_t cols;
	public:
		Array2D(size_t rows, size_t cols);
		~Array2D(void);

		T & operator()(size_t r, size_t c);
		void Print(void);
	};

	template<class T> Array2D<T>::Array2D(size_t rows, size_t cols)
	{
		if (rows <= 0) throw invalid_argument(String::Format("Invalid rows %d", rows));
		if (cols <= 0) throw invalid_argument(String::Format("Invalid cols %d", cols));
		this->rows = rows;
		this->cols = cols;
		size_t c = rows * cols;
		this->buffer = new T[c];
		memset(this->buffer, 0, c * sizeof(T));
	}

	template<class T> Array2D<T>::~Array2D(void)
	{
		if (this->buffer != nullptr) {
			delete[] this->buffer;
			this->buffer = nullptr;
			this->rows = 0;
			this->cols = 0;
		}
	}

	template<class T> T & Array2D<T>::operator()(size_t r, size_t c)
	{
		if (r < 0) throw invalid_argument(String::Format("Invalid r %d", r));
		if (c < 0) throw invalid_argument(String::Format("Invalid c %d", c));
		T & value = *(this->buffer + r * this->cols + c);
		return value;
	}

	template<class T> void Array2D<T>::Print(void)
	{
		for (size_t i = 0; i < this->cols; i ++) {
			cout << "\t" << i;
		}

		cout << endl;
		
		for (size_t i = 0; i < this->rows; i ++) {
			cout << i;			
			for (size_t j = 0; j < this->cols; j ++) {
				cout << "\t" << this->operator()(i, j);
			}

			cout << endl;
		}

		cout << endl;
	}
}