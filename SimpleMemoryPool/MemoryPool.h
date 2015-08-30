#ifndef _MEMORY_POOL_H_
#define _MEMORY_POOL_H_

template<class T>
class MemoryPool
{
public:
	MemoryPool(size_t num = 32);
	~MemoryPool();
	void* allocate();
	void free(void* ptr);
private:
	void expand(int num = 32);
	MemoryPool<T>* freeList;
};

template<class T>
MemoryPool<T>::MemoryPool(size_t num = 16)
{
	expand(num);
}

template<class T>
MemoryPool<T>::~MemoryPool()
{
	if (freeList == nullptr)return;
	MemoryPool<T>* item;
	while (freeList != nullptr)
	{
		item = freeList;
		freeList = freeList->freeList;
		::free(item);
	}
}

template<class T>
void* MemoryPool<T>::allocate()
{
	if (freeList == nullptr)
	{
		expand();
	}
	MemoryPool<T>* pHead = freeList;
	freeList = freeList->freeList;
	return pHead;
}

template<class T>
void MemoryPool<T>::free(void* ptr)
{
	MemoryPool<T>* pHead = static_cast<MemoryPool<T>*>(ptr);
	pHead->freeList = freeList;
	freeList = pHead;
}

template<class T>
void MemoryPool<T>::expand(int num)
{
	if (num <= 0)return;
	size_t size = sizeof(T) > sizeof(MemoryPool<T>) ? sizeof(T) : sizeof(MemoryPool<T>);
	MemoryPool<T>* item = static_cast<MemoryPool<T>*>(static_cast<void*>(new char[size]));
	freeList = item;
	freeList->freeList = nullptr;
	for (int i = 0; i < num - 1; i++)
	{
		item = static_cast<MemoryPool<T>*>(static_cast<void*>(new char[size]));
		item->freeList = freeList;
		freeList = item;
	}
	
}



#endif