#pragma once
#include <iostream>

using namespace std;

#ifndef AVLTREE
#define AVLTREE

template <class T> struct Node
{
	T data;
	Node<T>* pLeft, * pRight;
	int height;
	Node() : data(0), height(1), pLeft(NULL), pRight(NULL) {}
	Node(int dataIn) : data(dataIn), height(1), pLeft(NULL), pRight(NULL) {}
};

template <class T> class AVLTree
{
	Node<T>* pRoot;

	bool		insertNode(Node<T>*& pRoot, T dataIn);
	//Delete one Node
	Node<T>*	deleteNode(Node<T>* pDel);
	//Delete recursion
	bool		deleteNode(Node<T>* pPre, Node<T>*& pDel, T key);

	Node<T>*	minOfRightBranch(Node<T>* pRoot);
	int			getBalance(Node<T>* pRoot);
	int			Max(int a, int b);

	Node<T>*	Search(Node<T>* pRoot, T key);

	Node<T>*	rotateRight(Node<T>* pRoot);
	Node<T>*	rotateLeft(Node<T>* pRoot);

	void		ClearRecursion(Node<T>* pRoot);
	void		Print(Node<T>* pRoot);
public:
	AVLTree();
	~AVLTree();

	Node<T>*	Search(T key);
	int			getHeight(Node<T>*);

	bool		insertNode(T dataIn);
	bool		deleteNode(T info);

	void		Clear();
	void		Print();


};

template <class T>			AVLTree<T>::AVLTree()
{
	pRoot = NULL;
}
template <class T>			AVLTree<T>::~AVLTree()
{
	Clear();
}

template <class T> Node<T>* AVLTree<T>::Search(Node<T>* pRoot, T key)
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
template <class T> Node<T>* AVLTree<T>::Search(T key)
{
	return Search(pRoot, key);
}

template <class T> Node<T>* AVLTree<T>::rotateRight(Node<T>* pRoot)
{
	//Rotate
	Node<T>* pTemp = pRoot->pLeft;
	pRoot->pLeft = pTemp->pRight;
	pTemp->pRight = pRoot;

	//Update Height
	pRoot->height = 1 + Max(getHeight(pRoot->pLeft), getHeight(pRoot->pRight));
	pTemp->height = 1 + Max(getHeight(pTemp->pLeft), getHeight(pRoot));

	return pTemp;
}
template <class T> Node<T>* AVLTree<T>::rotateLeft (Node<T>* pRoot)
{
	//Rotate
	Node<T>* pTemp = pRoot->pRight;
	pRoot->pRight = pTemp->pLeft;
	pTemp->pLeft = pRoot;

	//Update Height
	pRoot->height = 1 + Max(getHeight(pRoot->pLeft), getHeight(pRoot->pRight));
	pTemp->height = 1 + Max(getHeight(pTemp->pRight), getHeight(pRoot));

	return pTemp;
}

template <class T> bool		AVLTree<T>::insertNode(Node<T>*& pRoot, T dataIn)
{
	//Insert BST
	bool SS = 1;
	if (pRoot == NULL)
	{
		Node<T>* pNew = new Node<T>(dataIn);
		if (pNew == NULL) return 0;
		pRoot = pNew;
		return 1;
	}
	else if (pRoot->data < dataIn)
	{
		SS = insertNode(pRoot->pRight, dataIn);
	}
	else if (pRoot->data > dataIn)
	{
		SS = insertNode(pRoot->pLeft, dataIn);
	}
	else
	{
		return 0;
	}
	//Update height
	pRoot->height = 1 + Max(getHeight(pRoot->pLeft), getHeight(pRoot->pRight));

	//Check balance
	int balance = getBalance(pRoot);

	//Left-Left
	if (balance > 1 && dataIn < pRoot->pLeft->data)
	{
		pRoot = rotateRight(pRoot);
	}
	//Left-Right
	else if (balance > 1 && dataIn > pRoot->pLeft->data)
	{
		pRoot->pLeft = rotateLeft(pRoot->pLeft);
		pRoot = rotateRight(pRoot);
	}
	//Right-Right
	if (balance < -1 && dataIn > pRoot->pRight->data)
	{
		pRoot = rotateLeft(pRoot);
	}
	//Right-Left
	else if (balance < -1 && dataIn < pRoot->pRight->data)
	{
		pRoot->pRight = rotateRight(pRoot->pRight);
		pRoot = rotateLeft(pRoot);
	}
	return SS;
}
template <class T> bool		AVLTree<T>::insertNode(T dataIn)
{
	return insertNode(pRoot, dataIn);
}

