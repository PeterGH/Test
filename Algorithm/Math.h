#pragma once
#include <string>
using namespace std;
namespace Test {
	class Math {
	public:
		Math();
		~Math();

		__declspec(dllexport) static unsigned long long ExcelDecode(const string & input);
		__declspec(dllexport) static string ExcelEncode(unsigned long long input);
	};
}

