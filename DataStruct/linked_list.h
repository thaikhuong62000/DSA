#pragma once
#include <iostream>

struct Node {
	int data = 0;
    Node* next = NULL;
};

class LList {
    private:
        Node* head;
        int size;
        ////////////////////////
		bool insertNode(Node* pPre, int value);
		bool deleteNode(Node* pPre, Node* pLoc);
    public:
        LList();
        ~LList();      

        bool insert(int pos, int value);
        bool remove(int value);
        int search(int value);        
        bool replace(int position, int value);

        int getsize();
        bool isEmpty();

        void clear();

        Node* get_head();
        void merge_list(LList* list);

        void print_list();
    
};

LList::LList()
{
	// TODO
	this->head = nullptr;
	this->size = 0;
}

LList::~LList()
{
	// TODO
	clear();
}

bool LList::insert(int pos, int value)
{
	// TODO
	if (pos > this->size || pos < 0)
	{
		return 0;
	}
	else if (pos == 0)
	{
		return insertNode(nullptr, value);
	}
	else
	{
		int temp = 1;
		Node* pPre = new Node();
		pPre = this->head;
		while (temp < pos)
		{
			pPre = pPre->next;
			temp++;
		}
		return insertNode(pPre, value);
	}
}

bool LList::remove(int value)
{
	// TODO
	Node* pPre = new Node();
	pPre = this->head;
	while (pPre->next != NULL)
	{
		if (pPre->next->data == value)
		{
			break;
		}
		pPre = pPre->next;
	}
	return deleteNode(pPre, pPre->next);
}

int LList::search(int value)
{
	// TODO
	Node* pLoc = new Node();
	pLoc = this->head;
	int idx = 0;
	while (pLoc != NULL)
	{
		if (pLoc->data == value)
		{
			return idx;
		}
		pLoc = pLoc->next;
		idx++;
	}
	return -1;
}

bool LList::replace(int position, int value)
{
	// TODO
	if (position >= this->size || position < 0)
	{
		return 0;
	}
	else if (position == 0)
	{
		this->head->data = value;
		return 1;
	}
	else
	{
		int temp = 1;
		Node* pLoc = new Node();
		pLoc = this->head->next;
		while (temp < position)
		{
			pLoc = pLoc->next;
			temp++;
		}
		pLoc->data = value;
		return 1;
	}
}

int LList::getsize()
{
	// TODO
	return size;
}

bool LList::isEmpty()
{
	// TODO
	return !head;
}

void LList::clear()
{
	// TODO
	if (this->head != NULL)
	{
		Node* pDel = new Node();
		while (this->head != NULL)
		{
			delete pDel;
			pDel = this->head;
			this->head = this->head->next;
		}
		delete pDel;
	}
	this->size = 0;
}

Node* LList::get_head()
{
	// TODO
	return head;
}

void LList::merge_list(LList* list)
{
	// TODO
	Node* pLoc = new Node();
	pLoc = this->head;
	while (pLoc->next != NULL)
	{
		pLoc = pLoc->next;
	}
	pLoc->next = list->get_head();
	this->size = list->getsize();
}

void LList::print_list()
{
	// TODO
	Node* pLoc = new Node();
	pLoc = this->head;
	while (pLoc != NULL)
	{
		cout << pLoc->data;
		pLoc = pLoc->next;
	}
	cout << '\n';
}

bool LList::insertNode(Node* pPre, int value)
{
	Node* pNew = new Node();
	if (pNew == NULL)
	{
		return 0;
	}
	pNew->data = value;
	if (pPre == NULL)
	{
		pNew->next = this->head;
		this->head = pNew;
	}
	else
	{
		pNew->next = pPre->next;
		pPre->next = pNew;
	}
	this->size++;
	return 1;
}

bool LList::deleteNode(Node* pPre, Node* pLoc)
{
	if (pLoc == NULL)
	{
		return 0;
	}
	if (pPre == NULL)
	{
		this->head = pLoc->next;
	}
	else
	{
		pPre->next = pLoc->next;
	}
	this->size--;
	delete pLoc;
	return 1;
}