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
	//return ::operator new(size);//right,����ȫ��operator new
	//return ::new char[size];//right,���˼�������
	return malloc(size);//right
	//return new MemoryDemo();//Bug,������ѭ������
	//return ::new MemoryDemo();//Bug,��������ι��캯��
	
}

void MemoryDemo::operator delete(void * ptr)
{
	cout << "operator delete" << endl;
	//::delete ptr;//right,��ʱptr��void*���Բ���ѭ�����ã�Ҳ������������������������˼������ӣ��о���̫�ã�
	//::operator delete(ptr);//right,����ȫ�ֵ�operator delete
	free(ptr);//right
	//delete (MemoryDemo*)ptr;//Bug,����ѭ������
	//::delete (MemoryDemo*)ptr;//Bug,�����������������
}


void* MemoryDemo::operator new[](std::size_t size)
{
	cout << "operator new[] " << size << endl;
	//return ::operator new(size);//right,����ȫ��operator new
	//return ::new char[size];//right,���˼�������
	//return ::operator new[](size);//right,Ĭ�ϵ���operator new(size)
	return malloc(size);
}
void MemoryDemo::operator delete[](void* ptr)
{
	cout << "operator delete[]" << endl;
	//::delete ptr;//right,��ʱptr��void*���Բ���ѭ�����ã�Ҳ������������������������˼������ӣ��о���̫�ã�
	//::operator delete(ptr);//right,����ȫ�ֵ�operator delete
	//::operator delete[](ptr);//right,Ĭ�ϵ���operator delete(size)
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