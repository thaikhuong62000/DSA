/* Created by Nguyen Duc Dung on 2019-09-03.
 * =========================================================================================
 * Name        : dsaLib.h
 * Author      : Duc Dung Nguyen
 * Email       : nddung@hcmut.edu.vn
 * Copyright   : Faculty of Computer Science and Engineering - HCMUT
 * Description : The data structure library for Assignment 1
 * Course      : Data Structure and Algorithms - Fall 2019
 * =========================================================================================
 */

#ifndef DSA191_A1_DSALIB_H
#define DSA191_A1_DSALIB_H
#include <string>
#include <stdio.h>
#include <string.h>
#include <iostream>

using namespace std;

class DSAException {
	int     _error;
	string  _text;
public:

	DSAException() : _error(0), _text("Success") {}
	DSAException(int err) : _error(err), _text("Unknown Error") {}
	DSAException(int err, const char* text) : _error(err), _text(text) {}

	int getError() { return _error; }
	string& getErrorText() { return _text; }
};

template <class T>
struct L1Item {
	T data;
	L1Item<T>* pNext;
	L1Item() : pNext(NULL) {}
	L1Item(T& a) : data(a), pNext(NULL) {}
};

template <class T>
class L1List {
	L1Item<T>* _pHead;// The head pointer of linked list
	size_t      _size;// number of elements in this list
	int insertItem(L1Item<T>* pPre, T value);
	T deleteItem(L1Item<T>* pPre, L1Item<T>* pLoc);
public:
	L1List() : _pHead(NULL), _size(0) {}
	~L1List() { this->clean(); }
	void    clean();
	bool    isEmpty() {
		return _pHead == NULL;
	}
	size_t  getSize() {
		return _size;
	}

	T& at(int i);// give the reference to the element i-th in the list
	T& operator[](int i);// give the reference to the element i-th in the list

	bool    find(T& a, int& idx);// find an element similar to a in the list. Set the found index to idx, set idx to -1 if failed. Return true if success.
	int     insert(int i, T& a);// insert an element into the list at location i. Return 0 if success, -1 otherwise
	int     remove(int i);// remove an element at position i in the list. Return 0 if success, -1 otherwise.

	int     push_back(T& a);// insert to the end of the list
	int     insertHead(T& a);// insert to the beginning of the list

	int     removeHead();// remove the beginning element of the list
	int     removeLast();// remove the last element of the list

	void    reverse();

	void    traverse(void (*op)(T&)) {

	}
	void    traverse(void (*op)(T&, void*), void* pParam) {
		// TODO: Your code goes here
	}

	void p2C();
};

/// Insert item to the end of the list
/// Return 0 if success, -1 otherwise
template <class T>
int L1List<T>::push_back(T& a) {
	// TODO: Your code goes here
	L1Item<T>* pPre = new L1Item<T>();
	L1Item<T>* pLoc = new L1Item<T>();
	pPre = this->_pHead;
	if (pPre != NULL)
	{
		pLoc = pPre->pNext;
		while (pLoc != NULL)
		{
			pPre = pPre->pNext;
			pLoc = pLoc->pNext;
		}
		insertItem(pPre, a);
	}
	else insertHead(a);
	return 0;
}

/// Insert item to the front of the list
/// Return 0 if success, -1 otherwise
template <class T>
int L1List<T>::insertHead(T& a) {
	return insertItem(nullptr, a);
}

/// Remove the first item of the list
/// Return 0 if success, -1 otherwise
template <class T>
int L1List<T>::removeHead() {
	deleteItem(nullptr, this->_pHead);
	return 0;
}

