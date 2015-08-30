#ifndef _MEMORY_DEMO_H_
#define _MEMORY_DEMO_H_
#include <new>
class MemoryDemo
{
public:
	MemoryDemo();
	virtual ~MemoryDemo();
	void* operator new(std::size_t size);
	void operator delete(void* ptr);
	void* operator new[](std::size_t size);
	void operator delete[](void* ptr);
	void* operator new(std::size_t size, const std::nothrow_t&);
	void operator delete(void* ptr,const std::nothrow_t&);
	void* operator new[](std::size_t size, const std::nothrow_t&);
	void operator delete[](void* ptr, const std::nothrow_t&);

	//重载有额外参数的
	void* operator new(std::size_t size,char* str);
	void operator delete(void* ptr, char* str);
	void* operator new[](std::size_t size, char* str);
	void operator delete[](void* ptr, char* str);

};
//继承后，也是可用的，与正常函数一样使用
class MemorySubClass :public MemoryDemo
{
public:
	MemorySubClass();
	virtual ~MemorySubClass();
};


#endif