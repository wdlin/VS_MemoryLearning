#include "MemoryDemo.h"
#include <iostream>
using namespace std;

MemoryDemo::MemoryDemo()
{
	cout << "MemoryDemo Construct" << endl;
}
MemoryDemo::~MemoryDemo()
{
	cout << "MemoryDemo Destruct" << endl;
}
void* MemoryDemo::operator new(size_t size)
{
	cout << "operator new " <<size<< endl;
	//return ::operator new(size);//right,调用全局operator new
	//return ::new char[size];//right,编程思想的例子
	return malloc(size);//right
	//return new MemoryDemo();//Bug,会无限循环调用
	//return ::new MemoryDemo();//Bug,会调用两次构造函数
	
}

void MemoryDemo::operator delete(void * ptr)
{
	cout << "operator delete" << endl;
	//::delete ptr;//right,此时ptr是void*所以不会循环调用，也不会出现两次析构函数，编程思想的例子（感觉不太好）
	//::operator delete(ptr);//right,调用全局的operator delete
	free(ptr);//right
	//delete (MemoryDemo*)ptr;//Bug,出现循环调用
	//::delete (MemoryDemo*)ptr;//Bug,会调用两次析构函数
}


void* MemoryDemo::operator new[](std::size_t size)
{
	cout << "operator new[] " << size << endl;
	//return ::operator new(size);//right,调用全局operator new
	//return ::new char[size];//right,编程思想的例子
	//return ::operator new[](size);//right,默认调用operator new(size)
	return malloc(size);
}
void MemoryDemo::operator delete[](void* ptr)
{
	cout << "operator delete[]" << endl;
	//::delete ptr;//right,此时ptr是void*所以不会循环调用，也不会出现两次析构函数，编程思想的例子（感觉不太好）
	//::operator delete(ptr);//right,调用全局的operator delete
	//::operator delete[](ptr);//right,默认调用operator delete(size)
	free(ptr);
}
void* MemoryDemo::operator new(std::size_t size, const std::nothrow_t&)
{
	cout << "operator new nothrow" << endl;
	return malloc(size);
}
void MemoryDemo::operator delete(void* ptr, const std::nothrow_t&)
{
	cout << "operator delete nothrow" << endl;
	free(ptr);
}
void* MemoryDemo::operator new[](std::size_t size, const std::nothrow_t&)
{
	cout << "operator new[] nothrow" << endl;
	return malloc(size);
}
void MemoryDemo::operator delete[](void* ptr, const std::nothrow_t&)
{
	cout << "operator delete[] nothrow" << endl;
	free(ptr);
}

void* MemoryDemo::operator new(std::size_t size, char* str)
{
	cout << "operator new:"<<str<< endl;
	return malloc(size);
}
void MemoryDemo::operator delete(void* ptr, char* str)
{
	cout << "operator delete:" << str << endl;
	free(ptr);
}
void* MemoryDemo::operator new[](std::size_t size, char* str)
{
	cout << "operator new[]:" << str << endl;
	return malloc(size);
}
void MemoryDemo::operator delete[](void* ptr, char* str)
{
	cout << "operator delete[]:" << str << endl;
	free(ptr);
}


MemorySubClass::MemorySubClass(){ cout << "SubClass Construct" << endl; };
MemorySubClass::~MemorySubClass(){ cout << "SubClass Destruct" << endl; };