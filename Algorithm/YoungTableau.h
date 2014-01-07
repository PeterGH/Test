#pragma once

#include "Array.h"
#include "MergeSort.h"

namespace Test {
	template<class T> class YoungTableau {
		template<class T> friend Log & operator<<(Log &, const YoungTableau<T> &);
	private:
		unsigned int cols;
		unsigned int rows;
		T * buffer;
		// Count the used space in buffer
		unsigned long size;

		// Get the index of the element above
		int Up(int i) { return i - this->cols; }
		// Get the element above
		T * Up(T * input, int length, int i);
		// Get the index of the element below
		int Down(int i) { return i + this->cols; }
		// Get the element below
		T * Down(T * input, int length, int i);
		// Get the index of the element to the left
		int Left(int i) { return i - 1; }
		// Get the element to the left
		T * Left(T * input, int length, int i);
		// Get the index of the element to the right
		int Right(int i) { return i + 1; }
		// Get the element to the right
		T * Right(T * input, int length, int i);
		// Get the index of the element at the up-left corner
		int UpLeft(int i) { return i - this->cols - 1; }
		// Get the element at the up-left corner
		T * UpLeft(T * input, int length, int i);
		// Get the index of the element at the up-right corner
		int UpRight(int i) { return i - this->cols + 1; }
		// Get the element at the up-right corner
		T * UpRight(T * input, int length, int i);
		// Get the index of the element at the down-left corner
		int DownLeft(int i) { return i + this->cols - 1; }
		// Get the element at the down-left corner
		T * DownLeft(T * input, int length, int i);
		// Get the index of the element at the down-right corner
		int DownRight(int i) { return i + this->cols + 1; }
		// Get the element at the down-right corner
		T * DownRight(T * input, int length, int i);

		// Push the element at index i down through the tableau
		void PushDown(T * input, int length, int i);
		// Push the element at index i up through the tableau
		void PushUp(T * input, int length, int i);
		
	public:
		YoungTableau(unsigned int r, unsigned int c) : rows(r), cols(c), buffer(nullptr), size(0) {}
		YoungTableau(unsigned int r, unsigned int c, const T * input, int length);
		~YoungTableau(void);

		unsigned int Columns(void) { return this->cols; }
		unsigned long MaxSize(void) { return this->rows * this->cols; }

		// Sort all the rows
		void SortRows(T * input, int length);
		// Sort all the columns
		void SortColumns(T * input, int length);
		// Convert the input as a tableau
		void Create(T * input, int length);
		void Create2(T * input, int length);
		// If down is true and the input element is smaller than input[0], 
		// then replace input[0] with the element and push it down. 
		// If down is false and the input element is greater than existing maximum, 
		// then replace maximum with the element and push it up. 
		bool PushElement(T * input, int length, const T & e, bool down = true);
		// Verify if the input is a tableau
		bool Verify(T * input, int length);

		// Init the tableau using an input array
		void Init(const T * input, int length, bool down = true);
		// Push the input array into the tableau, i.e. 
		// append it to the existing elements in the tableau.
		// If the tableau is not initialized, then init the tableau first.
		void Push(const T * input, int length, bool down = true);
		// Push an element into the tableau.
		void Push(const T & e, bool down = true);
		bool Verify(void) { return this->Verify(this->buffer, this->size); }
	};

	template<class T> YoungTableau<T>::YoungTableau(unsigned int r, unsigned int c, const T * input, int length)
		: rows(r), cols(c), buffer(nullptr), size(0)
	{
		Init(input, length);
	}

	template<class T> YoungTableau<T>::~YoungTableau(void)
	{
		if (this->buffer != nullptr) {
			delete[] this->buffer;
			this->buffer = nullptr;
		}
	}

	template<class T> T * YoungTableau<T>::Up(T * input, int length, int i)
	{
		if (input == nullptr || i < 0 || length <= 0 || i >= length) return nullptr;
		int j = Up(i);
		if (j < 0) return nullptr;
		return input + j;
	}

	template<class T> T * YoungTableau<T>::Down(T * input, int length, int i)
	{
		if (input == nullptr || i < 0 || length <= 0 || i >= length) return nullptr;
		int j = Down(i);
		if (j >= length) return nullptr;
		return input + j;
	}

