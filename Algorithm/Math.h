#pragma once
#include <algorithm>
#include <functional>
#include <map>
#include <memory>
#include <stack>
#include <string>
#include <unordered_map>
#include <vector>
#include "BinaryNode.h"
using namespace std;
namespace Test {
	class Math {
	public:
		Math();
		~Math();

		// Add two bit arrays, n2 = n0 + n1. Assume bit-0 is the LSB.
		__declspec(dllexport) static void AddBits(int * n0, size_t l0, int * n1, size_t l1, int * n2);

		__declspec(dllexport) static unsigned long long ExcelDecode(const string & input);
		__declspec(dllexport) static string ExcelEncode(unsigned long long input);

		// For each element input[i] compute multiplication of the other elements in input.
		__declspec(dllexport) static void ExclusiveMultiplication(const int * input, int length, long long * output);

		__declspec(dllexport) static int EvalRPNExpression(vector<string> & tokens);

		__declspec(dllexport) static int FindSingleNumber(int input[], int lenth);
		__declspec(dllexport) static int FindSingleNumber2(int input[], int lenth);

		__declspec(dllexport) static int AllocateCandy(int ratings[], int length, int amount[]);
		__declspec(dllexport) static int AllocateCandy2(int ratings[], int length, int amount[]);

		__declspec(dllexport) static unsigned long long BinaryTreeSumBranches(BinaryNode<unsigned int> * node);
		__declspec(dllexport) static long long BinaryTreeMaxPathSum(BinaryNode<int> * root, vector<BinaryNode<int> *> & path);

		// Find the elements forming the longest contiguous sequence.
		// Given [100, 4, 200, 1, 3, 2], The longest consecutive elements sequence is [1, 2, 3, 4]. Return its length: 4. 
		__declspec(dllexport) static void LongestConsecutiveSequence(vector<int> & input, int & begin, int & length);

		__declspec(dllexport) static int TriangleMinPathSum(vector<vector<int>> & triangle);

		template<class T> __declspec(dllexport) static T GreatestCommonDivisor(T n0, T n1);

		class Tree {
		public:
			//         0
			//    1          2
			//  3   4     5     6
			// 7 8 9 10 11 12 13 14
			// Given height H, the number of nodes are in [2^(H - 1), 2^H - 1]
			// The indices of nodes at height H are in [2^(H - 1) - 1, 2^H - 2]
			__declspec(dllexport) static unsigned int Parent(unsigned int i) { return (i - 1) >> 1; }
			__declspec(dllexport) static unsigned int Left(unsigned int i) { return (i << 1) + 1; }
			__declspec(dllexport) static unsigned int Right(unsigned int i) { return (i << 1) + 2; }
			// Get the height of binary tree given count of nodes
			__declspec(dllexport) static unsigned int Height(unsigned int count);
			// d-ary heap
			//                                                  0
			//                   1                              2                    ...          d
			// (d+1)                   (d+2) ... (d+d) | (2d+1) (2d+2) ... (2d+d) | (d^2+1) (d^2+2) ... (d^2+d)
			// (d^2+d+1) (d^2+d+2) ...
			// ......
			// Given height h, the number of nodes are [(d^(h-1)-1)/(d-1)+1, (d^h-1)/(d-1)]
			// The indices at height h are [(d^(h-1)-1)/(d-1), (d^h-1)/(d-1)-1]
			// Return the index of the parent of node i
			__declspec(dllexport) static unsigned int Parent(unsigned int i, unsigned int d) { return (i - 1) / d; }
			// Return the index of the j-th child of node i. j is zero based.
			__declspec(dllexport) static unsigned int Child(unsigned int i, unsigned int j, unsigned int d) { return i * d + j + 1; }
			// Get the height of d-ary tree given count of nodes
			__declspec(dllexport) static unsigned int Height(unsigned int count, unsigned int d);
		};
	};

	template<class T> T Math::GreatestCommonDivisor(T n0, T n1)
	{
		if (n0 == 0 && n1 == 0) throw invalid_argument("(0, 0) has no greatest common divisor");
		if (n0 < 0) n0 = -n0;
		if (n1 < 0) n1 = -n1;
		if (n0 == 0) return n1;
		if (n1 == 0) return n0;
		if (n1 > n0) swap(n0, n1);
		T r = n0 % n1;
		while (r != 0) {
			n0 = n1;
			n1 = r;
			r = n0 % n1;
		}
		return n1;
	}
}

