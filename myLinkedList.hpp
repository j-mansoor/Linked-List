
#pragma once
#include <stdexcept>

template <class T>
struct Node {
	T data;//data the node will hold
	Node<T>* next;//pointer to the next node in the list
	Node<T>* prev;//pointer to the previous node in the list
};

template<class T>
class myLinkedList {
private:
	Node<T>*mHead;//pointer to the first node in the linked list
	Node<T>*mTail;//pointer to the last node in the linked list
	int mSize;//keeps a running count of the number of nodes in the linked list
	
	void clear();//function that deletes every node from the list
	void copy(const myLinkedList&);//function that takes in the contents of one list and performs a deep copy of it
	void checkForEmptyList() const;//function that checks to see if the list is empty, throws an error if true
	
public:
	myLinkedList();//default constructor, set mHead and mTail to null, set size to 0
	myLinkedList(const myLinkedList &);//copy constructor, takes a linked list and performs deep copy
	~myLinkedList();//destructor that performs pop_front repeatedly until the list is empty
	myLinkedList<T>& operator=(const myLinkedList&);//overloaded assignment operator, deletes current list and replaces it with a copy of the passed list
	
	int size() const;//function that returns the size of the linked list
	
	T front() const; //returns the first node in the list
	T back() const; //returns the last node in the list
	T at(int) const;//traverses the list and returns the data value at a specific node
	bool empty();// returns true if the list is empty14 ;v222
	void push_front(T);//creates new node, places it at front of list, increments size by one
	void push_back(T);//creates new node, places it at end of list, increments size by one
	T pop_front();//deletes node from the beginning of the list, decrements size by one, returns deleted element
	T pop_back();//deletes node from the end of the list, decrements size by one, returns deleted element
};



template<class T>
void myLinkedList<T>::clear()
{
	while (mHead != nullptr)
		pop_front();
}

template<class T>
void myLinkedList<T>::copy(const myLinkedList &firstList)
{
	Node<T>* cursor = firstList.mHead;

	while (cursor != nullptr) {
		push_back(cursor->data);
		cursor = cursor->next;
	}
}

template<class T>
void myLinkedList<T>::checkForEmptyList() const
{
	if (mHead == nullptr)
		throw std::logic_error("The list is empty");
}

template<class T>
myLinkedList<T>::myLinkedList()
{
	mHead = nullptr;
	mTail = nullptr;
	mSize = 0;
}

template<class T>
myLinkedList<T>::myLinkedList(const myLinkedList &firstList)
{
	clear();
	copy(firstList);

}

template<class T>
myLinkedList<T>::~myLinkedList()
{
	clear();
}

template<class T>
myLinkedList<T>& myLinkedList<T>::operator=(const myLinkedList &right)
{
	if (this != &right) {
		clear();
		copy(right);
}
	return *this;
}

template<class T>
int myLinkedList<T>::size() const
{
	return mSize;
}

template<class T>
T myLinkedList<T>::front() const
{
	return mHead->data;
}

template<class T>
T myLinkedList<T>::back() const
{
	return mTail->data;
}

template<class T>
T myLinkedList<T>::at(int num) const
{
	checkForEmptyList();
	if (num < 0 || num >= mSize) {
		throw std::logic_error("Index out of bounds");
	}
	if (num + 1 == mSize) { return mTail->data; }
	Node<T>* cursor = mHead;
	
	for (int i = 0; i < num; i++) {
	cursor = cursor->next;
	}
	return cursor->data;
}

template<class T>
bool myLinkedList<T>::empty()
{
	if (mHead == nullptr)
		return true;
	else
		return false;
}

template<class T>
void myLinkedList<T>::push_front(T data)
{
	if (mHead == nullptr) {
		mHead = new Node<T>{ data, nullptr, nullptr };
		mTail = mHead;
	}
	else {
		mHead->prev = new Node<T>{ data, mHead, nullptr };
		mHead = mHead->prev;
	}
	mSize++;
}

template<class T>
void myLinkedList<T>::push_back(T data)
{
	if (mHead == nullptr && mTail == nullptr) { 
		mHead = new Node<T>{ data, nullptr, nullptr };
		mTail = mHead;
	}
	else {
		mTail->next = new Node<T>{ data, nullptr, mTail };
		mTail = mTail->next;
	}
	mSize++;
}

template<class T>
T myLinkedList<T>::pop_front()
{
	checkForEmptyList();
	T temp = mHead->data;
	Node<T>* oldHead = mHead;
	if (mHead->next == nullptr) {
		mHead = nullptr;
		mTail = nullptr;
	}
	else {
		mHead = mHead->next;
		mHead->prev = nullptr;
	}
	mSize--;
	delete oldHead;
	oldHead = nullptr;
    return temp;
}

template<class T>
T myLinkedList<T>::pop_back()
{
	checkForEmptyList();
	T temp = mTail->data;
	Node<T>* oldTail = mTail;
	if (mTail->prev == nullptr) {
		mHead = nullptr;
		mTail = nullptr;
	}
	else {
		mTail = mTail->prev;
		mTail->next = nullptr;
	}
	mSize--;
	delete oldTail;
	oldTail = nullptr;
	return temp;
}
