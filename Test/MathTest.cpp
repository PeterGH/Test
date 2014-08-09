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
}