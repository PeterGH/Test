#pragma once

#include <stack>

using namespace std;

namespace Test {
	template<class T> class Queue {
	private:
		stack<T> in, out;
		void FlushInToOut(void);
	public:
		Queue(void) {}
		~Queue(void) {}

		T & Back(void);
		bool Empty(void) const;
		T & Front(void);
		void Pop(void);
		void Push(const T & value);
		size_t Size(void) const;
	};

	template<class T> void Queue<T>::FlushInToOut(void)
	{
		while (!in.empty()) {
			T v = in.top();
			in.pop();
			out.push(v);
		}
	}

	template<class T> T & Queue<T>::Back(void)
	{
		if (in.empty()) {
			if (out.empty()) throw runtime_error("Queue is empty");
			while (!out.empty()) {
				T v = out.top();
				out.pop();
				in.push(v);
			}
		}

		return in.top();
	}

	template<class T> bool Queue<T>::Empty(void) const
	{
		return out.empty() && in.empty();
	}

	template<class T> T & Queue<T>::Front(void)
	{
		if (out.empty()) FlushInToOut();
		if (out.empty()) throw runtime_error("Queue is empty");
		return out.top();
	}

	template<class T> void Queue<T>::Pop(void)
	{
		if (out.empty()) FlushInToOut();
		if (out.empty()) throw runtime_error("Queue is empty");
		out.pop();
	}

	template<class T> void Queue<T>::Push(const T & value)
	{
		in.push(value);
	}

	template<class T> size_t Queue<T>::Size(void) const
	{
		return out.size() + in.size();
	}
}