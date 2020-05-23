#pragma once
#include <iostream>

using namespace std;

#ifndef STACKLINKEDLIST
#define STACKLINKEDLIST

template <class T> struct Node
{
	T data;
	Node<T>* pNext;
	Node(): data(0), pNext(NULL) {}
};

template <class T> class LinkedStack
{
	Node<T>* pHead;
	int size;
public:
	LinkedStack();
	~LinkedStack();
	void	Clear();
	bool	Push(T dataIn);
	Node<T>*Pop();
	void	GetTopElement(Node<T>*& dataOut);
	int		GetSize();
	bool	isEmpty();
	void	print2Console();
};

template <class T> LinkedStack<T>::LinkedStack()
{
	pHead = NULL;
	size = 0;
}
template <class T> LinkedStack<T>::~LinkedStack()
{
	Clear();
}

template <class T> bool LinkedStack<T>::Push(T dataIn)
{
	Node<T>* pNew = new Node<T>();
	if (!pNew)
	{
		return 0;
	}
	pNew->data = dataIn;
	pNew->pNext = pHead;
	pHead = pNew;
	++size;
	return 1;
}
template <class T> Node<T>* LinkedStack<T>::Pop()
{
	if (size == 0)
	{
		return 0;
	}
	Node<T>* dataOut = pHead;
	Node<T>* pDel = pHead;
	pHead = pHead->pNext;
	delete pDel;
	--size;
	return dataOut;
}

template <class T> void LinkedStack<T>::Clear()
{
	while (size > 0)
	{
		Pop();
	}
}

template <class T> void LinkedStack<T>::GetTopElement(Node<T>*& dataOut)
{
	dataOut = pHead;
}
template <class T> int LinkedStack<T>::GetSize()
{
	return size;
}
template <class T> bool LinkedStack<T>::isEmpty()
{
	return (pHead == NULL) ? 1 : 0;
}

template <class T> void LinkedStack<T>::print2Console()
{
	Node<T>* pLoc = pHead;
	int i = 0;
	while (pLoc != NULL)
	{
		cout << i++ << '\t' << pLoc->data << '\n';
		pLoc = pLoc->pNext;
	}
	cout << size;
}


#endif // STACKLINKEDLIST
