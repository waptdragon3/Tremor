#pragma once
#include <cstdint>
#include <stdexcept>

/// <summary>
/// Non-owning list
/// </summary>
/// <typeparam name="T"></typeparam>
template <class T>
class DynamicList
{
private:
	T* items;
	uint32_t numItems;
	uint32_t maxSize;

public:
	DynamicList(uint32_t size = 0);
	~DynamicList();
	void addItem(T& item);
	void removeIndex(uint32_t index);

	T& operator[](uint32_t index);
	void clear();
	void resize(uint32_t newSize);

private:
	void swap(uint32_t ind1, uint32_t ind2);

public:
	uint32_t length();
	uint32_t capacity();
};

template<class T>
DynamicList<T>::DynamicList(uint32_t size)
{
	items = new T[size];
	numItems = 0;
	maxSize = size;
}

template<class T>
DynamicList<T>::~DynamicList()
{
	delete[] items;
}

template<class T>
void DynamicList<T>::addItem(T& item)
{
	if (numItems + 1 > maxSize) resize(maxSize + 5);
	items[numItems] = item;
	numItems++;
}

template<class T>
void DynamicList<T>::removeIndex(uint32_t index)
{
	swap(numItems - 1, index);
	numItems--;
}

template<class T>
T& DynamicList<T>::operator[](uint32_t index)
{
	return items[index];
}

template<class T>
void DynamicList<T>::clear()
{
	numItems = 0;
}

template<class T>
void DynamicList<T>::resize(uint32_t newSize)
{
	if (newSize < numItems)
		throw std::runtime_error("DynamicList cannot be resized");
	T* tmp = new T[newSize];
	for (unsigned int i = 0; i < numItems; i++)
	{
		tmp[i] = items[i];
	}
	delete[] items;
	items = tmp;
	maxSize = newSize;
}

template<class T>
void DynamicList<T>::swap(uint32_t ind1, uint32_t ind2)
{
	T tmp = items[ind1];
	items[ind1] = items[ind2];
	items[ind2] = tmp;
}

template<class T>
uint32_t DynamicList<T>::length()
{
	return numItems;
}

template<class T>
uint32_t DynamicList<T>::capacity()
{
	return maxSize;
}
