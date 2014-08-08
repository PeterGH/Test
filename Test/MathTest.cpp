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
}