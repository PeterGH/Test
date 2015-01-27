#include "MergeSortTest.h"

void MergeSortTest::Init(void)
{
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

	Add("SortList", [&](){
		auto check = [&](Test::SingleNode<int> * list){
			cout << "List: " << list << endl;
			size_t len1 = list->Length();
			Test::MergeSort::Sort(list);
			cout << "Sort: " << list << endl;
			size_t len2 = list->Length();
			ASSERT1(len1 == len2);

			Test::SingleNode<int> * p = list;
			Test::SingleNode<int> * n = p->Next();
			while (n != nullptr && n != list) {
				ASSERT1(p->Value() <= n->Value());
				p = n;
				n = n->Next();
			}

			list->DeleteList();
			delete list;
		};
		{
			Test::SingleNode<int> * list = new Test::SingleNode<int>(1);
			check(list);
		}
		{
			Test::SingleNode<int> * list = new Test::SingleNode<int>(1);
			list->Next() = list;
			check(list);
		}
		{
			Test::SingleNode<int> * list = new Test::SingleNode<int>(1);
			list->InsertAtEnd(new Test::SingleNode<int>(2));
			check(list);
		}
		{
			Test::SingleNode<int> * list = new Test::SingleNode<int>(1);
			Test::SingleNode<int> * p = new Test::SingleNode<int>(2);
			list->InsertAtEnd(p);
			p->Next() = list;
			check(list);
		}
		{
			Test::SingleNode<int> * list = new Test::SingleNode<int>(2);
			list->InsertAtEnd(new Test::SingleNode<int>(1));
			check(list);
		}
		{
			Test::SingleNode<int> * list = new Test::SingleNode<int>(2);
			Test::SingleNode<int> * p = new Test::SingleNode<int>(1);
			list->InsertAtEnd(p);
			p->Next() = list;
			check(list);
		}
		{
			Test::SingleNode<int> * list = new Test::SingleNode<int>(2);
			list->InsertAtEnd(new Test::SingleNode<int>(2));
			check(list);
		}
		{
			Test::SingleNode<int> * list = new Test::SingleNode<int>(2);
			list->Next() = list;
			list->InsertAtEnd(new Test::SingleNode<int>(2));
			check(list);
		}
		{
			Test::SingleNode<int> * list = new Test::SingleNode<int>(1);
			list->InsertAtEnd(new Test::SingleNode<int>(2));
			list->InsertAtEnd(new Test::SingleNode<int>(3));
			check(list);
		}
		{
			Test::SingleNode<int> * list = new Test::SingleNode<int>(1);
			list->InsertAtEnd(new Test::SingleNode<int>(2));
			Test::SingleNode<int> * p = new Test::SingleNode<int>(3);
			list->InsertAtEnd(p);
			p->Next() = list;
			check(list);
		}
		{
			Test::SingleNode<int> * list = new Test::SingleNode<int>(1);
			list->InsertAtEnd(new Test::SingleNode<int>(3));
			list->InsertAtEnd(new Test::SingleNode<int>(2));
			check(list);
		}
		{
			Test::SingleNode<int> * list = new Test::SingleNode<int>(1);
			list->InsertAtEnd(new Test::SingleNode<int>(3));
			Test::SingleNode<int> * p = new Test::SingleNode<int>(2);
			list->InsertAtEnd(p);
			p->Next() = list;
			check(list);
		}
		{
			Test::SingleNode<int> * list = new Test::SingleNode<int>(2);
			list->InsertAtEnd(new Test::SingleNode<int>(1));
			list->InsertAtEnd(new Test::SingleNode<int>(3));
			check(list);
		}
		{
			Test::SingleNode<int> * list = new Test::SingleNode<int>(2);
			list->InsertAtEnd(new Test::SingleNode<int>(1));
			Test::SingleNode<int> * p = new Test::SingleNode<int>(3);
			list->InsertAtEnd(p);
			p->Next() = list;
			check(list);
		}
		{
			Test::SingleNode<int> * list = new Test::SingleNode<int>(2);
			list->InsertAtEnd(new Test::SingleNode<int>(3));
			list->InsertAtEnd(new Test::SingleNode<int>(1));
			check(list);
		}
		{
			Test::SingleNode<int> * list = new Test::SingleNode<int>(2);
			list->InsertAtEnd(new Test::SingleNode<int>(3));
			Test::SingleNode<int> * p = new Test::SingleNode<int>(1);
			list->InsertAtEnd(p);
			p->Next() = list;
			check(list);
		}
		{
			Test::SingleNode<int> * list = new Test::SingleNode<int>(3);
			list->InsertAtEnd(new Test::SingleNode<int>(1));
			list->InsertAtEnd(new Test::SingleNode<int>(2));
			check(list);
		}
		{
			Test::SingleNode<int> * list = new Test::SingleNode<int>(3);
			list->InsertAtEnd(new Test::SingleNode<int>(1));
			Test::SingleNode<int> * p = new Test::SingleNode<int>(2);
			list->InsertAtEnd(p);
			p->Next() = list;
			check(list);
		}
		{
			Test::SingleNode<int> * list = new Test::SingleNode<int>(3);
			list->InsertAtEnd(new Test::SingleNode<int>(2));
			list->InsertAtEnd(new Test::SingleNode<int>(1));
			check(list);
		}
		{
			Test::SingleNode<int> * list = new Test::SingleNode<int>(3);
			list->InsertAtEnd(new Test::SingleNode<int>(2));
			Test::SingleNode<int> * p = new Test::SingleNode<int>(1);
			list->InsertAtEnd(p);
			p->Next() = list;
			check(list);
		}
		{
			Test::SingleNode<int> * list = new Test::SingleNode<int>(1);
			list->InsertAtEnd(new Test::SingleNode<int>(2));
			list->InsertAtEnd(new Test::SingleNode<int>(2));
			check(list);
		}
		{
			Test::SingleNode<int> * list = new Test::SingleNode<int>(1);
			list->Next() = list;
			list->InsertAtEnd(new Test::SingleNode<int>(2));
			list->InsertAtEnd(new Test::SingleNode<int>(2));
			check(list);
		}
		{
			Test::SingleNode<int> * list = new Test::SingleNode<int>(2);
			list->InsertAtEnd(new Test::SingleNode<int>(1));
			list->InsertAtEnd(new Test::SingleNode<int>(2));
			check(list);
		}
		{
			Test::SingleNode<int> * list = new Test::SingleNode<int>(2);
			list->Next() = list;
			list->InsertAtEnd(new Test::SingleNode<int>(1));
			list->InsertAtEnd(new Test::SingleNode<int>(2));
			check(list);
		}
		{
			Test::SingleNode<int> * list = new Test::SingleNode<int>(2);
			list->InsertAtEnd(new Test::SingleNode<int>(2));
			list->InsertAtEnd(new Test::SingleNode<int>(1));
			check(list);
		}
		{
			Test::SingleNode<int> * list = new Test::SingleNode<int>(2);
			list->Next() = list;
			list->InsertAtEnd(new Test::SingleNode<int>(2));
			list->InsertAtEnd(new Test::SingleNode<int>(1));
			check(list);
		}
		{
			Test::SingleNode<int> * list = new Test::SingleNode<int>(3);
			list->InsertAtEnd(new Test::SingleNode<int>(3));
			list->InsertAtEnd(new Test::SingleNode<int>(3));
			check(list);
		}
		{
			Test::SingleNode<int> * list = new Test::SingleNode<int>(3);
			list->Next() = list;
			list->InsertAtEnd(new Test::SingleNode<int>(3));
			list->InsertAtEnd(new Test::SingleNode<int>(3));
			check(list);
		}
		{
			Test::SingleNode<int> * list = new Test::SingleNode<int>(1);
			list->InsertAtEnd(new Test::SingleNode<int>(2));
			list->InsertAtEnd(new Test::SingleNode<int>(3));
			list->InsertAtEnd(new Test::SingleNode<int>(4));
			check(list);
		}
		{
			Test::SingleNode<int> * list = new Test::SingleNode<int>(1);
			list->InsertAtEnd(new Test::SingleNode<int>(2));
			list->InsertAtEnd(new Test::SingleNode<int>(3));
			Test::SingleNode<int> * p = new Test::SingleNode<int>(4);
			list->InsertAtEnd(p);
			p->Next() = list;
			check(list);
		}
		{
			Test::SingleNode<int> * list = new Test::SingleNode<int>(2);
			list->InsertAtEnd(new Test::SingleNode<int>(1));
			list->InsertAtEnd(new Test::SingleNode<int>(3));
			list->InsertAtEnd(new Test::SingleNode<int>(4));
			check(list);
		}
		{
			Test::SingleNode<int> * list = new Test::SingleNode<int>(2);
			list->InsertAtEnd(new Test::SingleNode<int>(1));
			list->InsertAtEnd(new Test::SingleNode<int>(3));
			Test::SingleNode<int> * p = new Test::SingleNode<int>(4);
			list->InsertAtEnd(p);
			p->Next() = list;
			check(list);
		}
		{
			Test::SingleNode<int> * list = new Test::SingleNode<int>(2);
			list->InsertAtEnd(new Test::SingleNode<int>(3));
			list->InsertAtEnd(new Test::SingleNode<int>(1));
			list->InsertAtEnd(new Test::SingleNode<int>(4));
			check(list);
		}
		{
			Test::SingleNode<int> * list = new Test::SingleNode<int>(2);
			list->InsertAtEnd(new Test::SingleNode<int>(3));
			list->InsertAtEnd(new Test::SingleNode<int>(1));
			Test::SingleNode<int> * p = new Test::SingleNode<int>(4);
			list->InsertAtEnd(p);
			p->Next() = list;
			check(list);
		}
		{
			Test::SingleNode<int> * list = new Test::SingleNode<int>(2);
			list->InsertAtEnd(new Test::SingleNode<int>(3));
			list->InsertAtEnd(new Test::SingleNode<int>(4));
			list->InsertAtEnd(new Test::SingleNode<int>(1));
			check(list);
		}
		{
			Test::SingleNode<int> * list = new Test::SingleNode<int>(2);
			list->InsertAtEnd(new Test::SingleNode<int>(3));
			list->InsertAtEnd(new Test::SingleNode<int>(4));
			Test::SingleNode<int> * p = new Test::SingleNode<int>(1);
			list->InsertAtEnd(p);
			p->Next() = list;
			check(list);
		}
		{
			Test::SingleNode<int> * list = new Test::SingleNode<int>(3);
			list->InsertAtEnd(new Test::SingleNode<int>(2));
			list->InsertAtEnd(new Test::SingleNode<int>(1));
			list->InsertAtEnd(new Test::SingleNode<int>(4));
			check(list);
		}
		{
			Test::SingleNode<int> * list = new Test::SingleNode<int>(3);
			list->InsertAtEnd(new Test::SingleNode<int>(2));
			list->InsertAtEnd(new Test::SingleNode<int>(1));
			Test::SingleNode<int> * p = new Test::SingleNode<int>(4);
			list->InsertAtEnd(p);
			p->Next() = list;
			check(list);
		}
		{
			Test::SingleNode<int> * list = new Test::SingleNode<int>(3);
			list->InsertAtEnd(new Test::SingleNode<int>(2));
			list->InsertAtEnd(new Test::SingleNode<int>(4));
			list->InsertAtEnd(new Test::SingleNode<int>(1));
			check(list);
		}
		{
			Test::SingleNode<int> * list = new Test::SingleNode<int>(3);
			list->InsertAtEnd(new Test::SingleNode<int>(2));
			list->InsertAtEnd(new Test::SingleNode<int>(4));
			Test::SingleNode<int> * p = new Test::SingleNode<int>(1);
			list->InsertAtEnd(p);
			p->Next() = list;
			check(list);
		}
		{
			Test::SingleNode<int> * list = new Test::SingleNode<int>(4);
			list->InsertAtEnd(new Test::SingleNode<int>(1));
			list->InsertAtEnd(new Test::SingleNode<int>(2));
			list->InsertAtEnd(new Test::SingleNode<int>(3));
			check(list);
		}
		{
			Test::SingleNode<int> * list = new Test::SingleNode<int>(4);
			list->InsertAtEnd(new Test::SingleNode<int>(1));
			list->InsertAtEnd(new Test::SingleNode<int>(2));
			Test::SingleNode<int> * p = new Test::SingleNode<int>(3);
			list->InsertAtEnd(p);
			p->Next() = list;
			check(list);
		}
		{
			Test::SingleNode<int> * list = new Test::SingleNode<int>(4);
			list->InsertAtEnd(new Test::SingleNode<int>(2));
			list->InsertAtEnd(new Test::SingleNode<int>(1));
			list->InsertAtEnd(new Test::SingleNode<int>(3));
			check(list);
		}
		{
			Test::SingleNode<int> * list = new Test::SingleNode<int>(4);
			list->InsertAtEnd(new Test::SingleNode<int>(2));
			list->InsertAtEnd(new Test::SingleNode<int>(1));
			Test::SingleNode<int> * p = new Test::SingleNode<int>(3);
			list->InsertAtEnd(p);
			p->Next() = list;
			check(list);
		}
		{
			Test::SingleNode<int> * list = new Test::SingleNode<int>(4);
			list->InsertAtEnd(new Test::SingleNode<int>(2));
			list->InsertAtEnd(new Test::SingleNode<int>(3));
			list->InsertAtEnd(new Test::SingleNode<int>(1));
			check(list);
		}
		{
			Test::SingleNode<int> * list = new Test::SingleNode<int>(4);
			list->InsertAtEnd(new Test::SingleNode<int>(2));
			list->InsertAtEnd(new Test::SingleNode<int>(3));
			Test::SingleNode<int> * p = new Test::SingleNode<int>(1);
			list->InsertAtEnd(p);
			p->Next() = list;
			check(list);
		}
		{
			for (int i = 0; i < 100; i++) {
				Logger().WriteInformation("Run %d\n", i);
				Test::SingleNode<int> * list = new Test::SingleNode<int>(Test::Random::Next());
				int len = Test::Random::Next(100);
				for (int j = 0; j < len; j++) {
					list->InsertAtEnd(new Test::SingleNode<int>(Test::Random::Next()));
				}
				check(list);
			}
		}
		{
			for (int i = 0; i < 100; i++) {
				Logger().WriteInformation("Run %d\n", i);
				Test::SingleNode<int> * list = new Test::SingleNode<int>(Test::Random::Next());
				int len = Test::Random::Next(100);
				for (int j = 0; j < len; j++) {
					list->InsertAtEnd(new Test::SingleNode<int>(Test::Random::Next()));
				}
				Test::SingleNode<int> * p = new Test::SingleNode<int>(Test::Random::Next());
				list->InsertAtEnd(p);
				p->Next() = list;
				check(list);
			}
		}
	});
}