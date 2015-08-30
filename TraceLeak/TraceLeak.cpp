#include "TraceLeak.h"
#include <memory>
#include <cstdio>
#include <iostream>
#include <fstream>
#include <mutex>
namespace TraceLeak{
/*
存放分配信息的节点类
成员中尽可能不使用对象，否则有可能死循环
*/
typedef struct PointerNode
{
	PointerNode() :pointer(nullptr), next(nullptr), file(nullptr), line(0){}
	void* pointer;
	struct PointerNode* next;
	const char* file;
	int line;
	void* operator new(size_t size);
	void operator delete(void* ptr);
}PointerNode;
//重载节点类的operator new，防止使用全局的
void* PointerNode::operator new(size_t size)
{
	return malloc(size);
}
//重载节点类的operator delete，防止使用全局的
void PointerNode::operator delete(void * ptr)
{
	free(ptr);
}
//存放分配信息的全局链表头
PointerNode* pointerNodeHead = new PointerNode;
//读写互斥
std::mutex mut;

/*
void init()
{
	pointerNodeHead = new PointerNode;
	pointerNodeHead->next = nullptr;
	pointerNodeHead->pointer = nullptr;
}
*/

//增加分配信息
void addNode(void* ptr, const char* file, int line)
{
	if (ptr != nullptr)
	{
		std::lock_guard<std::mutex> lock(mut);
		PointerNode* pn = new PointerNode;
		pn->pointer = ptr;
		pn->file = file;
		pn->line = line;
		pn->next = pointerNodeHead;
		pointerNodeHead = pn;
	}
}
//删除分配信息
void removeNode(void* ptr)
{
	if (ptr != nullptr)
	{
		std::lock_guard<std::mutex> lock(mut);
		PointerNode* temp = pointerNodeHead;
		if (pointerNodeHead->pointer == ptr)
		{
			pointerNodeHead = pointerNodeHead->next;
			delete temp;
			return;
		}
		while (temp->next != nullptr)
		{
			if (temp->next->pointer == ptr)
			{
				PointerNode* p = temp->next;
				temp->next = temp->next->next;
				delete p;
				break;
			}
			temp = temp->next;
		}
	}
}
//打印信息
void print()
{
	std::lock_guard<std::mutex> lock(mut);
	if (pointerNodeHead->next == nullptr)
	{
		printf("no memory leak ...");
		return;
	}
	printf("allocated memory without release:\n");
	PointerNode* temp = pointerNodeHead;
	while (temp->next != nullptr)
	{
		printf("file:%s--line:%d\n",temp->file,temp->line);
		temp = temp->next;
	}
}
//输出信息
void output(const char* filename)
{
	
	std::ofstream output(filename);
	std::lock_guard<std::mutex> lock(mut);
	char* str;
	if (pointerNodeHead->next == nullptr)
	{
		str = "no memory leak ...";
		output.write(str,strlen(str));
		output.close();
		return;
	}

	str = "allocated memory without release:\n";
	output.write(str, strlen(str));

	PointerNode* temp = pointerNodeHead;
	while (temp->next != nullptr)
	{
		char buf[500];
		sprintf_s(buf,"file:%s--line:%d\n", temp->file, temp->line);
		output.write(buf, strlen(buf));
		temp = temp->next;
	}
	output.close();
}

}
//重载全局的operator new 和operator delete
using namespace TraceLeak;
void* operator new(size_t size, const char* file, int line)
{
	void* ptr = malloc(size);
	addNode(ptr,file,line);
	return ptr;
}
void operator delete(void* ptr)
{
	free(ptr);
	removeNode(ptr);
}
void* operator new[](size_t size, const char*file, int line)
{
	void* ptr = malloc(size);
	addNode(ptr, file, line);
	return ptr;
}
void operator delete[](void* ptr)
{
	free(ptr);
	removeNode(ptr);
}

