#pragma once
#include <iostream>

using namespace std;

#ifndef LINKEDLIST
#define LINKEDLIST
template <class Type> struct Node
{
	Type data;
	Node<Type>* link;
	Node(): data(0), link(NULL){}
	Node(int dataIn) : data(dataIn), link(NULL){}
};

template <class List_ItemType> class LinkList
{
	Node<List_ItemType>* head;
	int count;
protected:
	int insertNode(Node<List_ItemType>* pPre, List_ItemType value);
	List_ItemType deleteNode(Node<List_ItemType>* pPre, Node<List_ItemType>* pLoc);
	int search(List_ItemType value, Node<List_ItemType> * &pPre, Node<List_ItemType>*& pLoc);
public:
	LinkList();
	~LinkList();
	void insertFirst(List_ItemType value);
	void insertLast(List_ItemType value);
	int insertItem(List_ItemType value,int index);
	void deleteFirst();
	void deleteLast();
	int deleteItem(int index);
	int getItem(int index, List_ItemType &dataOut);
	LinkList<List_ItemType>* Clone();
	void reverse();
	void print2Console();
	void clear();
};
template <class List_ItemType> LinkList<List_ItemType>::LinkList()
{
	this->head = nullptr;
	this->count = 0;
}
template <class List_ItemType> LinkList<List_ItemType>::~LinkList()
{
	this->clear();
}
template <class List_ItemType> int LinkList<List_ItemType>::insertNode(
	Node<List_ItemType>* pPre,
	List_ItemType value)
{
	Node<List_ItemType>* pNew = new Node<List_ItemType>();
	if (pNew == NULL)
	{
		return 0;
	}
	pNew->data = value;
	if (pPre == NULL)
	{
		pNew->link = this->head;
		this->head = pNew;
	}
	else
	{
		pNew->link = pPre->link;
		pPre->link = pNew;
	}
	this->count++;
	return 1;
}
template <class List_ItemType> List_ItemType LinkList<List_ItemType>::deleteNode(
	Node<List_ItemType>* pPre,
	Node<List_ItemType>* pLoc)
{
	List_ItemType result = pLoc->data;
	if (pPre == NULL)
	{
		this->head = pLoc->link;
	}
	else
	{
		pPre->link = pLoc->link;
	}
	this->count--;
	delete pLoc;
	return result;
}
template <class List_ItemType> int LinkList<List_ItemType>::search(
	List_ItemType value,
	Node<List_ItemType>*& pPre,
	Node<List_ItemType>*& pLoc)
{
	pPre = NULL;
	pLoc = this->head;
	while (pLoc != NULL && pLoc->data != value)
	{
		pPre = pLoc;
		pLoc = pLoc->link;
	}
	return (pLoc != NULL);
}
template <class List_ItemType> void LinkList<List_ItemType>::clear()
{
	if (this->head != NULL)
	{
		Node<List_ItemType>* pDel = new Node<List_ItemType>();
		while (this->head != NULL)
		{
			delete pDel;
			pDel = this->head;
			this->head = this->head->link;
		}
		delete pDel;
	}
	this->count = 0;
}
template <class List_ItemType> void LinkList<List_ItemType>::insertFirst(List_ItemType value)
{
	insertNode(nullptr, value);
}
template <class List_ItemType> void LinkList<List_ItemType>::insertLast(List_ItemType value)
{
	Node<List_ItemType>* pPre = new Node<List_ItemType>();
	Node<List_ItemType>* pLoc = new Node<List_ItemType>();
	pPre = this->head;
	if (pPre != NULL)
	{
		pLoc = pPre->link;
		while (pLoc != NULL)
		{
			pPre = pPre->link;
			pLoc = pLoc->link;
		}
		insertNode(pPre, value);
	}
	else insertFirst(value);
}
template <class List_ItemType> int LinkList<List_ItemType>::insertItem(List_ItemType value, int index)
{
	if (index >= this->count || index < 0)
	{
		return 0;
	}
	else if (index == 0)
	{
		insertFirst(value);
	}
	else
	{
		int temp = 1;
		Node<List_ItemType>* pPre = new Node<List_ItemType>();
		pPre = this->head;
		while (temp < index)
		{
			pPre = pPre->link;
			temp++;
		}
		insertNode(pPre, value);
	}
	return 1;
}
template <class List_ItemType> void LinkList<List_ItemType>::deleteFirst()
{
	deleteNode(nullptr, this->head);
}
template <class List_ItemType> void LinkList<List_ItemType>::deleteLast()
{
	Node<List_ItemType>* pPre = new Node<List_ItemType>();
	Node<List_ItemType>* pLoc = new Node<List_ItemType>();
	if (this->head != NULL)
	{
		pPre = this->head;
		pLoc = pPre->link;
		while (pLoc->link != NULL)
		{
			pPre = pLoc;
			pLoc = pLoc->link;
		}
		deleteNode(pPre, pLoc);
	}
}
template <class List_ItemType> int LinkList<List_ItemType>::deleteItem(int index)
{
	if (index >= this->count || index < 0)
	{
		return 0;
	}
	else if (index == 0)
	{
		deleteFirst();
	}
	else
	{
		int temp = 1;
		Node<List_ItemType>* pPre = new Node<List_ItemType>();
		pPre = this->head;
		while (temp < index)
		{
			pPre = pPre->link;
			temp++;
		}
		deleteNode(pPre, pPre->link);
	}
	return 1;
}
template <class List_ItemType> int LinkList<List_ItemType>::getItem(int index, List_ItemType& dataOut)
{
	if (index >= this->count || index < 0)
	{
		return 0;
	}
	else
	{
		int temp = 0;
		Node<List_ItemType>* pLoc = new Node<List_ItemType>();
		pLoc = this->head;
		while (temp < index)
		{
			pLoc = pLoc->link;
			temp++;
		}
		dataOut = pLoc->data;
		return 1;
	}
}
template <class List_ItemType> LinkList<List_ItemType>* LinkList<List_ItemType>::Clone()
{
	Node<List_ItemType>* pLoc = new Node<List_ItemType>();
	LinkList<List_ItemType>* newLinkList = new LinkList<List_ItemType>();
	pLoc = this->head;
	while (pLoc != NULL)
	{
		newLinkList->insertLast(pLoc->data);
		pLoc = pLoc->link;
	}
	return newLinkList;
}
template <class List_ItemType> void LinkList<List_ItemType>::print2Console()
{
	Node<List_ItemType>* pLoc = new Node<List_ItemType>();
	int temp = 0;
	pLoc = this->head;
	while (pLoc != NULL)
	{
		cout << "Index: " << temp << '\t' << "Value: " << pLoc->data << '\n';
		++temp;
		pLoc = pLoc->link;
	}
	delete pLoc;
}
template <class List_ItemType> void LinkList<List_ItemType>::reverse()
{
	Node<List_ItemType>* p1 = new Node<List_ItemType>();
	Node<List_ItemType>* p2 = new Node<List_ItemType>();
	Node<List_ItemType>* p3 = new Node<List_ItemType>();
	if (this->head != NULL)
	{
		if (this->head->link != NULL)
		{
			p1 = this->head;
			p2 = p1->link;
			p3 = p2->link;
			p1->link = NULL;
			while ((p1 != NULL) && (p2 != NULL) && (p3 != NULL))
			{
				p2->link = p1;
				p1 = p3->link;
				if (p1 == NULL)
					break;
				p3->link = p2;
				p2 = p1->link;
				if (p2 == NULL)
					break;
				p1->link = p3;
				p3 = p2->link;
				if (p3 == NULL)
					break;
			}
			if (p1 == NULL)
			{
				this->head = p3;
				this->head->link = p2;
			}
			else if (p2 == NULL)
			{
				this->head = p1;
				this->head->link = p3;
			}
			else if (p3 == NULL)
			{
				this->head = p2;
				this->head->link = p1;
			}
		}
	}
}

#endif // !LINKEDLIST
