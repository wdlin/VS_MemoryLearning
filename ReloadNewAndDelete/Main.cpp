#include <iostream>
#include "MemoryDemo.h"
using namespace std;

//#define GLOBAL_RELOAD
#ifdef GLOBAL_RELOAD
//重载全局operator new和operator delete
class GlobalTest
{
public:
	GlobalTest(){cout<<"Global Construct"<<endl;};
	~GlobalTest(){cout<<"Global Destruct"<<endl;};
};
void* operator new(size_t size)
{
	cout << "global operator new" << endl;
	return malloc(size);
}
void operator delete(void* ptr)
{
	cout << "global operator delete" << endl;
	free(ptr);
}
void* operator new[](size_t size)
{
	cout << "global operator new[]" << endl;
	return malloc(size);
}
void operator delete[](void* ptr)
{
	cout << "global operator delete[]" << endl;
	free(ptr);
}
#endif

int main()
{
#ifdef GLOBAL_RELOAD
	cout << "Test0****************" << endl;
	GlobalTest* glo = new GlobalTest[2];
	delete[] glo;
#endif
	cout << "Test1****************" << endl;
	MemoryDemo* mem = new MemoryDemo();
	delete mem;
	cout << "Test2****************" << endl;
	mem = new MemoryDemo[3];
	delete[] mem;
	cout << "Test3****************" << endl;
	mem = new (nothrow)MemoryDemo();
	delete mem;
	cout << "Test4****************" << endl;
	mem = new (nothrow)MemoryDemo[3];
	delete[] mem;
	cout << "Test5****************" << endl;
	mem = new("test new")MemoryDemo();
	delete mem;
	cout << "Test6****************" << endl;
	mem = new("test new[]")MemoryDemo[3];
	delete[] mem;
	cout << "Test7****************" << endl;
	mem = new MemorySubClass();
	delete mem;
	cout << "Test8****************" << endl;
	mem = new MemorySubClass[3];
	delete[] mem;
	cout << "Test9****************" << endl;
	MemorySubClass* mem1 = new MemorySubClass();
	delete mem1;
	cout << "Test10****************" << endl;
	mem1 = new MemorySubClass[3];
	delete[] mem1;
	system("pause");
	return 0;
}

/*
Test1****************
operator new 4
MemoryDemo Construct
MemoryDemo Destruct
operator delete
Test2****************
operator new[] 16
MemoryDemo Construct
MemoryDemo Construct
MemoryDemo Construct
MemoryDemo Destruct
MemoryDemo Destruct
MemoryDemo Destruct
operator delete[]
Test3****************
operator new nothrow
MemoryDemo Construct
MemoryDemo Destruct
operator delete
Test4****************
operator new[] nothrow
MemoryDemo Construct
MemoryDemo Construct
MemoryDemo Construct
MemoryDemo Destruct
MemoryDemo Destruct
MemoryDemo Destruct
operator delete[]
Test5****************
operator new:test new
MemoryDemo Construct
MemoryDemo Destruct
operator delete
Test6****************
operator new[]:test new[]
MemoryDemo Construct
MemoryDemo Construct
MemoryDemo Construct
MemoryDemo Destruct
MemoryDemo Destruct
MemoryDemo Destruct
operator delete[]
Test7****************
operator new 4
MemoryDemo Construct
SubClass Construct
SubClass Destruct
MemoryDemo Destruct
operator delete
Test8****************
operator new[] 16
MemoryDemo Construct
SubClass Construct
MemoryDemo Construct
SubClass Construct
MemoryDemo Construct
SubClass Construct
SubClass Destruct
MemoryDemo Destruct
SubClass Destruct
MemoryDemo Destruct
SubClass Destruct
MemoryDemo Destruct
operator delete[]
Test9****************
operator new 4
MemoryDemo Construct
SubClass Construct
SubClass Destruct
MemoryDemo Destruct
operator delete
Test10****************
operator new[] 16
MemoryDemo Construct
SubClass Construct
MemoryDemo Construct
SubClass Construct
MemoryDemo Construct
SubClass Construct
SubClass Destruct
MemoryDemo Destruct
SubClass Destruct
MemoryDemo Destruct
SubClass Destruct
MemoryDemo Destruct
operator delete[]
请按任意键继续. . .
*/