template <class T> Node<T>* AVLTree<T>::deleteNode(Node<T>* pDel)
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
		T temp = pDel->data;
		if (pPre == NULL)									//minOfRightBranch == pRoot->pRight
		{
			pDel->data = pDel->pRight->data;
			pDel->pRight->data = temp;
			deleteNode(pDel, pDel->pRight, temp);
			return pDel;
		}
		else
		{
			pDel->data = pPre->pLeft->data;
			pPre->pLeft->data = temp;
			deleteNode(NULL, pDel, temp);
			return pDel;
		}
	}
}
template <class T> bool		AVLTree<T>::deleteNode(Node<T>* pPre, Node<T>*& pDel, T key)
{
	bool SS = 1;
	if ((pPre != NULL && pDel == NULL) || pDel == NULL)
	{
		return 0;
	}
	else if (pDel->data > key)
	{
		//Delete pDel->pLeft
		SS = deleteNode(pDel, pDel->pLeft, key);
	}
	else if (pDel->data < key)
	{
		//Delete pDel->pLeft
		SS = deleteNode(pDel, pDel->pRight, key);
	}
	else
	{
		//Delete pDel
		pDel = deleteNode(pDel);
	}
	if (pDel == NULL)
	{
		return SS;
	}
	//Update height
	pDel->height = 1 + Max(getHeight(pDel->pLeft), getHeight(pDel->pRight));

	//Check balance
	int balance = getBalance(pDel);
	int balanceLeft = getBalance(pDel->pLeft);
	int balanceRight = getBalance(pDel->pRight);

	//Left-Left
	if (balance > 1 && balanceLeft >= 0)
	{
		pDel = rotateRight(pDel);
	}
	//Left-Right
	else if (balance > 1 && balanceLeft < 0)
	{
		pDel->pLeft = rotateLeft(pDel->pLeft);
		pDel = rotateRight(pDel);
	}
	//Right-Right
	if (balance < -1 && balanceRight <= 0)
	{
		pDel = rotateLeft(pDel);
	}
	//Right-Left
	else if (balance < -1 && balanceRight > 0)
	{
		pDel->pRight = rotateRight(pDel->pRight);
		pDel = rotateLeft(pDel);
	}
	return SS;
}
template <class T> bool		AVLTree<T>::deleteNode(T key)
{
	return deleteNode(NULL, pRoot, key);
}

template <class T> Node<T>* AVLTree<T>::minOfRightBranch(Node<T>* pRoot)
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
template <class T> int		AVLTree<T>::getHeight(Node<T>* pRoot)
{
	if (pRoot == NULL)
	{
		return 0;
	}
	else return pRoot->height;
}
template <class T> int		AVLTree<T>::getBalance(Node<T>* pRoot)
{
	if (pRoot == NULL)
	{
		return 0;
	}
	else
	{
		return getHeight(pRoot->pLeft) - getHeight(pRoot->pRight);
	}
}
template <class T> int		AVLTree<T>::Max(int a, int b)
{
	return (a > b) ? a : b;
}

template <class T> void		AVLTree<T>::ClearRecursion(Node<T>* pRoot)
{
	if (pRoot->pLeft != NULL) ClearRecursion(pRoot->pLeft);
	if (pRoot->pRight != NULL) ClearRecursion(pRoot->pRight);
	delete pRoot;
}
template <class T> void		AVLTree<T>::Clear()
{
	ClearRecursion(pRoot);
}

template <class T> void		AVLTree<T>::Print(Node<T>* pRoot)
{
	if (pRoot != NULL)
	{
		Print(pRoot->pLeft);
		cout << pRoot->data << " ";
		Print(pRoot->pRight);
	}
}
template <class T> void		AVLTree<T>::Print()
{
	Print(pRoot);
}



#endif // !AVLTREE