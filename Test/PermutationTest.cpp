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
		for_each(all.begin(), all.end(), [&](vector<int> & v){
			string s = Test::String::Join(v, ":");
			Logger().WriteInformation("%s\n", s.c_str());
			vector<string>::iterator it = find(freq2.begin(), freq2.end(), s);
			ASSERT2(it == freq2.end(), Test::String::Format("%s already exists", s.c_str()));
			freq2.push_back(s);
		});

		ASSERT1(freq.size() == freq2.size());
		for_each(freq.begin(), freq.end(), [&](string & s){
			vector<string>::iterator it = find(freq2.begin(), freq2.end(), s);
			ASSERT2(it != freq2.end(), Test::String::Format("%s is not found in freq2", s.c_str()));
		});
		for_each(freq2.begin(), freq2.end(), [&](string & s){
			vector<string>::iterator it = find(freq.begin(), freq.end(), s);
			ASSERT2(it != freq.end(), Test::String::Format("%s is not found in freq", s.c_str()));
		});
	});
}