/// Remove the last item of the list
/// Return 0 if success, -1 otherwise
template <class T>
int L1List<T>::removeLast() {
	L1Item<T>* pPre = new L1Item<T>();
	L1Item<T>* pLoc = new L1Item<T>();
	if (this->_pHead != NULL)
	{
		pPre = this->_pHead;
		pLoc = pPre->pNext;
		while (pLoc->pNext != NULL)
		{
			pPre = pLoc;
			pLoc = pLoc->pNext;
		}
		deleteItem(pPre, pLoc);
	}
	return 0;
}
template <class T> int L1List<T>::insertItem(L1Item<T>* pPre, T value)
{
	L1Item<T>* pNew = new L1Item<T>();
	if (pNew == NULL)
	{
		return -1;
	}
	pNew->data = value;
	if (pPre == NULL)
	{
		pNew->pNext = this->_pHead;
		this->_pHead = pNew;
	}
	else
	{
		pNew->pNext = pPre->pNext;
		pPre->pNext = pNew;
	}
	this->_size++;
	return 0;
}
template <class T> T L1List<T>::deleteItem(L1Item<T>* pPre, L1Item<T>* pLoc)
{
	T result = pLoc->data;
	if (pPre == NULL)
	{
		this->_pHead = pLoc->pNext;
	}
	else
	{
		pPre->pNext = pLoc->pNext;
	}
	this->_size--;
	delete pLoc;
	return result;
}
template <class T> void L1List<T>::clean()
{
	if (this->_pHead != NULL)
	{
		L1Item<T>* pDel = new L1Item<T>();
		while (this->_pHead != NULL)
		{
			delete pDel;
			pDel = this->_pHead;
			this->_pHead = this->_pHead->pNext;
		}
		delete pDel;
	}
	this->_size = 0;
}
template <class T> T& L1List<T>::at(int i)
{
	if (i >= _size || i < 0)
	{
		throw(DSAException(5));
	}
	else if (i == 0)
	{
		return _pHead->data;
	}
	else
	{
		L1Item<T>* pLoc = new L1Item<T>();
		pLoc = this->_pHead;
		for (int j = 1; j < i; j++)
		{
			pLoc = pLoc->pNext;
		}
		return pLoc->data;
	}
}
template <class T> T& L1List<T>::operator[](int i)
{



}
template <class T> bool L1List<T>::find(T& a, int& idx)
{

	int temp = 0;
	L1Item<T>* pLoc = new L1Item<T>();
	pLoc = this->_pHead;
	while (pLoc->data != a)
	{
		pLoc = pLoc->pNext;
		temp++;
		if (pLoc == NULL)
		{
			break;
		}
	}
	if (pLoc != NULL)
	{
		a = pLoc->data;
		idx = temp;
	}
	else
	{
		idx = -1;
	}
	delete pLoc;
	return 1;
}
template <class T> int L1List<T>::insert(int i, T& a)
{
	if (i < 0 || i >= _size)
	{
		return -1;
	}
	else if (i == 0)
	{
		insertHead(a);
	}
	else
	{
		L1Item<T>* pPre = new L1Item<T>();
		pPre = this->_pHead;
		for (int j = 1; j < i; j++)
		{
			pPre = pPre->pNext;
		}
		return insertItem(pPre, a);
	}
}
template <class T> int L1List<T>::remove(int i)
{
	if (i < 0 || i >= _size)
	{
		return -1;
	}
	else if (i == 0)
	{
		return removeHead();
	}
	else
	{
		L1Item<T>* pPre = new L1Item<T>();
		pPre = this->_pHead;
		for (int j = 1; j < i; j++)
		{
			pPre = pPre->pNext;
		}
		deleteItem(pPre, pPre->pNext);
		return 0;
	}
}
template <class T> void L1List<T>::reverse()
{
	L1Item<T>* p1 = new L1Item<T>();
	L1Item<T>* p2 = new L1Item<T>();
	L1Item<T>* p3 = new L1Item<T>();
	if (this->_pHead != NULL)
	{
		if (this->_pHead->pNext != NULL)
		{
			p1 = this->_pHead;
			p2 = p1->pNext;
			p3 = p2->pNext;
			p1->pNext = NULL;
			while ((p1 != NULL) && (p2 != NULL) && (p3 != NULL))
			{
				p2->pNext = p1;
				p1 = p3->pNext;
				if (p1 == NULL)
					break;
				p3->pNext = p2;
				p2 = p1->pNext;
				if (p2 == NULL)
					break;
				p1->pNext = p3;
				p3 = p2->pNext;
				if (p3 == NULL)
					break;
			}
			if (p1 == NULL)
			{
				this->_pHead = p3;
				this->_pHead->pNext = p2;
			}
			else if (p2 == NULL)
			{
				this->_pHead = p1;
				this->_pHead->pNext = p3;
			}
			else if (p3 == NULL)
			{
				this->_pHead = p2;
				this->_pHead->pNext = p1;
			}
		}
	}
}
template <class T> void L1List<T>::p2C()
{
	L1Item<T>* pLoc = new L1Item<T>();
	int temp = 0;
	pLoc = this->_pHead;
	cout << '\n';
	while (pLoc != NULL)
	{
		cout << "Index:  " << temp << '\t' << "Value: " << pLoc->data << '\n';
		++temp;
		pLoc = pLoc->pNext;
	}
	cout <<  '\t' << _size << '\t' << _pHead;
	delete pLoc;
}
#endif //DSA191_A1_DSALIB_H
