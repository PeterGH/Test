#include "String.h"

namespace Test {

	string String::Format(const char * format, ...)
	{
		char buffer[MaxLength];
		va_list args;
		va_start(args, format);
		vsprintf_s(buffer, format, args);
		va_end(args);
		return string(buffer);
	}

	wstring String::Format(const wchar_t * format, ...)
	{
		wchar_t buffer[MaxLength];
		va_list args;
		va_start(args, format);
		vswprintf_s(buffer, format, args);
		va_end(args);
		return wstring(buffer);
	}

	int String::RemoveDuplicateChars(char * input, int length)
	{
		if (input == nullptr) return -1;
		if (length <= 0) return length;
		bitset<256> mask;

		// Using i to point to the last position of a non-dup char that has been checked.
		// Next non-dup char should be copied to the position i+1.
		// 0 | 1 | ... | i | ... | j | ... | n-1
		// ~~~~~~~~~~~~~~~~      ~~~~~~~~~~~~~~
		// Non-dup chars         chars to check

		int i = -1;
		for (int j = 0; j < length; j++) {
			if ('\0' == input[j]) break;
			// Should look at bit input[j] of mark			
			if (!mask.test(input[j])) {
				// The bit is zero, and it means input[j] is not a dup.
				// Set the bit.
				mask.set(input[j]);
				if (1 < (j - i)) {
					// Have skipped some dups
					// Move current non-dup char to the front.
					input[++i] = input[j];
				} else {
					// Have not skipped any dups.
					// Hop i with j.
					i++;
				}
			}
		}

		input[++i] = '\0';
		// Now i equals to the new length.
		return i;
	}

	// http://leetcode.com/2011/09/regular-expression-matching.html
	bool String::IsMatch(char * input, char * pattern)
	{
		if (input == nullptr || pattern == nullptr) return false;

		while (*pattern == '*') pattern++;

		if (*input == '\0' && *pattern == '\0') return true;

		if (*input == '\0' || *pattern == '\0') return false;

		if (*input != *pattern && *pattern != '.') {
			// input    a#######
			// pattern  b####
			if (*(pattern+1) != '*') return false;

			// input    a#######
			// pattern  b***####
			return IsMatch(input, pattern + 2);
		} else {
			// input    a#######
			// pattern  a####
			//          .####
			if (*(pattern+1) != '*') return IsMatch(++input, ++pattern);

			// input    a#######
			// pattern  a***###
			//          .***###
			while (*input == *pattern || (*pattern == '.' && *input != '\0')) {
				if (IsMatch(input++, pattern+2)) return true;
			}

			return IsMatch(input, pattern+2);
		}
	}

	bool String::IsMatch2(char * input, char * pattern)
	{
		if (input == nullptr || pattern == nullptr) return false;

		while (*pattern == '*') {
			// Ignore leading '*'
			pattern++;
		}

		while ((*input == *pattern || *pattern == '.') && *input != '\0' && *pattern != '\0' && *(pattern+1) != '*') {
			// input    a#######
			// pattern  a####
			//          .####
			input++;
			pattern++;
		}

		if (*input == '\0' && *pattern == '\0') {
			// input and pattern match
			return true;
		}

		if (*pattern == '\0') {
			// input has more characters unmatched
			return false;
		}

		if (*input == '\0') {
			// pattern has more characters. Need to check if they are '*'
			while (*pattern == '*') pattern++;
			if (*pattern != '\0') return false;
			else return true;
		}

		if (*(pattern+1) != '*') {
			// input    a#######
			// pattern  b####
			return false;
		}

		// Now *(pattern+1) == '*'

		if (*input != *pattern && *pattern != '.') {
			// input    a#######
			// pattern  b*###
			return IsMatch2(input, pattern+2);
		}

		// input    a#######
		// pattern  a*###
		//          .*###
		while (*input != '\0' && (*input == *pattern || *pattern == '.')) {
			if (IsMatch2(input, pattern+2)) return true;
			input++;
		}

		// input	'\0'
		// input    b#######
		// pattern  a*###
		return IsMatch2(input, pattern+2);
	}

