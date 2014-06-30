#pragma once
#include "BinaryIterator.h"
#include "BinaryNodeWithParent.h"
using namespace std;
namespace Test {
	template<class T> class PostOrderBinaryIteratorWithOutStack : public BinaryIterator<T, BinaryNodeWithParent> {
	private:
		BinaryNodeWithParent<T> * current;
		BinaryNodeWithParent<T> * prev;
	public:
		PostOrderBinaryIteratorWithOutStack(BinaryNodeWithParent<T> * p) : BinaryIterator(p), current(p), prev(p)
		{
			this->operator++();
		}

		PostOrderBinaryIteratorWithOutStack(const PostOrderBinaryIteratorWithOutStack & it) : BinaryIterator(it), current(it.pointer), prev(it.pointer)
		{
			this->operator++();
		}

		PostOrderBinaryIteratorWithOutStack(void) : BinaryIterator(), current(nullptr), prev(nullptr) {}

		// Prefix increment
		// ++ it
		bool operator++() {
			if (this->current == nullptr) {
				this->pointer = nullptr;
			}

			while (this->current != nullptr) {
				if (this->prev == this->current->right) {
					this->pointer = this->current;
					this->prev = this->current;
					this->current = this->current->parent;
					break;
				} else if (this->current->left != nullptr && this->prev != this->current->left) {
					this->prev = this->current;
					this->current = (BinaryNodeWithParent<T> *)this->current->left;
				} else {
					this->prev = this->current;
					if (this->current->right != nullptr) {
						this->current = (BinaryNodeWithParent<T> *)this->current->right;
					} else {
						this->pointer = this->current;
						this->current = this->current->parent;
						break;
					}
				}
			}

			return this->pointer != nullptr;
		}

		// Postfix increment
		// it ++
		bool operator++(int) { return operator++(); }
	};
}