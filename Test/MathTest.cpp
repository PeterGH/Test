#include "MathTest.h"

void MathTest::Init(void)
{
	Add("Decode", [&](){
		auto check = [&](const string & input, unsigned long long expect) {
			Logger().WriteInformation("%s = ", input.c_str());
			unsigned long long r = Test::Math::ExcelDecode(input);
			Logger().WriteInformation("%llu\n", r);
			ASSERT1(r == expect);
		};

		check("A", 0);
		check("B", 1);
		check("C", 2);
		check("X", 23);
		check("Y", 24);
		check("Z", 25);
		check("AA", 26);
		check("AB", 27);
		check("AY", 50);
		check("AZ", 51);
		check("BA", 52);
		check("BB", 53);
		check("BZ", 77);
		check("CA", 78);
		check("ZA", 676);
		check("ZY", 700);
		check("ZZ", 701);
		check("AAA", 702);
		check("AAB", 703);
		check("AAZ", 727);
	});

	Add("Encode", [&](){
		for (unsigned long long i = 0; i < 1000; i++) {
			string code = Test::Math::ExcelEncode(i);
			unsigned long long decode = Test::Math::ExcelDecode(code);
			Logger().WriteInformation("%llu, %s, %llu\n", i, code.c_str(), decode);
			ASSERT1(decode == i);
		}
		for (unsigned int i = 0; i < 1000; i++) {
			unsigned long long n = Test::Random::Next();
			string code = Test::Math::ExcelEncode(n);
			unsigned long long decode = Test::Math::ExcelDecode(code);
			Logger().WriteInformation("%llu, %s, %llu\n", n, code.c_str(), decode);
			ASSERT1(decode == n);
		}
	});

	Add("RPN", [&](){
		auto check = [&](vector<string> & tokens, int expect) {
			Logger().WriteInformation("Expression:");
			for_each(tokens.begin(), tokens.end(), [&](string & t) {
				Logger().WriteInformation(" %s", t.c_str());
			});
			Logger().WriteInformation("\n");
			int r = Test::Math::EvalRPNExpression(tokens);
			Logger().WriteInformation("Result:     %d\n", r);
			ASSERT1(r == expect);
		};
		vector<string> t = { "2", "1", "+", "3", "*" };
		check(t, 9);
		t = { "4", "13", "5", "/", "+" };
		check(t, 6);
		t = { "-1", "-22", "+" };
		check(t, -23);
		t = { "1", "-22", "-" };
		check(t, 23);
		t = { "-2", "-3", "*" };
		check(t, 6);
		t = { "-22", "-2", "/" };
		check(t, 11);
	});

	Add("GCD", [&](){
		auto check = [&](int n0, int n1, int e) {
			int r = Test::Math::GreatestCommonDivisor<int>(n0, n1);
			Logger().WriteInformation("GCD(%d, %d) = %d\n", n0, n1, r);
			ASSERT1(r == e);
		};
		check(1, 0, 1);
		check(0, 1, 1);
		check(-1, 0, 1);
		check(1, 2, 1);
		check(2, 3, 1);
		check(2, 4, 2);
		check(3, 21, 3);
		check(42, 6, 6);
		check(56, 21, 7);
		check(57, 21, 3);
		check(77, 9, 1);
		check(1, -2, 1);
		check(-2, 3, 1);
		check(-2, -4, 2);
		check(-3, 21, 3);
		check(-42, 6, 6);
		check(-56, -21, 7);
		check(-57, -21, 3);
		check(77, -9, 1);
	});

	Add("SingleNumber", [&](){
		auto check = [&](int input[], int length, int expect){
			int r1 = Test::Math::FindSingleNumber(input, length);
			int r2 = Test::Math::FindSingleNumber2(input, length);
			Logger().WriteInformation("Single number: %d, %d\n", r1, r2);
			ASSERT1(r1 == expect);
			ASSERT1(r2 == expect);
		};
		{
			int A[] = { 0, 1, 0, 0 };
			check(A, 4, 1);
		}
		{
			int A[] = { 0xFFFFFFFF, 3, 0xFFFFFFFF, 0xFFFFFFFF };
			check(A, 4, 3);
		}
		{
			int A[] = { 1, 2, 3, 1, 2, 3, 4, 1, 2, 3 };
			check(A, 10, 4);
		}
		{
			int A[] = { 0, 1, 0, 1, 0, 1, 99 };
			check(A, 7, 99);
		}
	});

	Add("Candy", [&](){
		auto print = [&](int input[], int length){
			for (int i = 0; i < length; i++) {
				Logger().WriteInformation("  %d", input[i]);
			}
			Logger().WriteInformation("\n");
		};
		auto check = [&](int ratings[], int length, int amount[], int expect) {
			Logger().WriteInformation("Input:");
			print(ratings, length);
			int total = Test::Math::AllocateCandy(ratings, length, amount);
			Logger().WriteInformation("Candy:");
			print(amount, length);
			Logger().WriteInformation("Total:  %d\n", total);
			int total2 = Test::Math::AllocateCandy2(ratings, length, amount);
			Logger().WriteInformation("Candy:");
			print(amount, length);
			Logger().WriteInformation("Total:  %d\n", total2);
			ASSERT1(total == expect);
			ASSERT1(total2 == expect);
		};
		{
			int r[] = { 0 };
			int a[1];
			check(r, 1, a, 1);
		}
		{
			int r[] = { 0, 0 };
			int a[2];
			check(r, 2, a, 2);
		}
		{
			int r[] = { 0, 1 };
			int a[2];
			check(r, 2, a, 3);
		}
		{
			int r[] = { 1, 0 };
			int a[2];
			check(r, 2, a, 3);
		}
		{
			int r[] = { 0, 0, 0 };
			int a[3];
			check(r, 3, a, 3);
		}
		{
			int r[] = { 0, 0, 1 };
			int a[3];
			check(r, 3, a, 4);
		}
		{
			int r[] = { 0, 1, 0 };
			int a[3];
			check(r, 3, a, 4);
		}
		{
			int r[] = { 1, 0, 0 };
			int a[3];
			check(r, 3, a, 4);
		}
		{
			int r[] = { 0, 1, 1 };
			int a[3];
			check(r, 3, a, 5);
		}
		{
			int r[] = { 1, 0, 1 };
			int a[3];
			check(r, 3, a, 5);
		}
		{
			int r[] = { 1, 1, 0 };
			int a[3];
			check(r, 3, a, 5);
		}
		{
			int r[] = { 0, 1, 2 };
			int a[3];
			check(r, 3, a, 6);
		}
		{
			int r[] = { 0, 2, 1 };
			int a[3];
			check(r, 3, a, 4);
		}
		{
			int r[] = { 1, 0, 2 };
			int a[3];
			check(r, 3, a, 5);
		}
		{
			int r[] = { 1, 2, 0 };
			int a[3];
			check(r, 3, a, 4);
		}
		{
			int r[] = { 2, 0, 1 };
			int a[3];
			check(r, 3, a, 5);
		}
		{
			int r[] = { 2, 1, 0 };
			int a[3];
			check(r, 3, a, 6);
		}
		{
			int r[] = { 0, 0, 0, 0 };
			int a[4];
			check(r, 4, a, 4);
		}
		{
			int r[] = { 0, 0, 0, 1 };
			int a[4];
			check(r, 4, a, 5);
		}
		{
			int r[] = { 0, 0, 1, 0 };
			int a[4];
			check(r, 4, a, 5);
		}
		{
			int r[] = { 0, 1, 0, 0 };
			int a[4];
			check(r, 4, a, 5);
		}
		{
			int r[] = { 1, 0, 0, 0 };
			int a[4];
			check(r, 4, a, 5);
		}
		{
			int r[] = { 0, 0, 1, 1 };
			int a[4];
			check(r, 4, a, 6);
		}
		{
			int r[] = { 0, 1, 0, 1 };
			int a[4];
			check(r, 4, a, 6);
		}
		{
			int r[] = { 1, 0, 0, 1 };
			int a[4];
			check(r, 4, a, 6);
		}
		{
			int r[] = { 1, 0, 1, 0 };
			int a[4];
			check(r, 4, a, 6);
		}
		{
			int r[] = { 1, 1, 0, 0 };
			int a[4];
			check(r, 4, a, 6);
		}
		{
			int r[] = { 0, 1, 1, 1 };
			int a[4];
			check(r, 4, a, 7);
		}
		{
			int r[] = { 1, 0, 1, 1 };
			int a[4];
			check(r, 4, a, 7);
		}
		{
			int r[] = { 1, 1, 0, 1 };
			int a[4];
			check(r, 4, a, 7);
		}
		{
			int r[] = { 1, 1, 1, 0 };
			int a[4];
			check(r, 4, a, 7);
		}
		{
			int r[] = { 0, 0, 1, 2 };
			int a[4];
			check(r, 4, a, 7);
		}
		{
			int r[] = { 0, 1, 0, 2 };
			int a[4];
			check(r, 4, a, 6);
		}
		{
			int r[] = { 1, 0, 0, 2 };
			int a[4];
			check(r, 4, a, 6);
		}
		{
			int r[] = { 1, 0, 2, 0 };
			int a[4];
			check(r, 4, a, 6);
		}
		{
			int r[] = { 1, 2, 0, 0 };
			int a[4];
			check(r, 4, a, 5);
		}
		{
			int r[] = { 0, 0, 2, 1 };
			int a[4];
			check(r, 4, a, 5);
		}
		{
			int r[] = { 0, 2, 0, 1 };
			int a[4];
			check(r, 4, a, 6);
		}
		{
			int r[] = { 2, 0, 0, 1 };
			int a[4];
			check(r, 4, a, 6);
		}
		{
			int r[] = { 2, 0, 1, 0 };
			int a[4];
			check(r, 4, a, 6);
		}
		{
			int r[] = { 2, 1, 0, 0 };
			int a[4];
			check(r, 4, a, 7);
		}
		{
			int r[] = { 0, 1, 1, 2 };
			int a[4];
			check(r, 4, a, 8);
		}
		{
			int r[] = { 1, 0, 1, 2 };
			int a[4];
			check(r, 4, a, 8);
		}
		{
			int r[] = { 1, 1, 0, 2 };
			int a[4];
			check(r, 4, a, 7);
		}
		{
			int r[] = { 1, 1, 2, 0 };
			int a[4];
			check(r, 4, a, 5);
		}
		{
			int r[] = { 0, 1, 2, 1 };
			int a[4];
			check(r, 4, a, 7);
		}
		{
			int r[] = { 0, 2, 1, 1 };
			int a[4];
			check(r, 4, a, 5);
		}
		{
			int r[] = { 2, 0, 1, 1 };
			int a[4];
			check(r, 4, a, 7);
		}
		{
			int r[] = { 0, 0, 0, 0, 0 };
			int a[5];
			check(r, 5, a, 5);
		}
	});

	Add("BinaryTreeSumBranches", [&](){
		auto check = [&](Test::BinaryNode<unsigned int> * node, unsigned long long expect){
			node->Print2();
			unsigned long long sum = Test::Math::BinaryTreeSumBranches(node);
			Logger().WriteInformation("Sum %llu %s %llu\n", sum, sum == expect ? "==" : "!=", expect);
			ASSERT1(sum == expect);
		};
		{
			Test::BinaryNode<unsigned int> n1(1);
			check(&n1, 1);
		}
		{
			Test::BinaryNode<unsigned int> n1(1);
			Test::BinaryNode<unsigned int> n2(2);
			n1.left = &n2;
			check(&n1, 12);
		}
		{
			Test::BinaryNode<unsigned int> n1(1);
			Test::BinaryNode<unsigned int> n2(2);
			n1.right = &n2;
			check(&n1, 12);
		}
		{
			Test::BinaryNode<unsigned int> n1(1);
			Test::BinaryNode<unsigned int> n2(2);
			Test::BinaryNode<unsigned int> n3(3);
			n1.left = &n2;
			n1.right = &n3;
			check(&n1, 25);
		}
		{
			Test::BinaryNode<unsigned int> n1(1);
			Test::BinaryNode<unsigned int> n2(2);
			Test::BinaryNode<unsigned int> n3(3);
			Test::BinaryNode<unsigned int> n4(4);
			n1.left = &n2;
			n1.right = &n3;
			n2.left = &n4;
			check(&n1, 137);
		}
	});

	Add("BinaryTreeMaxPathSum", [&](){
		auto check = [&](Test::BinaryNode<int> * node, long long expect){
			node->Print2();
			vector<Test::BinaryNode<int> *> path;
			long long sum = Test::Math::BinaryTreeMaxPathSum(node, path);
			Logger().WriteInformation("Sum %lld %s %lld\n", sum, sum == expect ? "==" : "!=", expect);
			Logger().WriteInformation("Path:");
			for_each (path.begin(), path.end(), [&](Test::BinaryNode<int> * n){
				Logger().WriteInformation("  %d", n->content);
			});
			Logger().WriteInformation("\n");
			ASSERT1(sum == expect);
			Logger().WriteInformation("\n");
		};
		{
			Test::BinaryNode<int> n1(1);
			check(&n1, 1);
		}
		{
			Test::BinaryNode<int> n1(-1);
			check(&n1, -1);
		}
		{
			Test::BinaryNode<int> n1(1);
			Test::BinaryNode<int> n2(2);
			n1.left = &n2;
			check(&n1, 3);
		}
		{
			Test::BinaryNode<int> n1(-1);
			Test::BinaryNode<int> n2(2);
			n1.left = &n2;
			check(&n1, 2);
		}
		{
			Test::BinaryNode<int> n1(1);
			Test::BinaryNode<int> n2(-2);
			n1.left = &n2;
			check(&n1, 1);
		}
		{
			Test::BinaryNode<int> n1(-1);
			Test::BinaryNode<int> n2(-2);
			n1.left = &n2;
			check(&n1, -1);
		}
		{
			Test::BinaryNode<int> n1(1);
			Test::BinaryNode<int> n2(2);
			n1.right = &n2;
			check(&n1, 3);
		}
		{
			Test::BinaryNode<int> n1(-1);
			Test::BinaryNode<int> n2(2);
			n1.right = &n2;
			check(&n1, 2);
		}
		{
			Test::BinaryNode<int> n1(1);
			Test::BinaryNode<int> n2(-2);
			n1.right = &n2;
			check(&n1, 1);
		}
		{
			Test::BinaryNode<int> n1(-1);
			Test::BinaryNode<int> n2(-2);
			n1.right = &n2;
			check(&n1, -1);
		}
		{
			Test::BinaryNode<int> n1(1);
			Test::BinaryNode<int> n2(2);
			Test::BinaryNode<int> n3(3);
			n1.left = &n2;
			n1.right = &n3;
			check(&n1, 6);
		}
		{
			Test::BinaryNode<int> n1(-1);
			Test::BinaryNode<int> n2(2);
			Test::BinaryNode<int> n3(3);
			n1.left = &n2;
			n1.right = &n3;
			check(&n1, 4);
		}
		{
			Test::BinaryNode<int> n1(1);
			Test::BinaryNode<int> n2(-2);
			Test::BinaryNode<int> n3(3);
			n1.left = &n2;
			n1.right = &n3;
			check(&n1, 4);
		}
		{
			Test::BinaryNode<int> n1(1);
			Test::BinaryNode<int> n2(2);
			Test::BinaryNode<int> n3(-3);
			n1.left = &n2;
			n1.right = &n3;
			check(&n1, 3);
		}
		{
			Test::BinaryNode<int> n1(-2);
			Test::BinaryNode<int> n2(2);
			Test::BinaryNode<int> n3(3);
			n1.left = &n2;
			n1.right = &n3;
			check(&n1, 3);
		}
		{
			Test::BinaryNode<int> n1(-2);
			Test::BinaryNode<int> n2(3);
			Test::BinaryNode<int> n3(2);
			n1.left = &n2;
			n1.right = &n3;
			check(&n1, 3);
		}
		{
			Test::BinaryNode<int> n1(1);
			Test::BinaryNode<int> n2(-2);
			Test::BinaryNode<int> n3(-3);
			n1.left = &n2;
			n1.right = &n3;
			check(&n1, 1);
		}
		{
			Test::BinaryNode<int> n1(-4);
			Test::BinaryNode<int> n2(-2);
			Test::BinaryNode<int> n3(-3);
			n1.left = &n2;
			n1.right = &n3;
			check(&n1, -2);
		}
		{
			Test::BinaryNode<int> n1(-4);
			Test::BinaryNode<int> n2(-4);
			Test::BinaryNode<int> n3(-3);
			n1.left = &n2;
			n1.right = &n3;
			check(&n1, -3);
		}
		{
			Test::BinaryNode<int> n1(1);
			Test::BinaryNode<int> n2(2);
			Test::BinaryNode<int> n3(3);
			Test::BinaryNode<int> n4(4);
			n1.left = &n2;
			n1.right = &n3;
			n2.left = &n4;
			check(&n1, 10);
		}
		{
			Test::BinaryNode<int> n1(1);
			Test::BinaryNode<int> n2(-2);
			Test::BinaryNode<int> n3(3);
			Test::BinaryNode<int> n4(4);
			n1.left = &n2;
			n1.right = &n3;
			n2.left = &n4;
			check(&n1, 6);
		}
		{
			Test::BinaryNode<int> n1(1);
			Test::BinaryNode<int> n2(-4);
			Test::BinaryNode<int> n3(3);
			Test::BinaryNode<int> n4(4);
			n1.left = &n2;
			n1.right = &n3;
			n2.left = &n4;
			check(&n1, 4);
		}
		{
			Test::BinaryNode<int> n1(1);
			Test::BinaryNode<int> n2(2);
			Test::BinaryNode<int> n3(3);
			Test::BinaryNode<int> n4(-4);
			n1.left = &n2;
			n1.right = &n3;
			n2.left = &n4;
			check(&n1, 6);
		}
		{
			Test::BinaryNode<int> n1(1);
			Test::BinaryNode<int> n2(2);
			Test::BinaryNode<int> n3(3);
			Test::BinaryNode<int> n4(4);
			Test::BinaryNode<int> n5(3);
			n1.left = &n2;
			n1.right = &n3;
			n2.left = &n4;
			n2.right = &n5;
			check(&n1, 10);
		}
		{
			Test::BinaryNode<int> n1(1);
			Test::BinaryNode<int> n2(2);
			Test::BinaryNode<int> n3(3);
			Test::BinaryNode<int> n4(4);
			Test::BinaryNode<int> n5(5);
			n1.left = &n2;
			n1.right = &n3;
			n2.left = &n4;
			n2.right = &n5;
			check(&n1, 11);
		}
		{
			Test::BinaryNode<int> n1(1);
			Test::BinaryNode<int> n2(2);
			Test::BinaryNode<int> n3(3);
			Test::BinaryNode<int> n4(4);
			Test::BinaryNode<int> n5(5);
			Test::BinaryNode<int> n6(6);
			n1.left = &n2;
			n1.right = &n3;
			n2.left = &n4;
			n2.right = &n5;
			n3.left = &n6;
			check(&n1, 17);
		}
		{
			Test::BinaryNode<int> n1(-10);
			Test::BinaryNode<int> n2(2);
			Test::BinaryNode<int> n3(3);
			Test::BinaryNode<int> n4(4);
			Test::BinaryNode<int> n5(5);
			Test::BinaryNode<int> n6(6);
			n1.left = &n2;
			n1.right = &n3;
			n2.left = &n4;
			n2.right = &n5;
			n3.left = &n6;
			check(&n1, 11);
		}
	});

	Add("LongestConsecutiveSequence", [&](){
		auto print = [&](vector<int> & input){
			Logger().WriteInformation("Input:");
			for (size_t i = 0; i < input.size(); i++) {
				Logger().WriteInformation("  %d", input[i]);
			}
			Logger().WriteInformation("\n");
		};

		auto check = [&](vector<int> & input, int expectBegin, int expectLength) {
			int begin;
			int length;
			print(input);
			Test::Math::LongestConsecutiveSequence(input, begin, length);
			Logger().WriteInformation("  Begin:  %d %s %d\n", begin, begin == expectBegin ? "==" : "!=", expectBegin);
			Logger().WriteInformation("  Length: %d %s %d\n", length, length == expectLength ? "==" : "!=", expectLength);
			ASSERT1(begin == expectBegin);
			ASSERT1(length == expectLength);
		};
		{
			vector<int> input = { 0 };
			check(input, 0, 1);
		}
		{
			vector<int> input = { 0, 0 };
			check(input, 0, 1);
		}
		{
			vector<int> input = { 0, 1 };
			check(input, 0, 2);
		}
		{
			vector<int> input = { 1, 0 };
			check(input, 0, 2);
		}
		{
			vector<int> input = { 0, 2 };
			check(input, 0, 1);
		}
		{
			vector<int> input = { 0, 1, 2 };
			check(input, 0, 3);
		}
		{
			vector<int> input = { 0, 1, 3 };
			check(input, 0, 2);
		}
		{
			vector<int> input = { -1, 1, 2 };
			check(input, 1, 2);
		}
		{
			vector<int> input = { 0, -1, 2 };
			check(input, -1, 2);
		}
		{
			vector<int> input = { 3, 1, 2 };
			check(input, 1, 3);
		}
		{
			vector<int> input = { 0, 1, 1 };
			check(input, 0, 2);
		}
		{
			vector<int> input = { 1, 0, 1, 1 };
			check(input, 0, 2);
		}
		{
			vector<int> input = { 1, 0, 1, 0 };
			check(input, 0, 2);
		}
		{
			vector<int> input = { 1, 0, -1 };
			check(input, -1, 3);
		}
		{
			vector<int> input = { 0, 1, 2, 1 };
			check(input, 0, 3);
		}
		{
			vector<int> input = { -7, -1, 3, -9, -4, 7, -3, 2, 4, 9, 4, -9, 8, -7 ,5, -1, -7 };
			check(input, 2, 4);
		}
		{
			vector<int> input = { -6, 8, -5, 7, -9, -1, -7, -6, -9, -7, 5, 7, -1, -8, -8, -2, 0 };
			check(input, -9, 5);
		}
	});

	Add("TriangleMinPathSum", [&](){
		auto check = [&](vector<vector<int>> & triangle, int expect){
			for_each (triangle.begin(), triangle.end(), [&](vector<int> & r){
				for_each(r.begin(), r.end(), [&](int i){
					Logger().WriteInformation(" %d", i);
				});
				Logger().WriteInformation("\n");
			});
			int sum = Test::Math::TriangleMinPathSum(triangle);
			Logger().WriteInformation("Sum: %d %s %d\n", sum, sum == expect ? "==" : "!=", expect);
			ASSERT1(sum == expect);
		};
		{
			vector<vector<int>> t = { { -10 } };
			check(t, -10);
		}
		{
			vector<vector<int>> t = {
					{ -10 },
					{ 1, 2 }
			};
			check(t, -9);
		}
		{
			vector<vector<int>> t = {
					{ 2 },
					{ 3, 4 },
					{ 6, 5, 7 },
					{ 4, 1, 8, 3}
			};
			check(t, 11);
		}
	});
}