	void String::LongestSubStringWithUniqueChars(const string & input, int & index, int & length)
	{
		index = 0;
		length = 0;

		bitset<256> visited;
		int i = 0;
		int j = 0;

		while ((unsigned int)j < input.length()) {
			if (visited[input[j]] == true) {
				if (j - i > length) {
					index = i;
					length = j - i;
				}

				while (input[i] != input[j]) {
					visited[input[i]] = false;
					i++;
				}

				i++;
			} else {
				visited[input[j]] = true;
			}

			j++;
		}

		if (j - i > length) {
			index = i;
			length = j - i;
		}
	}

	// http://leetcode.com/2010/11/finding-minimum-window-in-s-which.html
	// Find the shortest substring containing all the characters in a given set
	// Assuming the given set does not contain duplicate characters
	void String::ShortestSubStringContainingGivenChars(const string & chars, const string & input, int & index, int & length)
	{
		index = -1;
		length = input.length();
		queue<int> indices;
		set<char> found;
		for (unsigned int i = 0; i < input.length(); i++) {
			if (chars.find(input[i]) != string::npos) {
				while (!indices.empty() && input[indices.front()] == input[i]) {
					// no need to track the indices if the oldest chars are the same as current one
					indices.pop();
				}

				indices.push(i);

				if (found.find(input[i]) == found.end()) {
					found.insert(input[i]);
					if (found.size() == chars.length()) {
						// found all chars
						int l = indices.back() - indices.front() + 1;
						if (l < length) {
							// Update if the current one is shorter
							index = indices.front();
							length = l;
						}

						// erase the oldest char in order to start next search
						found.erase(input[indices.front()]);
						indices.pop();
					}
				}
			}
		}

		if (index == -1) length = 0;
	}

	// http://leetcode.com/2010/11/microsoft-string-replacement-problem.html
	// Replace a pattern with a shorter string in place.
	// Continous occurrences of the pattern should be replaced with one shorter string.
	void String::ReplaceWithShorterString(char * input, const char * pattern, const char * shorter)
	{
		if (input == nullptr || pattern == nullptr || shorter == nullptr
			|| *input == '\0' || pattern == '\0' || shorter == '\0')
			return;

		char * i = input; // Next insert position
		char * j = input; // Next check position

		const char * s = shorter;
		const char * p = pattern;

		while (*j != '\0') {
			bool found = false;
			while (*j == *p) {
				char * k = j;
				while (*k != '\0' && *p != '\0' && *k == *p) {
					// Do not use *k++ == *p++ in the while condition statement,
					// because k and p will advance even if *k and *p are different.
					k++;
					p++;
				}
				if (*p == '\0') {
					// Found one pattern, skip it and
					// check for next continous pattern
					found = true;
					j = k;
					p = pattern;
				} else {
					// Input is done or not match
					p = pattern;
					break;
				}
			}

			if (found) {
				while (*s != '\0') *i++ = *s++;
				s = shorter;
			}

			if (*j != '\0') {
				// j may reach the end if the input ends with the pattern
				*i++ = *j++;
			}
		}

		*i = '\0';
	}

	// input is a sentence of words separated by spaces
	// Reverse the words in place
	void String::ReverseWords(string & input)
	{
		int len = input.length();
		int i = 0;
		while (i < len && input[i] == ' ') i++;
		if (i == len) {
			input.clear();
			return;
		}
		while (i < len) {
			int j = input.find_first_of(" ", i);
			if (j == string::npos) j = len;
			input.insert(len, input, i, j - i);
			input.insert(len, 1, ' ');
			while (j < len && input[j] == ' ') j++;
			i = j;
		}
		input = input.substr(i+1);
	}

	const char * String::StrStr(const char * input1, const char * input2)
	{
		if (input1 == nullptr || input2 == nullptr || *input1 == '\0' || * input2 == '\0') return nullptr;

		const char * q = input1;
		const char * p = input2;
		while (*(q+1) != '\0' && *(p+1) != '\0') {
			q++;
			p++;
		}
		if (*(q+1) == '\0' && *(p+1) != '\0') {
			// input2 is longer than input1
			return nullptr;
		}

		// now input1 is not shorter than input2
		// set p to the beginning of input1
		p = input1;
		const char * s = input2;

		// Hop p and q at same step until q reaches the end of input1
		while (*q != '\0') {
			if (*p == *s) {
				const char * r = p;
				while (*s != '\0' && *r == *s) {
					r++;
					s++;
				}
				if (*s == '\0') {
					// match;
					return p;
				} else {
					// reset s for next match
					s = input2;
				}
			}
			p++;
			q++;
		}
		return nullptr;
	}

