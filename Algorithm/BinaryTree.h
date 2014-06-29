#pragma once
#include <functional>
using namespace std;

namespace Test {

	template<class T, template<class T> class N> class BinaryTree {
	protected:
		N<T> * root;

	public:
		BinaryTree(void) : root(nullptr) {}

		virtual ~BinaryTree(void)
		{
			if (this->root != nullptr) {
				delete this->root;
				this->root = nullptr;
			}
		}

		virtual void Insert(T & content) {}

		void PreOrderWalk(function<void(T)> f)
		{
			if (this->root != nullptr) {
				this->root->PreOrderWalk(f);
			}
		}

		void PreOrderWalkWithStack(function<void(T)> f)
		{
			if (this->root != nullptr) {
				this->root->PreOrderWalkWithStack(f);
			}
		}

		void PreOrderWalkWithStack2(function<void(T)> f)
		{
			if (this->root != nullptr) {
				this->root->PreOrderWalkWithStack2(f);
			}
		}

		void InOrderWalk(function<void(T)> f)
		{
			if (this->root != nullptr) {
				this->root->InOrderWalk(f);
			}
		}

		void InOrderWalkWithStack(function<void(T)> f)
		{
			if (this->root != nullptr) {
				this->root->InOrderWalkWithStack(f);
			}
		}

		void InOrderWalkWithStack2(function<void(T)> f)
		{
			if (this->root != nullptr) {
				this->root->InOrderWalkWithStack2(f);
			}
		}

		void PostOrderWalk(function<void(T)> f)
		{
			if (this->root != nullptr) {
				this->root->PostOrderWalk(f);
			}
		}

		void PostOrderWalkWithStack(function<void(T)> f)
		{
			if (this->root != nullptr) {
				this->root->PostOrderWalkWithStack(f);
			}
		}

		void PostOrderWalkWithStack2(function<void(T)> f)
		{
			if (this->root != nullptr) {
				this->root->PostOrderWalkWithStack2(f);
			}
		}

		int Height(void)
		{
			if (this->root == nullptr) return 0;
			return this->root->Height();
		}

		void Print(void)
		{
			if (this->root != nullptr) this->root->Print();
		}
	};
}