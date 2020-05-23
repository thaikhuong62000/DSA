#pragma once
#include  <iostream>


#ifndef HEADER
#define HEADER
class dynamicArray
{
private:
	int size;
	int capacity;
	int* storage;
public:
	dynamicArray();
	dynamicArray(int Capacity);
	~dynamicArray();
	void set(int index, int value);
	int get(int index);
	void pack();
	void trim();
	void setCapacity(int newCapacity);
	void ensureCapacity(int minCapacity);
	bool checkRange(int index);
	void insertAt(int index,int value);
	void removeAt(int index);
	void print();
	void printAll();
};
dynamicArray::dynamicArray()
{
	capacity = 10;
	size = 0;
	storage = new int[capacity];
}
dynamicArray::dynamicArray(int Capacity)
{
	capacity = Capacity;
	size = 0;
	storage = new int[capacity];
}
dynamicArray::~dynamicArray()
{
	delete[] storage;
}
void dynamicArray::set(int index, int value)
{
	if (checkRange(index))
	{
		storage[index] = value;
	}
	else cout << "Set fail!";
}
int dynamicArray::get(int index)
{
	if (checkRange(index))
	{
		return storage[index];
	}
	cout << "Get fail!";
	return 0;
}
void dynamicArray::pack()
{
	if (size <= capacity / 2)
	{
		int newCapacity = capacity * 3 / 2 + 1;
		setCapacity(newCapacity);
	}
}
void dynamicArray::trim()
{
	int newCapacity = size;
	setCapacity(newCapacity);
}
void dynamicArray::setCapacity(int newCapacity)
{
	int* newStorage = new int[newCapacity];
	memcpy(newStorage, storage, sizeof(int) * size);
	capacity = newCapacity;
	delete[] storage; //Test
	storage = newStorage;
}
void dynamicArray::ensureCapacity(int minCapacity)
{
	if (minCapacity > capacity)
	{
		int newCapacity = (capacity * 3) / 2 + 1;
		if (newCapacity < minCapacity)
		{
			newCapacity = minCapacity;
		}
		setCapacity(newCapacity);
	}
}
bool dynamicArray::checkRange(int index)
{
	if ((index < 0) || (index >= size))
	{
		return 0;
	}
	return 1;
}
void dynamicArray::insertAt(int index,int value)
{
	if (!checkRange(index))
	{
		cout << "Insert Error!";
	}
	ensureCapacity(size + 1);
	int moveCount = size - index;
	if (moveCount != 0)
		memmove(storage + index + 1, storage + index, sizeof(int) * moveCount);
	storage[index] = value;
	++size;
}
void dynamicArray::removeAt(int index)
{
	if (!checkRange(index))
	{
		cout << "Remove Error!";
	}
	int moveCount = size - index - 1;
	if (moveCount > 0)
		memmove(storage + index, storage + index + 1, sizeof(int) * moveCount);
	--size;
	pack();
}

void dynamicArray::print()
{
	for (int i = 0; i < size; i++)
	{
		cout << i << "  " << storage[i] << '\n';
	}
}
void dynamicArray::printAll()
{
	cout << '\n';
	cout << "Capacity: " << capacity << '\n';
	cout << "Size:	   " << size;
}
#endif // !HEADER
