#pragma once

#include <map>
#include <set>
#include <vector>
#include "String.h"

using namespace std;

namespace Test {

	// Class to parse command line arguments
	template<class T> class Argument {
	private:
		// Indexed arguments
		vector<basic_string<T>> indexed;

		// Named arguments
		map<basic_string<T>, basic_string<T>> named;

		// Parse command line arguments
		void Parse(int argc, T * argv[]);
	public:
		// Create an Argument object with command line arguments
		Argument(int argc, T * argv[]) { Parse(argc, argv); }

		// Copy constructor
		Argument(const Argument & a) : this->indexed(a.indexed), this->named(a.named) {}

		// Destructor
		~Argument(void) {}

		// Count named arguments
		size_t CountNamedArgs(void) const { return this->named.size(); }

		// Count indexed arguments
		size_t CountIndexedArgs(void) const { return this->indexed.size(); }

		// Count total arguments
		size_t Count(void) const { return CountNamedArgs() + CountIndexedArgs(); }

		// Check if a named argument exists
		bool Has(const basic_string<T> & key);

		// Check if an indexed argument exists
		bool Has(unsigned int index) const { return index < this->indexed.size(); }

		// Get a named argument value
		const basic_string<T> & operator[](const basic_string<T> & name);

		// Get an indexed argument value
		const basic_string<T> & operator[](unsigned int index);

		// Convert all arguments into a string representation
		const basic_string<T> ToString(void);

		// Get the names of all named arguments
		const set<basic_string<T>> Keys(void);
	};

	template<class T> void Argument<T>::Parse(int argc, T * argv[])
	{
		int i = 0;
		do {
			if (argv[i][0] == T('-')) {
				basic_string<T> key = basic_string<T>(&argv[i][1]);
				if (i + 1 < argc && argv[i + 1][0] != T('-')) {
					// case: -key value					
					basic_string<T> value = basic_string<T>(argv[i + 1]);
					this->named.insert(pair<basic_string<T>, basic_string<T>>(String::ToLower(key), value));
					i += 2;
				} else {
					// case 1: -key
					// case 2: -key1 -key2
					this->named.insert(pair<basic_string<T>, basic_string<T>>(String::ToLower(key), basic_string<T>()));
					i++;
				}
			} else {
				basic_string<T> value = basic_string<T>(argv[i]);
				this->indexed.push_back(value);
				i++;
			}
		} while (i < argc);
	}

	template<class T> bool Argument<T>::Has(const basic_string<T> & key)
	{
		basic_string<T> keyl = String::ToLower(key);
		map<basic_string<T>, basic_string<T>>::iterator it = this->named.find(keyl);
		return it != this->named.end();
	}

	template<class T> const basic_string<T> & Argument<T>::operator[](const basic_string<T> & key)
	{
		basic_string<T> keyl = String::ToLower(key);
		map<basic_string<T>, basic_string<T>>::iterator it = this->named.find(keyl);
		if (it != this->named.end()) {
			return it->second;
		} else {
			throw invalid_argument(String::Format("Invalid argument name %s", String::ToString(key)));
		}
	}

	template<class T> const basic_string<T> & Argument<T>::operator[](unsigned int index)
	{
		if (index < this->indexed.size()) {
			return this->indexed[index];
		} else {
			throw invalid_argument(String::Format("Invalid argument index %d", index));
		}
	}

	template<class T> const basic_string<T> Argument<T>::ToString(void)
	{
		basic_string<T> s;
		unsigned int i = 0;
		string t;
		for (map<basic_string<T>, basic_string<T>>::iterator it = this->named.begin(); it != this->named.end(); it++) {
			t = "-";
			s.append(t.begin(), t.end());
			s += it->first;
			t = " ";
			s.append(t.begin(), t.end());
			s += it->second;
			if ((i++) < this->named.size() - 1) {
				t = " ";
				s.append(t.begin(), t.end());
			}
		}

		if (this->named.size() > 0 && this->indexed.size() > 0) {
			t = " ";
			s.append(t.begin(), t.end());
		}

		for (size_t i = 0; i < this->indexed.size(); i++) {
			s += this->indexed[i];
			if (i != this->indexed.size() - 1) {
				t = " ";
				s.append(t.begin(), t.end());
			}
		}

		return s;
	}

	template<class T> const set<basic_string<T>> Argument<T>::Keys(void)
	{
		set<basic_string<T>> keys;
		for (map<basic_string<T>, basic_string<T>>::iterator it = this->named.begin(); it != this->named.end(); it++) {
			keys.insert(it->first);
		}

		return keys;
	}
}