	template<class T> T * YoungTableau<T>::Left(T * input, int length, int i)
	{
		if (input == nullptr || i < 0 || length <= 0 || i >= length) return nullptr;
		if (i % this->cols == 0) return nullptr;
		return input + Left(i);
	}

	template<class T> T * YoungTableau<T>::Right(T * input, int length, int i)
	{
		if (input == nullptr || i < 0 || length <= 0 || i >= length) return nullptr;
		int j = Right(i);
		if (j % this->cols == 0 || j >= length) return nullptr;
		return input + j;
	}

	template<class T> T * YoungTableau<T>::UpLeft(T * input, int length, int i)
	{
		if (input == nullptr || i < 0 || length <= 0 || i >= length) return nullptr;
		int j = UpLeft(i);
		if (j < 0 || i % this->cols == 0) return nullptr;
		return input + j;
	}

	template<class T> T * YoungTableau<T>::UpRight(T * input, int length, int i)
	{
		if (input == nullptr || i < 0 || length <= 0 || i >= length) return nullptr;
		int j = UpRight(i);
		if (j < 0 || j % this->cols == 0) return nullptr;
		return input + j;
	}

	template<class T> T * YoungTableau<T>::DownLeft(T * input, int length, int i)
	{
		if (input == nullptr || i < 0 || length <= 0 || i >= length) return nullptr;
		int j = DownLeft(i);
		if (j >= length || i % this->cols == 0) return nullptr;
		return input + j;
	}

	template<class T> T * YoungTableau<T>::DownRight(T * input, int length, int i)
	{
		if (input == nullptr || i < 0 || length <= 0 || i >= length) return nullptr;
		int j = DownRight(i);
		if (j >= length || j % this->cols == 0) return nullptr;
		return input + j;
	}

	template<class T> void YoungTableau<T>::PushDown(T * input, int length, int i)
	{
		if (input == nullptr || i < 0 || length <= 0 || i >= length) return;

		int min;
		T minVal;

		while (true) {
			min = i;
			minVal = *(input + min);

			// Compare to the right neighbor
			int j = Right(i);
			T * jVal = Right(input, length, i);
			if (j < length && jVal != nullptr && minVal > *jVal) {
				min = j;
				minVal = *jVal;
			}

			// Compare to the down neighbor
			j = Down(i);
			jVal = Down(input, length, i);
			if (j < length && jVal != nullptr && minVal > *jVal) {
				min = j;
			}

			if (min == i) break;
			
			Array::Swap(input, i, min);
			i = min;
		}
	}

	template<class T> void YoungTableau<T>::PushUp(T * input, int length, int i)
	{
		if (input == nullptr || i < 0 || length <= 0 || i >= length) return;

		int max;
		T maxVal;

		while (true) {
			max = i;
			maxVal = *(input + max);

			// Compare to the up neighbor
			int j = Up(i);
			T * jVal = Up(input, length, i);
			if (j >= 0 && jVal != nullptr && maxVal < *jVal) {
				max = j;
				maxVal = *jVal;
			}

			// Compare to the left neighbor
			j = Left(i);
			jVal = Left(input, length, i);
			if (j >= 0 && jVal != nullptr && maxVal < *jVal) {
				max = j;
			}

			if (max == i) break;
			
			Array::Swap(input, i, max);
			i = max;
		}
	}

	template<class T> void YoungTableau<T>::SortRows(T * input, int length)
	{
		if (input == nullptr || length <= 0) return;
		int rows = length / this->cols;
		for (int i = 0; i < rows; i++) {
			int p = i * this->cols;
			int r = p + this->cols - 1;
			MergeSort::Sort(input, p, r);
		}

		int remainders = length % this->cols;
		if (remainders > 0)
			MergeSort::Sort(input, rows * this->cols, length - 1);
	}

	template<class T> void YoungTableau<T>::SortColumns(T * input, int length)
	{
		if (input == nullptr || length <= 0) return;
		int rows = length / this->cols;
		int remainders = length % this->cols;

		for (int i = 0; i < remainders; i++) {
			int p = i;
			int r = i + rows * this->cols;
			MergeSort::Sort(input, p, r, this->cols);
		}

		for (unsigned int i = remainders; i < this->cols; i++) {
			int p = i;
			int r = i + (rows - 1) * this->cols;
			MergeSort::Sort(input, p, r, this->cols);
		}
	}

