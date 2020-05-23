#pragma once
#include <iostream>

using namespace std;

#ifndef BINARYSEARCHTREE
#define BINARYSEARCHTREE

template <class T> struct Node
{
	T data;
	Node<T>* pLeft, * pRight;
	Node(): data(0), pLeft(NULL), pRight(NULL) {}
	Node(int dataIn) : data(dataIn), pLeft(NULL), pRight(NULL) {}
};

template <class T> class BinarySearchTree
{
	Node<T>* pRoot;

	bool		insertNode(Node<T>*& pRoot, T dataIn);
	Node<T>*	deleteNode(Node<T>* pDel);
	Node<T>*	minOfRightBranch(Node<T>* pRoot);

	Node<T>*	Search(Node<T>* pRoot, T key, int& isRight);
	Node<T>*	Search(Node<T>* pRoot, T key);

	void		ClearRecursion(Node<T>* pRoot);
	void		Print(Node<T>* pRoot);
public:
	BinarySearchTree();
	~BinarySearchTree();

	Node<T>*	Search(T key);

	bool		insertNode(T dataIn);
	bool		deleteNode(T info);

	void		Clear();
	void		Print();


};

template <class T>			BinarySearchTree<T>::BinarySearchTree()
{
	pRoot = NULL;
}
template <class T>			BinarySearchTree<T>::~BinarySearchTree()
{
	Clear();
}

template <class T> Node<T>* BinarySearchTree<T>::Search(Node<T>* pRoot, T key, int& isRight)
{
	if (pRoot == NULL)
	{
		return NULL;
	}
	if (pRoot->pLeft != NULL)
	{
		if (pRoot->pLeft->data == key)
		{
			isRight = 0;
			return pRoot;
		}
	}
	else if (pRoot->pRight != NULL)
	{
		if (pRoot->pRight->data == key)
		{
			isRight = 1;
			return pRoot;
		}
	}
	if (pRoot->data > key)
	{
		return Search(pRoot->pLeft, key, isRight);
	}
	else if (pRoot->data < key)
	{
		return Search(pRoot->pRight, key, isRight);
	}
	else
	{
		isRight = -1;
		return pRoot;
	}
}
template <class T> Node<T>* BinarySearchTree<T>::Search(Node<T>* pRoot, T key)
{
	if (pRoot == NULL)
	{
		return NULL;
	}
	if (pRoot->data > key)
	{
		return Search(pRoot->pLeft, key);
	}
	else if (pRoot->data < key)
	{
		return Search(pRoot->pRight, key);
	}
	else return pRoot;
}
template <class T> Node<T>* BinarySearchTree<T>::Search(T key)
{
	return Search(pRoot, key);
}

template <class T> bool		BinarySearchTree<T>::insertNode(Node<T>*& pRoot, T dataIn)
{
	if (pRoot == NULL)
	{
		Node<T>* pNew = new Node<T>(dataIn);
		if (pNew == NULL) return 0;
		pRoot = pNew;
	}
	else if (pRoot->data < dataIn)
	{
		insertNode(pRoot->pRight, dataIn);
	}
	else insertNode(pRoot->pLeft, dataIn);
	return 1;
}
template <class T> bool		BinarySearchTree<T>::insertNode(T dataIn)
{
	return insertNode(pRoot, dataIn);
}

template <class T> Node<T>* BinarySearchTree<T>::minOfRightBranch(Node<T>* pRoot)
{
	if (pRoot->pRight->pLeft == NULL)
	{
		return NULL;
	}
	else
	{
		Node<T>* pPre = pRoot->pRight;
		while (pPre->pLeft->pLeft != NULL)
		{
			pPre = pPre->pLeft;
		}
		return pPre;
	}
}
template <class T> Node<T>* BinarySearchTree<T>::deleteNode(Node<T>* pDel)
{
	if (pDel->pLeft == NULL && pDel->pRight == NULL)
	{
		delete pDel;
		return NULL;
	}
	else if (pDel->pLeft != NULL && pDel->pRight == NULL)
	{
		Node<T>* pTemp = pDel->pLeft;
		delete pDel;
		return pTemp;
	}
	else if (pDel->pLeft == NULL && pDel->pRight != NULL)
	{
		Node<T>* pTemp = pDel->pRight;
		delete pDel;
		return pTemp;
	}
	else
	{
		Node<T>* pPre = minOfRightBranch(pDel);
		if (pPre == NULL)
		{
			pDel->data = pDel->pRight->data;
			pDel->pRight = deleteNode(pDel->pRight);
			return pDel;
		}
		else
		{
			pDel->data = pPre->pLeft->data;
			pPre->pLeft = deleteNode(pPre->pLeft);
			return pDel;
		}
	}
}
template <class T> bool		BinarySearchTree<T>::deleteNode(T key)
{
	int isRight;
	Node<T>* pPre = Search(pRoot, key, isRight);
	if (pPre == NULL)
	{
		return 0;
	}

	if (isRight == 0)
	{
		pPre->pLeft = deleteNode(pPre->pLeft);
	}
	else if (isRight == 1)
	{
		pPre->pRight = deleteNode(pPre->pRight);
	}
	else if (isRight == -1)
	{
		pRoot = deleteNode(pPre);
	}
	return 1;
}

template <class T> void		BinarySearchTree<T>::ClearRecursion(Node<T>* pRoot)
{
	if (pRoot->pLeft != NULL) ClearRecursion(pRoot->pLeft);
	if (pRoot->pRight != NULL) ClearRecursion(pRoot->pRight);
	delete pRoot;
}
template <class T> void		BinarySearchTree<T>::Clear()
{
	ClearRecursion(pRoot);
}

template <class T> void		BinarySearchTree<T>::Print(Node<T>* pRoot)
{
	if (pRoot != NULL)
	{
		Print(pRoot->pLeft);
		cout << pRoot->data << " ";
		Print(pRoot->pRight);
	}
}
template <class T> void		BinarySearchTree<T>::Print()
{
	Print(pRoot);
}



#endif // !BINARYSEARCHTREE