	// Given a input string, break it by inserting spaces so that each word is in a given dictionary.
	vector<string> String::BreakWord(string input, unordered_set<string> & dictionary)
	{
		function<void(string, unordered_set<string> &, string, vector<string> &)>
		breakWord = [&](
			string s,
			unordered_set<string> & dict,
			string sentence,
			vector<string> & results)
		{
			size_t len = s.length();
			for_each (dict.begin(), dict.end(), [&] (string w) {
				size_t wlen = w.length();
				if (len >= wlen) {
					bool match = true;
					for (size_t i = 0; i < wlen; i++) {
						if (s[i] != w[i]) {
							match = false;
							break;
						}
					}
					if (match) {
						string sen(sentence);
						if (sen.length() > 0) {
							sen.append(1, ' ');
						}
						sen.append(s.substr(0, wlen));
						if (len == wlen) {
							results.push_back(sen);
						} else {
							breakWord(s.substr(wlen), dict, sen, results);
						}
					}
				}
			});
		};

		vector<string> sentences;
		breakWord(input, dictionary, string(), sentences);
		return sentences;
	}

	#pragma warning( disable : 4503 )
	// Given a input string, break it by inserting spaces so that each word is in a given dictionary.
	vector<string> String::BreakWord2(string input, unordered_set<string> & dictionary)
	{
		function<void(string &, size_t, unordered_set<string> &, map<size_t, vector<string>> &)>
		breakWord = [&](
			string & s,
			size_t index,
			unordered_set<string> & dict,
			map<size_t, vector<string>> & results)
		{
			if (results.find(index) == results.end()) {
				results[index] = vector<string> { };
			}
			size_t len = s.length() - index;
			for_each (dict.begin(), dict.end(), [&] (string w) {
				size_t wlen = w.length();
				if (len >= wlen) {
					bool match = true;
					for (size_t i = 0; i < wlen; i++) {
						if (s[index + i] != w[i]) {
							match = false;
							break;
						}
					}
					if (match) {
						size_t wi = index + wlen;
						if (wi == s.length()) {
							results[index].push_back(w);
						} else {
							if (results.find(wi) == results.end()) {
								breakWord(s, wi, dict, results);
							}
							for_each (results[wi].begin(), results[wi].end(), [&](string r){
								string rs(w);
								rs.append(1, ' ');
								rs.append(r);
								results[index].push_back(rs);
							});
						}
					}
				}
			});
		};

		map<size_t, vector<string>> sentences;
		breakWord(input, 0, dictionary, sentences);
		return sentences[0];
	}

	bool String::BreakWord3(string input, unordered_set<string> & dictionary)
	{
		function<void(string &, size_t, unordered_set<string> &, map<size_t, bool> &)>
		breakWord = [&](
			string & s,
			size_t index,
			unordered_set<string> & dict,
			map<size_t, bool> & results)
		{
			if (results.find(index) == results.end()) {
				results[index] = false;
			}
			size_t len = s.length() - index;
			for_each (dict.begin(), dict.end(), [&] (string w) {
				size_t wlen = w.length();
				if (len >= wlen) {
					bool match = true;
					for (size_t i = 0; i < wlen; i++) {
						if (s[index + i] != w[i]) {
							match = false;
							break;
						}
					}
					if (match) {
						size_t wi = index + wlen;
						if (wi == s.length()) {
							results[index] = true;
							return;
						} else {
							if (results.find(wi) == results.end()) {
								breakWord(s, wi, dict, results);
							}
							if (results[wi]) {
								results[index] = true;
								return;
							}
						}
					}
				}
			});
		};

		map<size_t, bool> sentences;
		breakWord(input, 0, dictionary, sentences);
		return sentences[0];
	}

