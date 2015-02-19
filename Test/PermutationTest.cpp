#include "PermutationTest.h"

void PermutationTest::Init(void)
{
	Add("Next1", [&](){
		Test::Permutation perm(4);
		int count = (int)perm.Max();
		ASSERT1(24 == count);
		
		int data[] = { 0, 1, 2, 3 };
		int output[4];
		vector<string> freq;
		for (int i = 0; i < count; i++) {
			perm.Next(data, output, 4);
			string s = Test::String::Join(output, 4, ":");
			Logger().WriteInformation("%s\n", s.c_str());
			vector<string>::iterator it = find(freq.begin(), freq.end(), s);
			ASSERT2(it == freq.end(), Test::String::Format("%s already exists", s.c_str()));
			freq.push_back(s);
		}
	}); 
	
	Add("Next2", [&](){
		Test::Permutation perm(4);
		int count = (int)perm.Max();
		ASSERT1(24 == count);

		int data[] = { 0, 1, 2, 3 };
		map<string, int> freq;
		int total = 1000000;
		for (int i = 0; i < total; i++) {
			// Keep the last output as the input to the next run.
			// This is not ideal because the frequenies have a large deviation.
			perm.Next(data, 4);
			string s = Test::String::Join(data, 4, ":");
			map<string, int>::iterator it = freq.find(s);
			if (it == freq.end()) {
				freq[s] = 1;
			} else {
				freq[s] ++;
			}
		}

		ASSERT1(freq.size() == count);
		int ave = total / count;
		// Use a larger delta.
		int delta = ave;

		for_each(freq.begin(), freq.end(), [&](pair<string, int> p){
			Logger().WriteInformation("%s\t%d\n", p.first.c_str(), p.second);
		});

		for_each(freq.begin(), freq.end(), [&](pair<string, int> p){
			ASSERT2(delta >= abs(p.second - ave), Test::String::Format("%s occurs %d times, average %d, delta %d", p.first.c_str(), p.second, ave, delta));
		});
	});

	Add("Random1", [&](){
		int data[] = { 0, 1, 2, 3 };
		map<string, int> freq;
		int total = 1000000;
		for (int i = 0; i < total; i++) {
			Test::Permutation::Random(data, 4);
			string s = Test::String::Join(data, 4, ":");
			map<string, int>::iterator it = freq.find(s);
			if (it == freq.end()) {
				freq[s] = 1;
			}
			else {
				freq[s] ++;
			}
		}

		int count = 24;
		ASSERT1(freq.size() == count);
		int ave = total / count;
		int delta = ave >> 1;

		for_each(freq.begin(), freq.end(), [&](pair<string, int> p){
			Logger().WriteInformation("%s\t%d\n", p.first.c_str(), p.second);
		});

		for_each(freq.begin(), freq.end(), [&](pair<string, int> p){
			ASSERT2(delta >= abs(p.second - ave), Test::String::Format("%s occurs %d times, average %d, delta %d", p.first.c_str(), p.second, ave, delta));
		});
	});

	Add("Random2", [&](){
		int data[] = { 0, 1, 2, 3 };
		int output[4];
		map<string, int> freq;
		int total = 1000000;
		for (int i = 0; i < total; i++) {
			Test::Permutation::Random(data, output, 4);
			string s = Test::String::Join(output, 4, ":");
			map<string, int>::iterator it = freq.find(s);
			if (it == freq.end()) {
				freq[s] = 1;
			} else {
				freq[s] ++;
			}
		}

		int count = 24;
		ASSERT1(freq.size() == count);
		int ave = total / count;
		int delta = ave >> 1;

		for_each(freq.begin(), freq.end(), [&](pair<string, int> p){
			Logger().WriteInformation("%s\t%d\n", p.first.c_str(), p.second);
		});

		for_each(freq.begin(), freq.end(), [&](pair<string, int> p){
			ASSERT2(delta >= abs(p.second - ave), Test::String::Format("%s occurs %d times, average %d, delta %d", p.first.c_str(), p.second, ave, delta));
		});
	});

	Add("All", [&](){
		Test::Permutation perm(4);
		int count = (int)perm.Max();
		ASSERT1(24 == count);

		int data[] = { 0, 1, 2, 3 };
		int output[4];
		vector<string> freq;
		Logger().WriteInformation("Permutation.Next:\n");
		for (int i = 0; i < count; i++) {
			perm.Next(data, output, 4);
			string s = Test::String::Join(output, 4, ":");
			Logger().WriteInformation("%s\n", s.c_str());
			vector<string>::iterator it = find(freq.begin(), freq.end(), s);
			ASSERT2(it == freq.end(), Test::String::Format("%s already exists", s.c_str()));
			freq.push_back(s);
		}

		vector<int> input = { 0, 1, 2, 3 };
		vector<vector<int>> all = Test::Permutation::All(input);
		vector<string> freq2;
		Logger().WriteInformation("Permutation.All:\n");
		for_each(all.begin(), all.end(), [&](vector<int> & v){
			string s = Test::String::Join(v, ":");
			Logger().WriteInformation("%s\n", s.c_str());
			vector<string>::iterator it = find(freq2.begin(), freq2.end(), s);
			ASSERT2(it == freq2.end(), Test::String::Format("%s already exists", s.c_str()));
			freq2.push_back(s);
		});

		vector<int> input2 = { 0, 1, 2, 3 };
		vector<vector<int>> unique = Test::Permutation::Unique(input2);
		vector<string> freq3;
		Logger().WriteInformation("Permutation.Unique:\n");
		for_each(unique.begin(), unique.end(), [&](vector<int> & v){
			string s = Test::String::Join(v, ":");
			Logger().WriteInformation("%s\n", s.c_str());
			vector<string>::iterator it = find(freq3.begin(), freq3.end(), s);
			ASSERT2(it == freq3.end(), Test::String::Format("%s already exists", s.c_str()));
			freq3.push_back(s);
		});

		ASSERT1(freq.size() == freq2.size());
		ASSERT1(freq.size() == freq3.size());
		for_each(freq.begin(), freq.end(), [&](string & s){
			vector<string>::iterator it = find(freq2.begin(), freq2.end(), s);
			ASSERT2(it != freq2.end(), Test::String::Format("%s is not found in freq2", s.c_str()));
			it = find(freq3.begin(), freq3.end(), s);
			ASSERT2(it != freq3.end(), Test::String::Format("%s is not found in freq3", s.c_str()));
		});
		for_each(freq2.begin(), freq2.end(), [&](string & s){
			vector<string>::iterator it = find(freq.begin(), freq.end(), s);
			ASSERT2(it != freq.end(), Test::String::Format("%s is not found in freq", s.c_str()));
		});
		for_each(freq3.begin(), freq3.end(), [&](string & s){
			vector<string>::iterator it = find(freq.begin(), freq.end(), s);
			ASSERT2(it != freq.end(), Test::String::Format("%s is not found in freq", s.c_str()));
		});
	});

	Add("Unique", [&](){
		auto check = [&](vector<int> & n) {
			Logger().WriteInformation("Permute: ");
			Logger().Print(n);
			vector<vector<int>> p = Test::Permutation::Unique(n);
			for_each(p.begin(), p.end(), [&](vector<int> & i){
				Logger().Print(i);
			});
		};
		check(vector<int> { 1, 1 });
		check(vector<int> { 1, 1, 1 });
		check(vector<int> { 1, 1, 2 });
		check(vector<int> { 1, 1, 2, 2 });
		check(vector<int> { 1, 2, 3, 1, 2, 3 });
	});

	Add("GetPermutation", [&](){
		auto fact = [&](int n)-> int {
			int m = 1;
			for (int i = 1; i <= n; i++) {
				m *= i;
			}
			return m;
		};
		auto print = [&](int n){
			for (int i = 1; i <= n; i++) {
				Logger().WriteInformation("%c", '0' + i);
			}
			Logger().WriteInformation("\n");
		};
		auto check = [&](int n){
			print(n);
			int m = fact(n);
			for (int i = 1; i <= m; i++) {
				string p = Test::Permutation::GetPermutation(n, i);
				Logger().WriteInformation("  %d\t%s\n", i, p.c_str());
			}
		};
		check(1);
		check(2);
		check(3);
		check(4);
		check(5);
		// check(6);
		// check(7);
		// check(8);
		// check(9);
	});

	Add("NextPermutation", [&](){
		auto check = [&](vector<int> & n) {
			Logger().WriteInformation("Permute: ");
			Logger().Print(n);
			vector<vector<int>> p = Test::Permutation::Unique(n);
			for_each(p.begin(), p.end(), [&](vector<int> & i){
				Logger().WriteInformation("Unique:\t");
				Logger().Print(i);
				Logger().WriteInformation("Next:\t");
				Logger().Print(n);
				bool e = Equal(i, n);
				ASSERT1(e == true);
				Test::Permutation::NextPermutation(n);
			});
		};
		check(vector<int> { 1, 1 });
		check(vector<int> { 1, 1, 1 });
		check(vector<int> { 1, 1, 2 });
		check(vector<int> { 1, 1, 2, 2 });
		check(vector<int> { 1, 1, 2, 2, 3, 3 });
	});
}