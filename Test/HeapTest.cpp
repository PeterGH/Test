#include "HeapTest.h"

void HeapTest::Init(void)
{
	Add("Max Heap Push", [&](){
		Test::Heap<int> heap;

		Logger().WriteInformation("At beginning, is %sheap\n", heap.IsHeap() ? "" : "not ");
		heap.Print(Logger());
		ASSERT1(heap.IsHeap());

		heap.Push(0);
		Logger().WriteInformation("Pushed 0, is %sheap\n", heap.IsHeap() ? "" : "not ");
		heap.Print(Logger()); 
		ASSERT1(heap.IsHeap());
		ASSERT1(heap.Top() == 0);

		heap.Push(1);
		Logger().WriteInformation("Pushed 1, is %sheap\n", heap.IsHeap() ? "" : "not ");
		heap.Print(Logger()); 
		ASSERT1(heap.IsHeap());
		ASSERT1(heap.Top() == 1);

		heap.Push(2);
		Logger().WriteInformation("Pushed 2, is %sheap\n", heap.IsHeap() ? "" : "not ");
		heap.Print(Logger()); 
		ASSERT1(heap.IsHeap());
		ASSERT1(heap.Top() == 2);

		heap.Push(-1);
		Logger().WriteInformation("Pushed -1, is %sheap\n", heap.IsHeap() ? "" : "not ");
		heap.Print(Logger()); 
		ASSERT1(heap.IsHeap());
		ASSERT1(heap.Top() == 2);

		for (int i = 3; i < 10; i++) {
			heap.Push(i);
			ASSERT1(heap.Top() == i);
		}

		Logger().WriteInformation("Pushed 3..9, is %sheap\n", heap.IsHeap() ? "" : "not ");
		heap.Print(Logger()); 
		ASSERT1(heap.IsHeap());
	});

	Add("Max Heap Pop", [&](){
		Test::Heap<int> heap;

		for (int i = 0; i < 10; i++) {
			heap.Push(i);
			ASSERT1(heap.Top() == i);
		}

		Logger().WriteInformation("Pushed 0..9, is %sheap\n", heap.IsHeap() ? "" : "not ");
		heap.Print(Logger()); 
		ASSERT1(heap.IsHeap());

		for (int i = 0; i < 10; i++) {
			int v = heap.Pop();
			Logger().WriteInformation("Popped %d, is %sheap\n", v, heap.IsHeap() ? "" : "not ");
			heap.Print(Logger()); 
			ASSERT1(heap.IsHeap());
			ASSERT1(v == (9 - i));
		}
	});

	Add("Max Heap Constructor", [&](){
		vector<int> input;

		for (int i = 0; i < 10; i++) {
			input.push_back(i);
		}

		Test::Heap<int> heap(input);
		Logger().WriteInformation("Constructor([0..9]), is %sheap\n", heap.IsHeap() ? "" : "not ");
		heap.Print(Logger()); 
		ASSERT1(heap.IsHeap());
		ASSERT1(heap.Top() == 9);
	});

	Add("Max Heap 1", [&](){
		Test::Heap<int> heap(1);

		Logger().WriteInformation("At beginning, is %sheap\n", heap.IsHeap() ? "" : "not ");
		heap.Print(Logger()); 
		ASSERT1(heap.IsHeap());

		heap.Push(0);
		Logger().WriteInformation("Pushed 0, is %sheap\n", heap.IsHeap() ? "" : "not ");
		heap.Print(Logger()); 
		ASSERT1(heap.IsHeap());
		ASSERT1(heap.Top() == 0);

		heap.Push(1);
		Logger().WriteInformation("Pushed 1, is %sheap\n", heap.IsHeap() ? "" : "not ");
		heap.Print(Logger()); 
		ASSERT1(heap.IsHeap());
		ASSERT1(heap.Top() == 0);

		heap.Push(2);
		Logger().WriteInformation("Pushed 2, is %sheap\n", heap.IsHeap() ? "" : "not ");
		heap.Print(Logger());
		ASSERT1(heap.IsHeap());
		ASSERT1(heap.Top() == 0);

		heap.Push(-1);
		Logger().WriteInformation("Pushed -1, is %sheap\n", heap.IsHeap() ? "" : "not ");
		heap.Print(Logger()); 
		ASSERT1(heap.IsHeap());
		ASSERT1(heap.Top() == -1);

		for (int i = 3; i < 10; i++) {
			heap.Push(i);
			ASSERT1(heap.Top() == -1);
		}

		Logger().WriteInformation("Pushed 3..9, is %sheap\n", heap.IsHeap() ? "" : "not ");
		heap.Print(Logger()); 
		ASSERT1(heap.IsHeap());
		ASSERT1(heap.Top() == -1);
	});

	Add("Max Heap 2", [&](){
		// This example shows the heap keeps the smallest two numbers from the input

		Test::Heap<int> heap(2);

		Logger().WriteInformation("At beginning, is %sheap\n", heap.IsHeap() ? "" : "not ");
		heap.Print(Logger()); 
		ASSERT1(heap.IsHeap());

		heap.Push(0);
		Logger().WriteInformation("Pushed 0, is %sheap\n", heap.IsHeap() ? "" : "not ");
		heap.Print(Logger()); 
		ASSERT1(heap.IsHeap());
		ASSERT1(heap.Top() == 0);

		heap.Push(1);
		Logger().WriteInformation("Pushed 1, is %sheap\n", heap.IsHeap() ? "" : "not ");
		heap.Print(Logger()); 
		ASSERT1(heap.IsHeap());
		ASSERT1(heap.Top() == 1);

		heap.Push(2);
		Logger().WriteInformation("Pushed 2, is %sheap\n", heap.IsHeap() ? "" : "not ");
		heap.Print(Logger()); 
		ASSERT1(heap.IsHeap());
		ASSERT1(heap.Top() == 1);

		heap.Push(-1);
		Logger().WriteInformation("Pushed -1, is %sheap\n", heap.IsHeap() ? "" : "not ");
		heap.Print(Logger()); 
		ASSERT1(heap.IsHeap());
		ASSERT1(heap.Top() == 0);

		for (int i = 3; i < 10; i++) {
			heap.Push(i);
			ASSERT1(heap.Top() == 0);
		}

		Logger().WriteInformation("Pushed 3..9, is %sheap\n", heap.IsHeap() ? "" : "not ");
		heap.Print(Logger()); 
		ASSERT1(heap.IsHeap());
		ASSERT1(heap.Top() == 0);
	});

	Add("Min Heap Push", [&](){
		Test::Heap<int, greater<int>> heap;

		Logger().WriteInformation("At beginning, is %sheap\n", heap.IsHeap() ? "" : "not ");
		heap.Print(Logger()); 
		ASSERT1(heap.IsHeap());

		heap.Push(0);
		Logger().WriteInformation("Pushed 0, is %sheap\n", heap.IsHeap() ? "" : "not ");
		heap.Print(Logger()); 
		ASSERT1(heap.IsHeap());
		ASSERT1(heap.Top() == 0);

		heap.Push(1);
		Logger().WriteInformation("Pushed 1, is %sheap\n", heap.IsHeap() ? "" : "not ");
		heap.Print(Logger()); 
		ASSERT1(heap.IsHeap());
		ASSERT1(heap.Top() == 0);

		heap.Push(2);
		Logger().WriteInformation("Pushed 2, is %sheap\n", heap.IsHeap() ? "" : "not ");
		heap.Print(Logger());
		ASSERT1(heap.IsHeap());
		ASSERT1(heap.Top() == 0);

		heap.Push(-1);
		Logger().WriteInformation("Pushed -1, is %sheap\n", heap.IsHeap() ? "" : "not ");
		heap.Print(Logger());
		ASSERT1(heap.IsHeap());
		ASSERT1(heap.Top() == -1);

		for (int i = 3; i < 10; i++) {
			heap.Push(i);
			ASSERT1(heap.Top() == -1);
		}

		Logger().WriteInformation("Pushed 3..9, is %sheap\n", heap.IsHeap() ? "" : "not ");
		heap.Print(Logger());
		ASSERT1(heap.IsHeap());
	});

	Add("Min Heap Pop", [&](){
		Test::Heap<int, greater<int>> heap;

		for (int i = 0; i < 10; i++) {
			heap.Push(i);
			ASSERT1(heap.Top() == 0);
		}

		Logger().WriteInformation("Pushed 0..9, is %sheap\n", heap.IsHeap() ? "" : "not ");
		heap.Print(Logger());
		ASSERT1(heap.IsHeap());

		for (int i = 0; i < 10; i++) {
			int v = heap.Pop();
			Logger().WriteInformation("Popped %d, is %sheap\n", v, heap.IsHeap() ? "" : "not ");
			heap.Print(Logger());
			ASSERT1(heap.IsHeap());
			ASSERT1(v == i);
		}
	});

	Add("Min Heap Constructor", [&](){
		vector<int> input;

		for (int i = 0; i < 10; i++) {
			input.push_back(i);
		}

		Test::Heap<int, greater<int>> heap(input);
		Logger().WriteInformation("Constructor([0..9]), is %sheap\n", heap.IsHeap() ? "" : "not ");
		heap.Print(Logger());
		ASSERT1(heap.IsHeap());
		ASSERT1(heap.Top() == 0);
	});

	Add("Min Heap 1", [&](){
		Test::Heap<int, greater<int>> heap(1);

		Logger().WriteInformation("At beginning, is %sheap\n", heap.IsHeap() ? "" : "not ");
		heap.Print(Logger());
		ASSERT1(heap.IsHeap());

		heap.Push(0);
		Logger().WriteInformation("Pushed 0, is %sheap\n", heap.IsHeap() ? "" : "not ");
		heap.Print(Logger());
		ASSERT1(heap.IsHeap());
		ASSERT1(heap.Top() == 0);

		heap.Push(1);
		Logger().WriteInformation("Pushed 1, is %sheap\n", heap.IsHeap() ? "" : "not ");
		heap.Print(Logger());
		ASSERT1(heap.IsHeap());
		ASSERT1(heap.Top() == 1);

		heap.Push(2);
		Logger().WriteInformation("Pushed 2, is %sheap\n", heap.IsHeap() ? "" : "not ");
		heap.Print(Logger());
		ASSERT1(heap.IsHeap());
		ASSERT1(heap.Top() == 2);

		heap.Push(-1);
		Logger().WriteInformation("Pushed -1, is %sheap\n", heap.IsHeap() ? "" : "not ");
		heap.Print(Logger());
		ASSERT1(heap.IsHeap());
		ASSERT1(heap.Top() == 2);

		for (int i = 3; i < 10; i++) {
			heap.Push(i);
			ASSERT1(heap.Top() == i);
		}

		Logger().WriteInformation("Pushed 3..9, is %sheap\n", heap.IsHeap() ? "" : "not ");
		heap.Print(Logger());
		ASSERT1(heap.IsHeap());
	});

	Add("Min Heap 2", [&](){
		// This example shows the heap keeps the greatest two numbers from the input

		Test::Heap<int, greater<int>> heap(2);

		Logger().WriteInformation("At beginning, is %sheap\n", heap.IsHeap() ? "" : "not ");
		heap.Print(Logger());
		ASSERT1(heap.IsHeap());

		heap.Push(0);
		Logger().WriteInformation("Pushed 0, is %sheap\n", heap.IsHeap() ? "" : "not ");
		heap.Print(Logger());
		ASSERT1(heap.IsHeap());
		ASSERT1(heap.Top() == 0);

		heap.Push(1);
		Logger().WriteInformation("Pushed 1, is %sheap\n", heap.IsHeap() ? "" : "not ");
		heap.Print(Logger());
		ASSERT1(heap.IsHeap());
		ASSERT1(heap.Top() == 0);

		heap.Push(2);
		Logger().WriteInformation("Pushed 2, is %sheap\n", heap.IsHeap() ? "" : "not ");
		heap.Print(Logger());
		ASSERT1(heap.IsHeap());
		ASSERT1(heap.Top() == 1);

		heap.Push(-1);
		Logger().WriteInformation("Pushed -1, is %sheap\n", heap.IsHeap() ? "" : "not ");
		heap.Print(Logger());
		ASSERT1(heap.IsHeap());
		ASSERT1(heap.Top() == 1);

		for (int i = 3; i < 10; i++) {
			heap.Push(i);
			ASSERT1(heap.Top() == (i - 1));
		}

		Logger().WriteInformation("Pushed 3..9, is %sheap\n", heap.IsHeap() ? "" : "not ");
		heap.Print(Logger());
		ASSERT1(heap.IsHeap());
	});
}