	// Find the length of shortest transformation sequence from a start string to a end string, such that
	// 1. only one character can be changed at each step
	// 2. each intermediate word must exist in a dictionary
	// Notes:
	// 1. all words are in the lower case
	// 2. start and end may not be in the dictionary
	int String::WordLadder(const string & start, const string & end, const unordered_set<string> & dictionary)
	{
		if (start.length() == 0 || end.length() == 0 || dictionary.size() == 0) return 0;
		unordered_set<string> dict;
		dict.insert(dictionary.begin(), dictionary.end());
		if (dict.find(start) == dict.end()) dict.insert(start);
		if (dict.find(end) == dict.end()) dict.insert(end);

		map<string, vector<string>> graph;
		for_each (dict.begin(), dict.end(), [&](string word){
			graph[word] = vector<string> { };
		});

		for_each (dict.begin(), dict.end(), [&](string word){
			int wordLen = word.length();
			for (map<string, vector<string>>::iterator it = graph.begin(); it != graph.end(); it++){
				if (wordLen == it->first.length()) {
					int diff = 0;
					for (int i = 0; i < wordLen; i++) {
						if (word[i] != it->first[i]) diff++;
						if (diff > 1) break;
					}
					if (diff == 1) {
						it->second.push_back(word);
					}
				}
			}
		});

		bool found = false;
		unordered_set<string> visited;
		queue<string> q[2];
		int step = 0;
		q[0].push(start);
		visited.insert(start);
		while (!q[0].empty() || !q[1].empty()) {
			queue<string> & current = q[step & 0x1];
			queue<string> & next = q[(step + 1) & 0x1];
			while (!current.empty()) {
				string word = current.front();
				current.pop();
				for (size_t i = 0; i <  graph[word].size(); i++){
					if (graph[word][i] == end) {
						found = true;
						break;
					}
					if (visited.find(graph[word][i]) == visited.end()){
						visited.insert(graph[word][i]);
						next.push(graph[word][i]);
					}
				}

				if (found) {
					return step + 2;
				}
			}

			step++;
		}
		return 0;
	}

	// Find the length of shortest transformation sequence from a start string to a end string, such that
	// 1. only one character can be changed at each step
	// 2. each intermediate word must exist in a dictionary
	// Notes:
	// 1. all words are in the lower case
	// 2. start and end may not be in the dictionary
	int String::WordLadder2(const string & start, const string & end, const unordered_set<string> & dictionary)
	{
		if (start.length() == 0 || end.length() == 0 || dictionary.size() == 0) return 0;
		unordered_set<string> dict;
		dict.insert(dictionary.begin(), dictionary.end());

		auto diff1 = [&](const string & first, const string & second)->bool {
			if (first.size() != second.size()) return false;
			int diff = 0;
			for (size_t i = 0; i < first.length(); i++) {
				if (first[i] != second[i]) diff++;
				if (diff > 1) return false;
			}
			return diff == 1;
		};

		vector<string> q[2];
		int step = 0;
		q[0].push_back(start);
		while (!q[0].empty() || !q[1].empty()) {
			vector<string> & current = q[step & 0x1];
			vector<string> & next = q[(step + 1) & 0x1];
			while (!current.empty()) {
				string word = current.front();
				current.erase(current.begin());
				for (unordered_set<string>::iterator it = dict.begin(); it != dict.end(); it++){
					if (diff1(word, *it)) {
						if (diff1(*it, end)) {
							return step + 3;
						} else {
							next.push_back(*it);
						}
					}
				}
			}
			for_each (next.begin(), next.end(), [&](string & s){
				dict.erase(s);
			});
			step++;
		}
		return 0;
	}

	// Find the length of shortest transformation sequence from a start string to a end string, such that
	// 1. only one character can be changed at each step
	// 2. each intermediate word must exist in a dictionary
	// Notes:
	// 1. all words are in the lower case
	// 2. start and end may not be in the dictionary
	int String::WordLadder3(const string & start, const string & end, const unordered_set<string> & dictionary)
	{
		if (start.length() == 0 || end.length() == 0 || dictionary.size() == 0) return 0;

		unordered_set<string> visited;
		queue<string> q[2];
		int step = 0;
		q[0].push(start);
		visited.insert(start);
		while (!q[0].empty() || !q[1].empty()) {
			queue<string> & current = q[step & 0x1];
			queue<string> & next = q[(step + 1) & 0x1];
			while (!current.empty()) {
				string word = current.front();
				current.pop();
				int wordLen = word.size();
				string temp;
				for (int i = 0; i < wordLen; i++) {
					temp = word;
					for (char j = 'a'; j <= 'z'; j++) {
						temp[i] = j;
						if (temp == end) {
							return step + 2;
						}
						if (dictionary.find(temp) != dictionary.end() && visited.find(temp) == visited.end()) {
							visited.insert(temp);
							next.push(temp);
						}
					}
				}
			}
			step++;
		}
		return 0;
	}

