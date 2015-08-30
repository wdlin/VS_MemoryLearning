#include <iostream>
#include "MemoryPool.h"
#include <ctime>
using namespace std;

class TestClass
{
public:
	void* operator new(size_t size)
	{
		void* ptr = pool->allocate();
		cout << "new: " <<(int)ptr<< endl;
		return ptr;
	}
	void operator delete(void* ptr)
	{
		cout << "delete: " << (int)ptr << endl;
		pool->free(ptr);
	}
	static void createPool()
	{
		if (pool == nullptr)
			pool = new MemoryPool<TestClass>;
	}
	static void deletePool()
	{
		delete pool;
		pool = nullptr;
	}
private:
	static MemoryPool<TestClass>* pool;
};
MemoryPool<TestClass>* TestClass::pool = nullptr;
void test()
{
	TestClass* tp[50];
	for (int i = 0; i < 50; i++)
	{
		tp[i] = new TestClass();
		if (rand() % 2 == 0)delete tp[i];
	}
}

int main()
{
	srand(time(NULL));
	TestClass::createPool();
	test();
	TestClass::deletePool();
	system("pause");
	return 0;
}

/*

new: 6932272
delete : 6932272
new : 6932272
delete : 6932272
new : 6932272
new : 6932208
delete : 6932208
new : 6932208
delete : 6932208
new : 6932208
delete : 6932208
new : 6932208
delete : 6932208
new : 6932208
new : 6932144
new : 6932080
delete : 6932080
new : 6932080
new : 6932016
new : 6931952
delete : 6931952
new : 6931952
new : 6931888
new : 6931824
delete : 6931824
new : 6931824
new : 6931760
delete : 6931760
new : 6931760
delete : 6931760
new : 6931760
new : 6931696
delete : 6931696
new : 6931696
new : 6931632
delete : 6931632
new : 6931632
new : 6931568
delete : 6931568
new : 6931568
new : 6931504
new : 6931440
delete : 6931440
new : 6931440
delete : 6931440
new : 6931440
delete : 6931440
new : 6931440
new : 6931376
delete : 6931376
new : 6931376
new : 6931312
new : 6931248
new : 6931184
delete : 6931184
new : 6931184
delete : 6931184
new : 6931184
delete : 6931184
new : 6931184
new : 6931120
delete : 6931120
new : 6931120
delete : 6931120
new : 6931120
delete : 6931120
new : 6931120
new : 6931056
new : 6930992
new : 6930928
new : 6930864
new : 6930800
new : 6930736
delete : 6930736
new : 6930736

*/