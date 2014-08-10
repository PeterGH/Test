#include "MergeSortTest.h"

void MergeSortTest::Init(void)
{
	Add("Sort 1", [&](){
		int I[] = { 1 };
		Test::MergeSort::Sort<int>(I, 1);
		ASSERT1(I[0] == 1);
	});

	Add("Sort 2", [&](){
		int I[] = { 2, 1 };

		Test::MergeSort::Sort<int>(I, 2);
		ASSERT1(I[0] == 1);
		ASSERT1(I[1] == 2);

		Test::MergeSort::Sort<int>(I, 2);
		ASSERT1(I[0] == 1);
		ASSERT1(I[1] == 2);

		I[1] = I[0];
		Test::MergeSort::Sort<int>(I, 2);
		ASSERT1(I[0] == 1);
		ASSERT1(I[1] == 1);
	});
	
	Add("Sort 3", [&](){
		int I[] = { 3, 2, 1 };

		Test::MergeSort::Sort<int>(I, 3);
		ASSERT1(I[0] == 1);
		ASSERT1(I[1] == 2);
		ASSERT1(I[2] == 3);

		Test::MergeSort::Sort<int>(I, 3);
		ASSERT1(I[0] == 1);
		ASSERT1(I[1] == 2);
		ASSERT1(I[2] == 3);

		I[1] = I[0];
		I[2] = I[0];
		Test::MergeSort::Sort<int>(I, 3);
		ASSERT1(I[0] == 1);
		ASSERT1(I[1] == 1);
		ASSERT1(I[2] == 1);
	});

	Add("Sort more", [&](){
		int I[] = { 3, 43, 42, 1, 3, 3556, 7, 34, 8, 8769, 96656532, 1, 445, 35, 64 };
		int L = sizeof(I) / sizeof(I[0]);

		std::vector<int> V;
		for (int i = 0; i < L; i++) {
			V.push_back(I[i]);
		}

		Test::MergeSort::Sort<int>(I, L);

		std::sort(V.begin(), V.end());

		for (int i = 0; i < L; i++) {
			ASSERT1(V[i] == I[i]);
		}
	});
	
	Add("Parallel sort", [&](){
		int I[] = { 3, 43, 42, 1, 3, 3556, 7, 34, 8, 8769, 96656532, 1, 445, 35, 64 };
		int L = sizeof(I) / sizeof(I[0]);

		std::vector<int> V;
		for (int i = 0; i < L; i++) {
			V.push_back(I[i]);
		}

		Test::MergeSort::ParallelSort<int>(I, L);

		std::sort(V.begin(), V.end());

		for (int i = 0; i < L; i++) {
			ASSERT1(V[i] == I[i]);
		}
	});

	Add("Sort Random", [&](){
		for (int j = 0; j < 100; j++) {
			unsigned int length = (unsigned int)Test::Random::Next();
			Logger().WriteInformation("Run %d, %d elements\n", j, length);

			unique_ptr<int[]> a1(new int[length]);
			unique_ptr<int[]> a2(new int[length]);
			vector<int> v;
			for (unsigned int i = 0; i < length; i++) {
				int t = Test::Random::Next();
				a1[i] = t;
				a2[i] = t;
				v.push_back(t);
			}

			Test::MergeSort::Sort(a1.get(), length);
			Test::MergeSort::ParallelSort(a2.get(), length);
			std::sort(v.begin(), v.end());

			for (unsigned int i = 0; i < length; i++) {
				ASSERT2(a1[i] == a2[i], Test::String::Format("a1[%d] %d != a2[%d] %d", i, a1[i], i, a2[i]));
				ASSERT2(a1[i] == v[i], Test::String::Format("a1[%d] %d != v[%d] %d", i, a1[i], i, v[i]));
			}
		}
	});

	Add("Count inversions", [&](){
		auto check = [&](int * A, int L, int expected) -> void {
			int count = Test::MergeSort::CountInversions<int>(A, L);
			ASSERT1(expected == count);
		};

		int I1[] = { 0 };
		check(I1, 1, 0);

		int I2[] = { 0, 1 };
		check(I2, 2, 0);

		int I3[] = { 1, 0 };
		check(I3, 2, 1);

		int I4[] = { 0, 1, 2 };
		check(I4, 3, 0);

		int I5[] = { 1, 0, 2 };
		check(I5, 3, 1);

		int I6[] = { 2, 0, 1 };
		check(I6, 3, 2);

		int I7[] = { 2, 1, 0 };
		check(I7, 3, 3);

		int I8[] = { 0, 2, 1 };
		check(I8, 3, 1);

		int I9[] = { 1, 2, 0 };
		check(I9, 3, 2);

		int I10[] = { 3, 2, 1, 0 };
		check(I10, 4, 6);

		int I11[] = { 9, 8, 7, 6, 5, 4, 3, 2, 1, 0 };
		int L = sizeof(I11) / sizeof(I11[0]);
		check(I11, L, 45);
	});
	
	Add("Multiple inputs", [&](){
		int * inputs[3];
		size_t sizes[3];

		int a0[] = { 0, 5, 9, 11 };
		inputs[0] = a0;
		sizes[0] = 4;

		int a1[] = { 0, 1, 2, 3, 5, 6 };
		inputs[1] = a1;
		sizes[1] = 6;

		int a2[] = { 6, 7, 8 };
		inputs[2] = a2;
		sizes[2] = 3;

		vector<int> output;

		Test::MergeSort::Sort<int>(inputs, sizes, (size_t)3, output);

		ASSERT1(is_sorted(output.begin(), output.end()));
		ASSERT1(output.size() == 13);

		for_each(output.begin(), output.end(), [&](int e) -> void {
			Logger().WriteInformation("\t%d", e);
		});

		Logger().WriteInformation("\n");
	});

	Add("MergeList", [&](){
		auto check = [&](Test::SingleNode<int> * f, Test::SingleNode<int> * s){
			cout << "First: " << f << endl;
			cout << "Second: " << s << endl;
			Test::MergeSort::Merge(f, s);
			cout << "Merge: " << f << endl;
			Test::SingleNode<int> * p = f;
			int i = 0;
			while (p != nullptr) {
				ASSERT1(p->Value() == i);
				p = p->Next();
				i++;
			}
			f->DeleteList();
			delete f;
		};
		{
			Test::SingleNode<int> * f = new Test::SingleNode<int>(0);
			Test::SingleNode<int> * s = new Test::SingleNode<int>(1);
			check(f, s);
		}
		{
			Test::SingleNode<int> * f = new Test::SingleNode<int>(1);
			Test::SingleNode<int> * s = new Test::SingleNode<int>(0);
			check(f, s);
		}
		{
			Test::SingleNode<int> * f = new Test::SingleNode<int>(0);
			Test::SingleNode<int> * s = new Test::SingleNode<int>(1);
			s->InsertAtEnd(new Test::SingleNode<int>(2));
			check(f, s);
		}
		{
			Test::SingleNode<int> * f = new Test::SingleNode<int>(1);
			Test::SingleNode<int> * s = new Test::SingleNode<int>(0);
			s->InsertAtEnd(new Test::SingleNode<int>(2));
			check(f, s);
		}
		{
			Test::SingleNode<int> * f = new Test::SingleNode<int>(2);
			Test::SingleNode<int> * s = new Test::SingleNode<int>(0);
			s->InsertAtEnd(new Test::SingleNode<int>(1));
			check(f, s);
		}
		{
			Test::SingleNode<int> * f = new Test::SingleNode<int>(0);
			f->InsertAtEnd(new Test::SingleNode<int>(1));
			Test::SingleNode<int> * s = new Test::SingleNode<int>(2);
			check(f, s);
		}
		{
			Test::SingleNode<int> * f = new Test::SingleNode<int>(0);
			f->InsertAtEnd(new Test::SingleNode<int>(2));
			Test::SingleNode<int> * s = new Test::SingleNode<int>(1);
			check(f, s);
		}
		{
			Test::SingleNode<int> * f = new Test::SingleNode<int>(1);
			f->InsertAtEnd(new Test::SingleNode<int>(2));
			Test::SingleNode<int> * s = new Test::SingleNode<int>(0);
			check(f, s);
		}
		{
			Test::SingleNode<int> * f = new Test::SingleNode<int>(0);
			f->InsertAtEnd(new Test::SingleNode<int>(1));
			Test::SingleNode<int> * s = new Test::SingleNode<int>(2);
			s->InsertAtEnd(new Test::SingleNode<int>(3));
			check(f, s);
		}
		{
			Test::SingleNode<int> * f = new Test::SingleNode<int>(0);
			f->InsertAtEnd(new Test::SingleNode<int>(2));
			Test::SingleNode<int> * s = new Test::SingleNode<int>(1);
			s->InsertAtEnd(new Test::SingleNode<int>(3));
			check(f, s);
		}
		{
			Test::SingleNode<int> * f = new Test::SingleNode<int>(0);
			f->InsertAtEnd(new Test::SingleNode<int>(3));
			Test::SingleNode<int> * s = new Test::SingleNode<int>(1);
			s->InsertAtEnd(new Test::SingleNode<int>(2));
			check(f, s);
		}
		{
			Test::SingleNode<int> * f = new Test::SingleNode<int>(1);
			f->InsertAtEnd(new Test::SingleNode<int>(2));
			Test::SingleNode<int> * s = new Test::SingleNode<int>(0);
			s->InsertAtEnd(new Test::SingleNode<int>(3));
			check(f, s);
		}
		{
			Test::SingleNode<int> * f = new Test::SingleNode<int>(1);
			f->InsertAtEnd(new Test::SingleNode<int>(3));
			Test::SingleNode<int> * s = new Test::SingleNode<int>(0);
			s->InsertAtEnd(new Test::SingleNode<int>(2));
			check(f, s);
		}
		{
			Test::SingleNode<int> * f = new Test::SingleNode<int>(2);
			f->InsertAtEnd(new Test::SingleNode<int>(3));
			Test::SingleNode<int> * s = new Test::SingleNode<int>(0);
			s->InsertAtEnd(new Test::SingleNode<int>(1));
			check(f, s);
		}
	});
}