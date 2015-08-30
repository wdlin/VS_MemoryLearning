#ifndef _SMART_POINTER_H_
#define _SMART_POINTER_H_
#include <atomic>
#include <iostream>

template<class T>
class SmartPointer
{
public:
	SmartPointer();
	SmartPointer(T*);
	SmartPointer(const SmartPointer<T>&);
	SmartPointer& operator=(const SmartPointer<T>& rhs);
	~SmartPointer();
	T& operator*() const;
	T* operator->() const;
	T* get();
	void reset(T*);
private:
	std::atomic<int>* pCount;
	T* ptr;
};

template<class T>
SmartPointer<T>::SmartPointer() :SmartPointer(nullptr)
{
}

template<class T>
SmartPointer<T>::SmartPointer(T* tptr)
{
	pCount = new std::atomic<int>;
	*pCount = 1;
	ptr = tptr;
}

template<class T>
SmartPointer<T>::SmartPointer(const SmartPointer<T>& sp)
{
	ptr = sp.ptr;
	pCount = sp.pCount;
	(*pCount)++;
}

template<class T>
SmartPointer<T>& SmartPointer<T>::operator=(const SmartPointer<T>& rhs)
{
	if (rhs.ptr == ptr)
		return *this;
	else
	{
		(*pCount)--;
		if (*pCount <= 0)
		{
			delete ptr;
			delete pCount;
		}
		ptr = rhs.ptr;
		pCount = rhs.pCount;
		(*pCount)++;
		return *this;
	}
	
}

template<class T>
SmartPointer<T>::~SmartPointer()
{
	(*pCount)--;
	if (*pCount <= 0)
	{
		delete ptr;
		delete pCount;
	}
		
}

template<class T>
T& SmartPointer<T>::operator*() const
{
	return *ptr;
}

template<class T>
T* SmartPointer<T>::operator->() const
{
	return ptr;
}

template<class T>
T* SmartPointer<T>::get()
{
	return ptr;
}
template<class T>
void SmartPointer<T>::reset(T* tptr)
{
	(*pCount)--;
	if (*pCount <= 0)
	{
		delete ptr;
		ptr = tptr;
		*pCount = 1;
	}
	else
	{
		ptr = tptr;
		pCount = std::atomic<int>;
		*pCount = 1;
	}
		
}
#endif