#pragma once
#include <functional>
#include "Array.h"
#include "BinarySearch.h"
#include "MergeSort.h"
#include "Search.h"
#include "Sort.h"
using namespace std;
namespace Test {
	template<class T> class YoungTableau {
		template<class T> friend Log & operator<<(Log &, const YoungTableau<T> &);
	private:
		unsigned int cols;
		unsigned int rows;
		T * buffer;
		// Count the used space in buffer
		unsigned long size;

		pair<int, int> Coordinate(int i) { return make_pair(i / this->cols, i % this->cols); }
		int Index(int r, int c) { return r * this->cols + c; }

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

		pair<int, int> SearchInternal(const T & e, int i0, int j0, int i1, int j1);

		unsigned long CountLessThanInternal(const T & e, int i0, int j0, int i1, int j1);
		
	public:
		YoungTableau(unsigned int r, unsigned int c) : rows(r), cols(c), buffer(nullptr), size(0) {}
		YoungTableau(unsigned int r, unsigned int c, const T * input, int length);
		~YoungTableau(void);

		// Get the rows of used space
		unsigned int Rows(void);
		unsigned int Columns(void) { return this->cols; }
		unsigned long MaxSize(void) { return this->rows * this->cols; }
		// Get the count of elements at the last row
		unsigned int LastRowSize(void) { return this->size % this->cols; }

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

		T & operator()(size_t r, size_t c);
		pair<int, int> Search(const T & e);
		pair<int, int> Search2(const T & e);

		unsigned long CountLessThan(const T & e);
		unsigned long CountLessThan2(const T & e);
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

	template<class T> unsigned int YoungTableau<T>::Rows(void)
	{
		unsigned int rows = this->size / this->cols;
		if (this->size % this->cols > 0) rows++;
		return rows;
	}

	template<class T> void YoungTableau<T>::SortRows(T * input, int length)
	{
		if (input == nullptr || length <= 0) return;
		int rows = length / this->cols;
		for (int i = 0; i < rows; i++) {
			int p = i * this->cols;
			int r = p + this->cols - 1;
			Sort::Merge::Sort(input, p, r);
		}

		int remainders = length % this->cols;
		if (remainders > 0)
			Sort::Merge::Sort(input, rows * this->cols, length - 1);
	}

	template<class T> void YoungTableau<T>::SortColumns(T * input, int length)
	{
		if (input == nullptr || length <= 0) return;
		int rows = length / this->cols;
		int remainders = length % this->cols;

		for (int i = 0; i < remainders; i++) {
			int p = i;
			int r = i + rows * this->cols;
			Sort::Merge::Sort(input, p, r, this->cols);
		}

		for (unsigned int i = remainders; i < this->cols; i++) {
			int p = i;
			int r = i + (rows - 1) * this->cols;
			Sort::Merge::Sort(input, p, r, this->cols);
		}
	}

	template<class T> void YoungTableau<T>::Create(T * input, int length)
	{
		if (input == nullptr || length <= 0) return;

		auto print = [&](){
			for (unsigned int i = 0; i < this->Columns(); i++) {
				cout << "\t" << i;
			}
			cout << endl;

			int rows = length / this->Columns();
			for (int i = 0; i < rows; i++) {
				cout << i;
				for (unsigned int j = 0; j < this->Columns(); j++) {
					cout << "\t" << *(input + i * this->Columns() + j);
				}
				cout << endl;
			}

			int remainders = length % this->Columns();
			if (remainders > 0) {
				cout << rows;
				for (int j = 0; j < remainders; j++) {
					cout << "\t" << *(input + rows * this->Columns() + j);
				}
				cout << endl;
			}
			cout << endl;
		};

		// print();
		for (int i = 0; i < length; i++) {
			this->PushUp(input, length, i);
			// print();
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
			Init(input, length, down);
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
		log.Print(tableau.buffer, tableau.size, tableau.cols);
		return log;
	}

	template<class T> T & YoungTableau<T>::operator()(size_t r, size_t c)
	{
		if (r < 0 || r >= this->rows) throw invalid_argument(String::Format("Invalid r %d not in [0, %d]", r, this->rows - 1));
		if (c < 0 || c >= this->cols) throw invalid_argument(String::Format("Invalid c %d not in [0, %d]", c, this->cols - 1));
		unsigned int i = Index(r, c);
		if (i >= this->size) throw invalid_argument(String::Format("Invalid i %d not in [0, %d]", i, this->size - 1));
		T & value = *(this->buffer + i);
		return value;
	}

	template<class T> pair<int, int> YoungTableau<T>::Search(const T & e)
	{
		// Default if not found
		pair<int, int> r = make_pair(-1, -1);

		if (this->size == 0) return r;

		if (this->Rows() == 1) {
			int j = Search::BinarySearch<T>(e, this->buffer, this->size);
			if (j == -1) return r;
			return make_pair(0, j);
		}

		int i = 0;
		int j = this->cols - 1;
		int k = this->Index(i, j);
		T * c = this->buffer + k;
		while (c != nullptr) {
			if (*c < e) {
				c = Down(this->buffer, this->size, k);
				i++;
			} else if (*c > e) {
				c = Left(this->buffer, this->size, k);
				j--;
			} else {
				return make_pair(i, j);
			}
			k = this->Index(i, j);
		}

		int remainders = this->LastRowSize();
		if (remainders > 0) {
			int lastRow = this->size / this->cols;
			if (i == lastRow) {
				// Need to check the last row, which is not filled up fully
				int j = Search::BinarySearch<T>(e, this->buffer + i * this->cols, remainders);
				if (j != -1) return make_pair(i, j);
			}
		}

		return r;
	}

	template<class T> pair<int, int> YoungTableau<T>::SearchInternal(const T & e, int i0, int j0, int i1, int j1)
	{
		if (i0 == i1) {
			int j = Search::BinarySearch<T>(e, this->buffer + this->Index(i0, j0), j1 - j0 + 1);
			if (j == -1) return make_pair(-1, -1);
			else return make_pair(i0, j0 + j);
		}

		if (j0 == j1) {
			for (int i = i0; i <= i1; i++) {
				int k = this->Index(i, j0);
				if (this->buffer[k] == e) return make_pair(i, j0);
			}
			return make_pair(-1, -1);
		}

		int i = (i0 + i1) >> 1;
		// j is biased by j0
		int j = Search::FindPositionToInsert<T>(e, this->buffer + this->Index(i, j0), j1 - j0 + 1);

		if (j < j1 - j0) {
			T & v = this->buffer[this->Index(i, j0 + j + 1)];
			if (v == e) return make_pair(i, j0 + j + 1);
			if (i > i0) {
				// Search the top-right area
				pair<int, int> r = SearchInternal(e, i0, j0 + j + 1, i - 1, j1);
				if (r.first != -1 && r.second != -1) return r;
			}
		}

		if (j > -1) {
			if (i == i1) {
				// We are down because no more rows to search
				return make_pair(-1, -1);
			}
			// Search the bottom-left hald
			return SearchInternal(e, i + 1, j0, i1, j0 + j);
		}

		return make_pair(-1, -1);
	}

	template<class T> pair<int, int> YoungTableau<T>::Search2(const T & e)
	{
		int rows = this->Rows();
		int remainders = this->LastRowSize();
		if (remainders == 0) {
			return SearchInternal(e, 0, 0, rows - 1, this->cols - 1);
		}

		if (rows > 1) {
			pair<int, int> r = SearchInternal(e, 0, 0, rows - 2, this->cols - 1);
			if (r.first != -1 && r.second != -1) return r;
		}

		int j = Search::BinarySearch<T>(e, this->buffer + this->Index(rows - 1, 0), remainders);
		if (j == -1) return make_pair(-1, -1);
		else return make_pair(rows - 1, j);
	}

	template<class T> unsigned long YoungTableau<T>::CountLessThanInternal(const T & e, int i0, int j0, int i1, int j1)
	{
		int i = i0;
		int j = j0;
		while (i <= i1 && j <= j1) {
			int k = this->Index(i, j);
			if (this->buffer[k] >= e) break;
			i++;
			j++;
		}

		if (i == i0 && j == j0) return 0;

		unsigned long count = (i - i0) * (j - j0);

		if (j <= j1) {
			count += CountLessThanInternal(e, i0, j, i > i1 ? i1 : i - 1, j1);
		}

		if (i <= i1) {
			count += CountLessThanInternal(e, i, j0, i1, j > j1 ? j1 : j - 1);
		}

		return count;
	}

	template<class T> unsigned long YoungTableau<T>::CountLessThan(const T & e)
	{
		int rows = this->Rows();
		int remainders = this->LastRowSize();
		if (remainders == 0) {
			return this->CountLessThanInternal(e, 0, 0, rows - 1, this->cols - 1);
		}

		int count = 0;
		if (rows > 1) {
			count = this->CountLessThanInternal(e, 0, 0, rows - 2, this->cols - 1);
		}

		int j = Search::FindPositionToInsert<T>(e, this->buffer + this->Index(rows - 1, 0), remainders);
		count += (j + 1);

		return count;
	}

	template<class T> unsigned long YoungTableau<T>::CountLessThan2(const T & e)
	{
		int rows = this->Rows();
		int remainders = this->LastRowSize();

		int r = remainders > 0 ? rows - 1 : rows;
		int c = this->cols;

		int count = 0;
		for (int j = 0; j < min(r, c); j++) {
			int t = 0;
			for (int i = 0; i <= j; i++) {
				int k = this->Index(i, j - i);
				if (this->buffer[k] < e) t++;
			}
			if (t == 0) break;
			else count += t;
		}

		if (r < c) {
			for (int j = r; j < c; j++) {
				int t = 0;
				for (int i = 0; i < r; i++) {
					int k = this->Index(i, j - i);
					if (this->buffer[k] < e) t++;
				}
				if (t == 0) break;
				else count += t;
			}
			for (int j = c - r + 1; j < c; j++) {
				int t = 0;
				for (int i = j - (c - r); i < r; i++) {
					int k = this->Index(i, j - i + r - 1);
					if (this->buffer[k] < e) t++;
				}
				if (t == 0) break;
				else count += t;
			}

		} else if (r > c) {
			for (int i = c; i < r; i++) {
				int t = 0;
				for (int j = 0; j < c; j++) {
					int k = this->Index(i - j, j);
					if (this->buffer[k] < e) t++;
				}
				if (t == 0) break;
				else count += t;
			}
			for (int i = r - c + 1; i < r; i++) {
				int t = 0;
				for (int j = i - (r - c); j < c; j++) {
					int k = this->Index(i - j + c - 1, j);
					if (this->buffer[k] < e) t++;
				}
				if (t == 0) break;
				else count += t;
			}
		}

		if (remainders > 0) {
			int j = Search::FindPositionToInsert<T>(e, this->buffer + this->Index(rows - 1, 0), remainders);
			count += (j + 1);
		}

		return count;
	}
}