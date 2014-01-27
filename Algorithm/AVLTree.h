#pragma once

#include <functional>
#include <vector>

using namespace std;

namespace Test {
	template<class T> class AVLTree {
	private:
		class Node {
			template<class T> friend class AVLTree;
		private:
			T content;
			Node * parent;
			Node * left;
			Node * right;
			int height;

		public:
			Node(const T & c) : content(c), parent(nullptr), left(nullptr), right(nullptr), height(1) {}
			// Not delete its children
			~Node(void)
			{
				auto f = [](Node * p) { if (p != nullptr) { p = nullptr; } };
				f(this->left);
				f(this->right);
				f(this->parent);
			}

			static void PostOrderWalk(Node * node, function<void(Node *)> f)
			{
				if (node == nullptr || f == nullptr) return;
				PostOrderWalk(node->left, f);
				PostOrderWalk(node->right, f);
				f(node);
			}

			static void Empty(Node* node)
			{
				PostOrderWalk(node->left, [](Node * x){ delete x; });
				PostOrderWalk(node->right, [](Node * x){ delete x; });
				node->left = nullptr;
				node->right = nullptr;
			}

			static bool Verify(Node * node)
			{
				if (node == nullptr) return true;
				if (node->left == nullptr && node->right == nullptr) {
					if (node->height != 1) return false;
				}

				if (node->left == nullptr && node->right != nullptr) {
					if (node->right->height != 1) return false;
					if (node->height != 2) return false;
				}

				if (node->left != nullptr && node->right == nullptr) {
					if (node->left->height != 1) return false;
					if (node->height != 2) return false;
				}
				
				if (node->left != nullptr && node->right != nullptr) {
					if (node->left->height - node->right->height > 1) return false;
					if (node->right->height - node->left->height > 1) return false;
					if (node->height != 1 + std::max(node->left->height, node->right->height)) return false;
				}

				if (node->left != nullptr && !Verify(node->left)) return false;

				if (node->right != nullptr && !Verify(node->right)) return false;

				return true;
			}

			static stringstream & ToString(stringstream & ss, Node * node, int x, vector<int> & y)
			{
				static string link = "____";
				string c = String::Format("%d:%d", node->height, node->content);
				ss << c;
				x += c.length();

				if (node->right != nullptr) {
					// Record current x coordinate,
					// so it can be used to draw '|'
					y.push_back(x);
				}

				if (node->left != nullptr) {
					ss << link;
					ToString(ss, node->left, x + link.length(), y);
				}

				if (node->right != nullptr) {
					ss << endl;

					for (size_t i = 0; i < y.size(); i++) {
						int len = i == 0 ? y[i] : y[i] - y[i - 1];
						string blank(len - 1, ' ');
						ss << blank << '|';
					}

					ss << link;

					// The right child is ready to print
					// Remove its coordinate because it is not needed any more
					y.pop_back();

					ToString(ss, node->right, x + link.length(), y);
				}

				return ss;
			}

			void Print(void)
			{
				stringstream ss;
				vector<int> y;
				ToString(ss, this, 0, y);
				ss << endl;
				cout << ss.str();
			}

		} * root;

		//        y               x
		//       / \             / \
		//      x       <====       y
		//     / \                 / \
		//        z               z
		//
		// Rotate at x
		Node * LeftRotate(Node * node)
		{
			if (node == nullptr) return nullptr;
			Node * y = node->right;
			if (y == nullptr) return nullptr;

			node->right = y->left;
			if (y->left != nullptr) y->left->parent = node;

			y->parent = node->parent;
			if (node->parent == nullptr) {
				this->root = y;
			} else {
				if (node == node->parent->left) node->parent->left = y;
				else node->parent->right = y;
			}

			y->left = node;
			node->parent = y;
			return y;
		}

		//        x               y
		//       / \             / \
		//      y       ====>       x
		//     / \                 / \
		//        z               z
		//
		// Rotate at x
		Node * RightRotate(Node * node)
		{
			if (node == nullptr) return nullptr;
			Node * y = node->left;
			if (y == nullptr) return nullptr;

			node->left = y->right;
			if (y->right != nullptr) y->right->parent = node;

			y->parent = node->parent;
			if (node->parent == nullptr) {
				this->root = y;
			} else {
				if (node == node->parent->left) node->parent->left = y;
				else node->parent->right = y;
			}

			y->right = node;
			node->parent = y;
			return y;
		}

		//        z                 x
		//       / \               / \
		//      x   y     <====       y
		//     /     \               / \
		//                          z
		// Transplant at x
		Node * LeftTransplant(Node * node)
		{
			if (node == nullptr) return nullptr;
			Node * y = node->right;
			if (y == nullptr) return nullptr;
			Node * z = y->left;
			if (z == nullptr) return nullptr;
			if (z->left != nullptr || z->right != nullptr) return nullptr;

			RightRotate(y);
			//               x
			//              / \
			//                 z
			//                  \
			//                   y
			//                    \
			//
			LeftRotate(node);
			//               z
			//              / \
			//             x   y
			//            /     \
			//
			return z;
		}

		//        x                 z
		//       / \               / \
		//      y       ====>     y   x
		//     / \               /     \
		//        z
		// Transplant at x
		Node * RightTransplant(Node * node)
		{
			if (node == nullptr) return nullptr;
			Node * y = node->left;
			if (y == nullptr) return nullptr;
			Node * z = y->right;
			if (z == nullptr) return nullptr;
			if (z->left != nullptr || z->right != nullptr) return nullptr;

			LeftRotate(y);
			//          x
			//         / \
			//        z
			//       /
			//      y
			//     /
			//
			RightRotate(node);
			//          z
			//         / \
			//        y   x
			//       /     \
			//
			return z;
		}

		// Case 1
		//        ( )
		//        / \
		//     N(h) ( )
		//     / \  / \
		//
		// Case 2
		//     ( )
		//     / \
		//   ( ) N(h)
		//   / \ / \
		//
		// The subtree at node is a valid AVL tree.
		// Need to fix the height of node's ancestors and siblings.
		void InsertFix(Node * node)
		{
			if (node == nullptr) return;
			while (node->parent != nullptr) {
				Node * parent = node->parent;
				if (parent->height == node->height + 1) {
					//       P(h+1)       P(h+1)
					//       /   \        /   \
					//     N(h)  (h)    (h)   N(h)
					//     / \   / \    / \   / \
					//
					break;
				}
				
				// Now parent->height == node->height

				if (node == parent->left) {
					if (parent->right == nullptr) {
						if (parent->height == 1) {
							//       P(1)
							//       /
							//     N(1)
							//
							if (parent->parent == nullptr) {
								parent->height++;
								break;
							}

							if (parent == parent->parent->right) {
								//     (2)
								//     / \
								//       P(1)
								//       /
								//     N(1)
								//
								RightRotate(parent);
								//     (2)
								//     / \
								//       N(1)
								//         \
								//         P(1)
								//
								node->height++;
								//     (2)
								//     / \
								//       N(2)
								//         \
								//         P(1)
								//
								continue;
							} else {
								//         (2)
								//         / \
								//       P(1)
								//       /
								//     N(1)
								//
								parent->height++;
								node = parent;
								//         (2)
								//         / \
								//       N(2)
								//       /
								//     (1)
								//
								continue;
							}
						}

						//       P(2)
						//       /
						//     N(2)
						//     / \
						//
						if (node->left == nullptr) {
							//       P(2)
							//       /
							//     N(2)
							//       \
							//       (1)
							LeftRotate(node);
							//       P(2)
							//       /
							//     (1)
							//     /
							//   N(2)
							node->height--;
							node = node->parent;
							node->height++;
							//       P(2)
							//       /
							//     N(2)
							//     /
							//   (1)
						}

						if (node->right == nullptr) {
							//       P(2)
							//       /
							//     N(2)
							//     /
							//   (1)
							RightRotate(parent);
							//     N(2)
							//     /  \
							//   (1)  P(2)
							parent->height = node->height - 1;
							//     N(2)
							//     /  \
							//   (1)  P(1)								
							break;
						} else {
							//       P(2)
							//       /
							//     N(2)
							//     /  \
							//   (1)  (1)
							RightRotate(parent);
							//     N(2)
							//     /  \
							//   (1)  P(2)
							//        /
							//      (1)
							node->height++;
							//     N(3)
							//     /  \
							//   (1)  P(2)
							//        /
							//      (1)
							continue;
						}
					} else if (parent->right != nullptr) {
						if (parent->right->height == node->height - 1) {
							//       P(h)
							//       /   \
							//     N(h) (h-1)
							//     / \   / \
							//
							if (parent->parent == nullptr) {
								parent->height++;
								break;
							}

							if (parent == parent->parent->left) {
								//         ( )
								//         /
								//       P(h)
								//       /   \
								//     N(h) (h-1)
								//     / \   / \
								//
								parent->height++;
								node = parent;
								//         ( )
								//         /
								//       N(h+1)
								//       /   \
								//     (h)  (h-1)
								//     / \   / \
								//
								continue;
							} else {
								//      ( )
								//        \
								//       P(h)
								//       /   \
								//     N(h) (h-1)
								//     / \   / \
								//
								RightRotate(parent);
								//      ( )
								//        \
								//       N(h)
								//       /   \
								//           P(h)
								//           / \
								//             (h-1)
								node->height++;
								//      ( )
								//        \
								//       N(h+1)
								//       /   \
								//           P(h)
								//           / \
								//             (h-1)
								continue;
							}
						}

						// Now parent->right->height == node->height - 2

						//       P(h)              P(h)              P(h)
						//       /   \            /    \            /    \
						//     N(h) (h-2)       N(h)   (h-2)      N(h)   (h-2)
						//     /     / \       /  \     / \      /  \     /  \
						//                  (h-1)(h-2)        (h-1)(h-1) 
						//
						RightRotate(parent);
						//       N(h)             N(h)                N(h)
						//       /   \            /   \               /   \
						//          P(h)       (h-1)  P(h)         (h-1)  P(h)
						//           / \             /   \               /    \
						//            (h-2)       (h-2)  (h-2)         (h-1) (h-2)
						//
						if (parent->left != nullptr && parent->height == parent->left->height + 1) {
							node = parent;
							continue;
						} else {
							parent->height--;
							break;
						}
						//       N(h)             N(h)                  (h)
						//       /   \            /   \               /   \
						//          P(h-1)     (h-1) P(h-1)         (h-1) N(h)
						//           / \             /   \               /    \
						//            (h-2)       (h-2)  (h-2)         (h-1) (h-2)
						//							
					}
				} else if (node == parent->right) {
					if (parent->left == nullptr) {
						if (parent->height == 1) {
							//       P(1)
							//         \
							//        N(1)
							//
							if (parent->parent == nullptr) {
								parent->height++;
								break;
							}

							if (parent == parent->parent->left) {
								//     (2)
								//     / \
								//   P(1)
								//     \
								//     N(1)
								//
								LeftRotate(parent);
								//     (2)
								//     / \
								//   N(1)
								//   /
								// P(1)
								//
								node->height++;
								//     (2)
								//     / \
								//   N(2)
								//   /
								// P(1)
								//
								continue;
							} else {
								//    (2)
								//    / \
								//      P(1)
								//        \
								//        N(1)
								//
								parent->height++;
								node = parent;
								//    (2)
								//    / \
								//      N(2)
								//        \
								//        (1)
								//
								continue;
							}
						}

						//       P(2)
						//          \
						//          N(2)
						//           / \
						//
						if (node->right == nullptr) {
							//       P(2)
							//          \
							//          N(2)
							//           /
							//         (1)
							RightRotate(node);
							//       P(2)
							//          \
							//          (1)
							//            \
							//           N(2)
							node->height--;
							node = node->parent;
							node->height++;
							//       P(2)
							//          \
							//          N(2)
							//            \
							//            (1)
						}

						if (node->left == nullptr) {
							//       P(2)
							//          \
							//          N(2)
							//            \
							//            (1)
							LeftRotate(parent);
							//       N(2)
							//       /   \
							//     P(2)  (1)
							parent->height = node->height - 1;
							//       N(2)
							//       /   \
							//     P(1)  (1)
							break;
						} else {
							//       P(2)
							//          \
							//          N(2)
							//          /  \
							//         (1) (1)
							LeftRotate(parent);
							//       N(2)
							//       /   \
							//     P(2)  (1)
							//        \
							//        (1)
							node->height++;
							//       N(3)
							//       /   \
							//     P(2)  (1)
							//        \
							//        (1)
							continue;
						}
					} else if (parent->left != nullptr) {
						if (parent->left->height == node->height - 1) {
							//       P(h)
							//       /   \
							//    (h-1) N(h)
							//     / \   / \
							//
							if (parent->parent == nullptr) {
								parent->height++;
								break;
							}

							if (parent == parent->parent->right) {
								//     ( )
								//       \
								//       P(h)
								//       /   \
								//    (h-1) N(h)
								//     / \   / \
								//
								parent->height++;
								node = parent;
								//     ( )
								//       \
								//       N(h+1)
								//       /   \
								//    (h-1)  (h)
								//     / \   / \
								//
								continue;
							} else {
								//         ( )
								//         /
								//       P(h)
								//       /   \
								//    (h-1) N(h)
								//     / \   / \
								//
								LeftRotate(parent);
								//         ( )
								//         /
								//       N(h)
								//       /   \
								//     P(h)
								//     / \
								//  (h-1)
								node->height++;
								//         ( )
								//         /
								//       N(h+1)
								//       /   \
								//     P(h)
								//     / \
								//  (h-1)
								continue;
							}
						}

						// Now parent->left->height == node->height - 2
						
						//		 P(h)              P(h)              P(h)
						//       /   \            /    \            /    \
						//    (h-2)  N(h)      (h-2)   N(h)      (h-2)   N(h)
						//     / \     \       /  \     / \      /  \     /  \
						//                           (h-2)(h-1)        (h-1) (h-1)
						//
						LeftRotate(parent);
						//       N(h)             N(h)                N(h)
						//       /   \            /   \               /   \
						//     P(h)            P(h)  (h-1)          P(h) (h-1)
						//     / \             /   \               /    \
						//  (h-2)           (h-2)  (h-2)         (h-2) (h-1)
						//
						if (parent->right != nullptr && parent->height == parent->right->height + 1) {
							node = parent;
							continue;
						} else {
							parent->height--;
							break;
						}
						//       N(h)             N(h)                 (h)
						//       /   \            /   \               /   \
						//    P(h-1)          P(h-1) (h-1)           N(h) (h-1)
						//     / \             /   \               /    \
						//  (h-2)           (h-2)  (h-2)         (h-2) (h-1)
						//
					}
				}
			}
		}

	public:

		AVLTree(void) : root(nullptr) {}

		~AVLTree()
		{ 
			if (this->root != nullptr) {
				Node::Empty(this->root);
				delete this->root;
				this->root = nullptr;
			}
		}

		void Insert(const T & content)
		{
			Node * newNode = new Node(content);

			if (this->root == nullptr) {
				// The new node becomes the root.
				this->root = newNode;
				return;
			}

			Node * parent = this->root;
			Node * current = this->root;
			while (current != nullptr) {
				parent = current;
				if (newNode->content < current->content) current = current->left;
				else current = current->right;
			}

			newNode->parent = parent;
			if (newNode->content < parent->content) {
				parent->left = newNode;				
			} else {
				parent->right = newNode;
			}

			InsertFix(newNode);
		}

		bool Verify(void)
		{
			return Node::Verify(this->root);
		}

		void Print(void)
		{
			if (this->root != nullptr) this->root->Print();
		}
	};
}
