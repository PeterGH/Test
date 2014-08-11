#pragma once
#include <map>
using namespace std;
namespace Test {
	class LRUCache {
	private:
		int _capacity;

		struct Item {
			int key;
			int value;
			struct Item * prev;
			struct Item * next;
			Item(int k, int v) : key(k), value(v), prev(nullptr), next(nullptr) {}
		} * head, * tail;

		map<int, struct Item *> keys;

		void MoveFront(struct Item * p);
	public:
		// Use __declspec(dllexport) on method instead of class
		// Otherwise, there will be 'warning C4251' because the map
		// container is exported for this dll, which seems to be discouraged.

		__declspec(dllexport) LRUCache(int capacity) : _capacity(capacity), head(nullptr), tail(nullptr) {}
		__declspec(dllexport) ~LRUCache(void);

		__declspec(dllexport) int Get(int key);
		__declspec(dllexport) void Set(int key, int value);
	};
}