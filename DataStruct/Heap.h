#pragma once
#include <iostream>
using namespace std;

#ifndef ARRAYHEAP
#define ARRAYHEAP

template<typename T> void swap(T& a, T& b)
{
	T temp = b;
	b = a;
	a = temp;
}
template<typename T> void reHeapUp(T*& heapArray, int Position)
{
	if (Position > 0)
	{
		int Parent = (Position - 1) / 2;
		if (heapArray[Position] > heapArray[Parent])
		{
			swap(heapArray[Position], heapArray[Parent]);
			reHeapUp(heapArray, Parent);
		}
	}
}
template<typename T> void reHeapDown(T*& heapArray, int Position, int LastPosition)
{
	int LeftChild  = Position * 2 + 1;
	int RightChild = Position * 2 + 2;
	int LargeChild;
	if (LeftChild <= LastPosition)
	{
		if (RightChild <= LastPosition && heapArray[RightChild] > heapArray[LeftChild])
		{
			LargeChild = RightChild;
		}
		else LargeChild = LeftChild;
		if (heapArray[LargeChild] > heapArray[LastPosition])
		{
			swap(heapArray[LargeChild] , heapArray[LastPosition]);
			reHeapDown(heapArray, LargeChild, LastPosition);
		}
	}
}
template<typename T> void buildHeap(T*& Array, int size)
{
	int walker = 1;
	while (walker < size)
	{
		reHeapUp(Array, walker);
		++walker;
	}
}
template<typename T> bool insertHeap(T*& heapArray, int size, int& LastPosition, T data)
{
	if (LastPosition < size - 1)
	{
		++LastPosition;
		heapArray[LastPosition] = data;
		reHeapUp(heapArray, LastPosition);
		return 1;
	}
	return 0;
}
template<typename T> bool deleteHeap(T*& heapArray, int& LastPosition, T& dataOut)
{
	if (LastPosition == -1)
	{
		return 0;
	}
	dataOut = heapArray[0];
	heapArray[0] = heapArray[LastPosition];
	--LastPosition;
	reHeapDown(heapArray, 0, LastPosition);
	return 1;
}
template<typename T> bool selectK(T*& heapArray, int& k, int& LastPosition, int& holdOut)
{
	if (k > LastPosition + 1)
	{
		return 0;
	}
	int i = 1;
	int originalSize = k + 1;
	while (i < k)
	{
		int dataOut;
		deleteHeap(heapArray, LastPosition, dataOut);
		heapArray[LastPosition + 1] = dataOut;
		++i;
	}
	holdOut = heapArray[0];
	while (LastPosition < originalSize)
	{
		++LastPosition;
		reHeapUp(heapArray, LastPosition);
	}
	return 1;
}

#endif // !ARRAYHEAP