	// Find all shortest transformation sequences from a start string to a end string, such that
	// 1. only one character can be changed at each step
	// 2. each intermediate word must exist in a dictionary
	// Notes:
	// 1. all words are in the lower case
	// 2. start and end may not be in the dictionary
	vector<vector<string>> String::WordLadders(const string & start, const string & end, const unordered_set<string> & dictionary)
	{
		vector<vector<string>> ladders = { };
		if (start.length() == 0 || end.length() == 0 || dictionary.size() == 0) return ladders;

		unordered_map<string, vector<vector<string>>> path;
		unordered_map<string, int> level;
		queue<string> q[2];
		int step = 0;
		bool stop = false;
		q[0].push(start);
		level[start] = step;
		path[start] = vector<vector<string>> { };
		path[start].push_back(vector<string> { start });
		while (!q[0].empty() || !q[1].empty()) {
			queue<string> & current = q[step & 0x1];
			queue<string> & next = q[(step + 1) & 0x1];
			while (!current.empty()) {
				string word = current.front();
				current.pop();
				int wordLen = word.size();
				string temp;
				for (int i = 0; i < wordLen; i++) {
					temp = word;
					for (char j = 'a'; j <= 'z'; j++) {
						temp[i] = j;
						if (temp == end) {
							for_each(path[word].begin(), path[word].end(), [&](vector<string> & p){
								vector<string> r(p);
								r.push_back(temp);
								ladders.push_back(r);
							});
							stop = true;
						} else if (dictionary.find(temp) != dictionary.end()) {
							if (level.find(temp) == level.end()) {
								level[temp] = step + 1;
								next.push(temp);
								path[temp] = vector<vector<string>> { };
							}
							if (level[temp] > step) {
								for_each(path[word].begin(), path[word].end(), [&](vector<string> & p){
									vector<string> r(p);
									r.push_back(temp);
									path[temp].push_back(r);
								});
							}
						}
					}
				}
			}
			if (stop) break;
			step++;
		}
		return ladders;
	}

	// Find all subsequences of input string that match a pattern.
	// Return the total count.
	int String::MatchSubsequence(const string & input, const string & pattern)
	{
		if (input.length() < pattern.length() || pattern.length() == 0) return 0;
		if (input.length() == pattern.length()) {
			if (input == pattern) return 1;
			else return 0;
		}
		int count = 0;
		for (size_t i = 0; i <= input.length() - pattern.length(); i++) {
			if (input[i] == pattern[0]) {
				if (pattern.length() == 1) count++;
				else count += MatchSubsequence(input.substr(i+1), pattern.substr(1));
			}
		}
		return count;
	}

	// Find all subsequences of input string that match a pattern.
	// Return the total count.
	int String::MatchSubsequence2(const string & input, const string & pattern)
	{
		if (input.length() < pattern.length() || pattern.length() == 0) return 0;

		map<pair<size_t, size_t>, int> count;
		function<int(size_t, size_t)>
		search = [&](size_t i, size_t j) -> int {
			if (input.length() - i == pattern.length() - j) {
				return input.substr(i) == pattern.substr(j) ? 1 : 0;
			}
			int c = 0;
			for (size_t k = i; k <= input.length() - pattern.length() + j; k++) {
				if (input[k] == pattern[j]) {
					pair<size_t, size_t> p = make_pair(k, j);
					if (count.find(p) == count.end()) {
						if (j == pattern.length() - 1) {
							count[p] = 1;
						} else {
							count[p] = search(k+1, j+1);
						}
					}
					c+= count[p];
				}
			}
			return c;
		};

		return search(0, 0);
	}
}