#pragma once

#include <iostream>
#include <stdarg.h>
#include <string>

using namespace std;

namespace Test {
	enum LogLevel {
		Error,
		Warning,
		Information,
		Verbose
	};

	class Log {
	private:
		static const size_t MaxLength = 1024;
		ostream & _os;
		LogLevel _level;
	public:
		__declspec(dllexport) Log(ostream & os = cout, LogLevel level = LogLevel::Error) : _os(os), _level(level) {}
		__declspec(dllexport) ~Log() {}

		__declspec(dllexport) void WriteError(const char * format, ...);
		__declspec(dllexport) void WriteWarning(const char * format, ...);
		__declspec(dllexport) void WriteInformation(const char * format, ...);
		__declspec(dllexport) void WriteVerbose(const char * format, ...);

		template<class T> __declspec(dllexport) void Print(T a[], int n, const char * format = "%d", const char * sep = ", ");
	};

	template<class T> void Log::Print(T a[], int n, const char * format, const char * sep)
	{
		WriteInformation("[");
		for (int i = 0; i < n; i++) {
			if (i != 0) WriteInformation(sep);
			WriteInformation(format, a[i]);
		}
		WriteInformation("]\n");
	}
}

