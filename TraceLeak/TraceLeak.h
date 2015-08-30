#ifndef _TRACE_LEAK_H_
#define _TRACE_LEAK_H_

void* operator new(size_t size,const char* file,int line);
void operator delete(void* ptr);
void* operator new[](size_t size, const char*file, int line);
void operator delete[](void* ptr);

namespace TraceLeak{
	//void init();
	void addNode(void* ptr, const char* file, int line);
	void removeNode(void* ptr);
	void print();
	void output(const char* filename);
}
#endif

