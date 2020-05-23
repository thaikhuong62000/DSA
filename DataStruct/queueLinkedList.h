#pragma once

#include <iostream>

using namespace std;

#ifndef QUEUELINKEDLIST
#define QUEUELINKEDLIST

template <class T> struct Node
{
	T data;
	Node<T>* pNext;
	Node() : data(0), pNext(NULL) {}
};

template <class T> class LinkedQueue
{
	Node<T>* pFront, *pRear;
	int size;
public:
	LinkedQueue();
	~LinkedQueue();
	bool	enQueue(T dataIn);
	Node<T>*deQueue();
	void	Clear();
	int		GetSize();
	bool	isEmpty();
	void	GetQueueFront(Node<T>*& dataOut);
	void	GetQueueRear(Node<T>*& dataOut);
	void	print2Console();
};

template <class T> LinkedQueue<T>::LinkedQueue()
{
	pFront = NULL;
	pRear = NULL;
	size = 0;
}
template <class T> LinkedQueue<T>::~LinkedQueue()
{
	Clear();
}

template <class T> bool LinkedQueue<T>::enQueue(T dataIn)
{
	Node<T>* pNew = new Node<T>();
	if (!pNew)
	{
		return 0;
	}
	pNew->data = dataIn;
	if (size == 0)
	{
		pFront = pNew;
	}
	else
	{
		pRear->pNext = pNew;
	}
	pRear = pNew;
	++size;
	return 1;
}
template <class T> Node<T>* LinkedQueue<T>::deQueue()
{
	if (size == 0)
	{
		return 0;
	}
	Node<T>* dataOut = pFront;
	Node<T>* pDel = pFront;
	if (size == 1)
	{
		pRear = nullptr;
	}
	pFront = pFront->pNext;
	delete pDel;
	--size;
	return dataOut;
}

template <class T> void LinkedQueue<T>::Clear()
{
	while (size > 0)
	{
		deQueue();
	}
}

template <class T> bool LinkedQueue<T>::isEmpty()
{
	return (pFront == NULL) ? 1 : 0;
}
template <class T> int LinkedQueue<T>::GetSize()
{
	return size;
}
template <class T> void LinkedQueue<T>::GetQueueFront(Node<T>*& dataOut)
{
	dataOut = pFront;
}
template <class T> void LinkedQueue<T>::GetQueueRear(Node<T>*& dataOut)
{
	dataOut = pRear;
}

template <class T> void LinkedQueue<T>::print2Console()
{
	Node<T>* pLoc = pFront;
	int i = 0;
	while (pLoc != NULL)
	{
		cout << i++ << '\t' << pLoc->data << '\n';
		pLoc = pLoc->pNext;
	}
	cout << size;
}

#endif