	template<class T> void YoungTableau<T>::Create(T * input, int length)
	{
		if (input == nullptr || length <= 0) return;

		for (int i = 0; i < length; i++) {
			this->PushUp(input, length, i);
		}
	}

	template<class T> void YoungTableau<T>::Create2(T * input, int length)
	{
		if (input == nullptr || length <= 0) return;

		this->SortRows(input, length);
		this->SortColumns(input, length);
	}

	template<class T> bool YoungTableau<T>::PushElement(T * input, int length, const T & e, bool down)
	{
		if (input == nullptr || length <= 0) return false;

		if (down) {
			if (e > input[0]) {
				input[0] = e;
				this->PushDown(input, length, 0);
				return true;
			}
		} else {
			int max = length - 1;
			T maxVal = input[max];

			int rows = length / this->cols;
			int j = rows * this->cols - 1;
			if (j != max && maxVal < input[j]) {
				max = j;
				maxVal = input[j];
			}

			if (e < maxVal) {
				input[max] = e;
				this->PushUp(input, length, max);
				return true;
			}
		}

		return false;
	}

	template<class T> bool YoungTableau<T>::Verify(T * input, int length)
	{
		if (input == nullptr || length <= 0) return false;

		for (int i = 0; i < length; i++) {
			T & v = input[i];
			T * t = this->Right(input, length, i);
			if (t != nullptr && v > *t) return false;
			t = this->Down(input, length, i);
			if (t != nullptr && v > *t) return false;
			t = this->DownRight(input, length, i);
			if (t != nullptr && v > *t) return false;
		}

		return true;
	}

	template<class T> void YoungTableau<T>::Init(const T * input, int length, bool down)
	{
		if (input == nullptr) throw invalid_argument("input is nullptr");
		if (length <= 0) throw invalid_argument(String::Format("length %d is invalid", length));

		unsigned long maxSize = this->MaxSize();
		if (this->buffer == nullptr) {
			this->buffer = new T[maxSize];
		}

		this->size = min((unsigned long)length, maxSize);
		memcpy_s(this->buffer, maxSize * sizeof(T), input, this->size * sizeof(T));

		this->Create(this->buffer, this->size);

		for (int i = maxSize; i < length; i++) {
			// input size is greater than capacity
			// Push the rest of elements as needed
			this->PushElement(this->buffer, this->size, input[i], down);
		}
	}

	template<class T> void YoungTableau<T>::Push(const T * input, int length, bool down)
	{
		if (input == nullptr) throw invalid_argument("input is nullptr");
		if (length <= 0) throw invalid_argument(String::Format("length %d is invalid", length));

		if (this->buffer == nullptr) {
			Init(input, length);
			return;
		}
		
		unsigned long maxSize = this->MaxSize();
		int l = maxSize - this->size;
		if (l > 0) {			
			for (int i = 0; i < l; i++) {
				this->buffer[this->size] = input[i];
				PushUp(this->buffer, (int)this->size + 1, (int)this->size);
				this->size++;
			}
		} else if (l == 0) {
			for (int i = l; i < length; i++) {
				// Push the rest of elements as needed
				this->PushElement(this->buffer, this->size, input[i], down);
			}
		}
	}

	template<class T> void YoungTableau<T>::Push(const T & e, bool down)
	{
		unsigned long maxSize = this->MaxSize();
		if (this->buffer == nullptr) {
			this->buffer == new T[maxSize];
			this->buffer[0] = e;
			return;
		}

		if (this->size < maxSize) {
			this->buffer[this->size] = e;
			PushUp(this->buffer, (int)this->size + 1, (int)this->size);
			this->size++;
		} else {
			this->PushElement(this->buffer, this->size, e, down);
		}
	}

	template<class T> Log & operator<<(Log & log, const YoungTableau<T> & tableau)
	{
		Array::Print(log, tableau.buffer, tableau.size, tableau.cols);
		return log;
	}
}