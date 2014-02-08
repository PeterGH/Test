#pragma once
#include <functional>
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
		const size_t Rows(void) const { return this->rows; }
		const size_t Cols(void) const { return this->cols; }
		void Print(function<void(T&)> p);
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
		if (r < 0 || r >= this->rows) throw invalid_argument(String::Format("Invalid r %d not in [0, %d]", r, this->rows - 1));
		if (c < 0 || c >= this->cols) throw invalid_argument(String::Format("Invalid c %d not in [0, %d]", c, this->cols - 1));
		T & value = *(this->buffer + r * this->cols + c);
		return value;
	}

	template<class T> void Array2D<T>::Print(function<void(T&)> p)
	{
		for (size_t i = 0; i < this->cols; i ++) {
			cout << "\t" << i;
		}

		cout << endl;
		
		for (size_t i = 0; i < this->rows; i ++) {
			cout << i;			
			for (size_t j = 0; j < this->cols; j ++) {
				cout << "\t";
				p(this->operator()(i, j));
			}

			cout << endl;
		}

		cout << endl;
	}

	template<class T> void Array2D<T>::Print(void)
	{
		Print([&](T & e)->void{ cout << e; });
	}
}