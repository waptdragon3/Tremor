#pragma once
#include <cstdint>
#include <stdexcept>

namespace W3D
{

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
		// main ctor
		explicit DynamicList(uint32_t size = 0);
		//copy constructor
		DynamicList(const DynamicList<T>& that);
		//Dtor
		~DynamicList();
		//copy asignment operator
		DynamicList<T>& operator=(const DynamicList<T>& other);


		void addItem(T& item);
		void addItems(DynamicList<T> list);
		void removeIndex(uint32_t index);

		T& operator[](uint32_t index);
		void clear();
		void resize(uint32_t newSize);

	private:
		void swap(uint32_t ind1, uint32_t ind2);

	public:
		uint32_t length() const;
		uint32_t capacity() const;
	};
}


template<class T>
W3D::DynamicList<T>::DynamicList(uint32_t size)
{
	items = new T[size];
	numItems = 0;
	maxSize = size;
}

template<class T>
W3D::DynamicList<T>::DynamicList(const W3D::DynamicList<T>& that)
{
	numItems = that.numItems;
	maxSize = that.maxSize;

	items = new T[maxSize];

	//copy items
	std::memcpy(items, that.items, maxSize * sizeof(T));
}

template<class T>
W3D::DynamicList<T>::~DynamicList()
{
	delete[] items;
}

template<class T>
W3D::DynamicList<T>& W3D::DynamicList<T>::operator=(const W3D::DynamicList<T>& other)
{
	//protect against self-assignment
	if (this != &other)
	{
		//1 allocate new memory and make copy of elements
		T* new_items = new T[other.maxSize];
		std::memcpy(new_items, other.items, other.maxSize * sizeof(T));

		//2 delete old memory
		delete[] items;

		//3 assign new memory
		items = new_items;
		numItems = other.numItems;
		maxSize = other.maxSize;
	}
	return *this;
}

template<class T>
void W3D::DynamicList<T>::addItem(T& item)
{
	if (numItems + 1 > maxSize) resize(maxSize + 5);
	items[numItems] = item;
	numItems++;
}

template<class T>
void W3D::DynamicList<T>::addItems(DynamicList<T> list)
{
	//resize all at once, instead of per item
	if (this->numItems + list.numItems > maxSize)
	{
		resize(this->numItems + list.numItems);
	}
	for (unsigned int i = 0; i < list.numItems; i++)
	{
		items[numItems] = list[i];
		numItems++;
	}
}

template<class T>
void W3D::DynamicList<T>::removeIndex(uint32_t index)
{
	swap(numItems - 1, index);
	numItems--;
}

template<class T>
T& W3D::DynamicList<T>::operator[](uint32_t index)
{
	return items[index];
}

template<class T>
void W3D::DynamicList<T>::clear()
{
	numItems = 0;
}

template<class T>
void W3D::DynamicList<T>::resize(uint32_t newSize)
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
void W3D::DynamicList<T>::swap(uint32_t ind1, uint32_t ind2)
{
	T tmp = items[ind1];
	items[ind1] = items[ind2];
	items[ind2] = tmp;
}

template<class T>
uint32_t W3D::DynamicList<T>::length() const
{
	return numItems;
}

template<class T>
uint32_t W3D::DynamicList<T>::capacity() const
{
	return maxSize;
}
