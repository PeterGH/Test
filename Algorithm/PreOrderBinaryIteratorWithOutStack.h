#pragma once
#include "BinaryIterator.h"
#include "BinaryNodeWithParent.h"
using namespace std;
namespace Test {
	template<class T> class PreOrderBinaryIteratorWithOutStack : public BinaryIterator<T, BinaryNodeWithParent> {
	private:
		BinaryNodeWithParent<T> * current;
		BinaryNodeWithParent<T> * prev;
	public:
		PreOrderBinaryIteratorWithOutStack(BinaryNodeWithParent<T> * p) : BinaryIterator(p), current(p), prev(p)
		{
			this->operator++();
		}

		PreOrderBinaryIteratorWithOutStack(const PreOrderBinaryIteratorWithOutStack & it) : BinaryIterator(it), current(it.pointer), prev(it.pointer)
		{
			this->operator++();
		}

		PreOrderBinaryIteratorWithOutStack(void) : BinaryIterator(), current(nullptr), prev(nullptr) {}

		// Prefix increment
		// ++ it
		bool operator++() {
			while (this->current != nullptr) {
				if (this->prev == this->current->right) {
					this->prev = this->current;
					this->current = this->current->parent;
				} else if (this->current->left != nullptr && this->prev != this->current->left) {
					this->pointer = this->current;
					this->prev = this->current;
					this->current = (BinaryNodeWithParent<T> *)this->current->left;
					break;
				} else {					
					if (this->current->left == nullptr) {
						this->pointer = this->current;
					}

					this->prev = this->current;
					if (this->current->right != nullptr) {
						this->current = (BinaryNodeWithParent<T> *)this->current->right;
					} else {
						this->current = this->current->parent;
					}

					if (this->pointer == this->prev) {
						break;
					}
				}
			}

			if (this->current == nullptr) {
				this->pointer = nullptr;
			}

			return this->pointer != nullptr;
		}

		// Postfix increment
		// it ++
		bool operator++(int) { return operator++(); }
	};
}