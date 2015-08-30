#include "TraceLeak.h"
#include <memory>
#include <cstdio>
#include <iostream>
#include <fstream>
#include <mutex>
namespace TraceLeak{
/*
��ŷ�����Ϣ�Ľڵ���
��Ա�о����ܲ�ʹ�ö��󣬷����п�����ѭ��
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
//���ؽڵ����operator new����ֹʹ��ȫ�ֵ�
void* PointerNode::operator new(size_t size)
{
	return malloc(size);
}
//���ؽڵ����operator delete����ֹʹ��ȫ�ֵ�
void PointerNode::operator delete(void * ptr)
{
	free(ptr);
}
//��ŷ�����Ϣ��ȫ������ͷ
PointerNode* pointerNodeHead = new PointerNode;
//��д����
std::mutex mut;

/*
void init()
{
	pointerNodeHead = new PointerNode;
	pointerNodeHead->next = nullptr;
	pointerNodeHead->pointer = nullptr;
}
*/

//���ӷ�����Ϣ
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
//ɾ��������Ϣ
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
//��ӡ��Ϣ
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
//�����Ϣ
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
//����ȫ�ֵ�operator new ��operator delete
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

