#include <algorithm>
#include <cassert>
#include "List.h"

template <typename T>
struct Node {
	T data;
	Node* next;

	Node(const T& data, Node* next);
};

template <typename T>
class LinkedList : public List<T> {
	Node<T>* front;
	Node<T>* back;
	int size;
	
	Node<T>* getNodeAtIndex(int index) const;

public:
	LinkedList();
	LinkedList(const LinkedList& other);
	~LinkedList();
	void swap(LinkedList& other);
	LinkedList& operator=(const LinkedList& other);

	void pushFront(const T& value);
	void pushBack(const T& value);
	void popFront();
	void popBack();
	const T& getFront() const;
	const T& getBack() const;
	bool isEmpty() const;
	int getSize() const;
	T& operator[](int index);
	const T& operator[](int index) const;
	void insertAt(int index, const T& value);
	void removeAt(int index, const T& value);
};

template <typename T>
Node<T>::Node(const T& data, Node* next)
	: data(data), next(next) {
}

template <typename T>
LinkedList<T>::LinkedList()
	: front(0), back(0) {
}

template <typename T>
LinkedList<T>::LinkedList(const LinkedList<T>& other)
	: front(0), back(0) {
	Node<T>* currentNode = other.front;
	while (currentNode != 0) {
		pushBack(currentNode->data);
		currentNode = currentNode->next;
	}
}

template <typename T>
LinkedList<T>::~LinkedList() {
	Node<T>* currentNode = front;

	while (currentNode != 0) {
		Node<T>* toDelete = currentNode;
		currentNode = currentNode->next;

		delete toDelete;
	}
}

template <typename T>
void LinkedList<T>::swap(LinkedList<T>& other) {
	std::swap(front, other.front);
	std::swap(back, other.back);
	std::swap(size, other.size);
}

template <typename T>
LinkedList<T>& LinkedList<T>::operator=(const LinkedList<T>& other) {
	if (this != &other) {
		LinkedList temp(other);
		swap(temp);
	}

	return *this;
}

template <typename T>
Node<T>* LinkedList<T>::getNodeAtIndex(int index) const {
	assert(index < size);
	
	Node<T>* currentNode = front;
	
	while (index > 0) {
		currentNode = currentNode->next;
		index--;
	}
	
	return currentNode;
}

template <typename T>
void LinkedList<T>::pushFront(const T& value) {
	front = new Node<T>(value, front);

	if (back == 0) {
		back = front;
	}

	size++;
}

template <typename T>
void LinkedList<T>::pushBack(const T& value) {
	Node<T>* newNode = new Node<T>(value, 0);

	if (front != 0) {
		back->next = newNode;
		back = newNode;
	} else {
		front = back = newNode;
	}

	size++;
}

template <typename T>
void LinkedList<T>::popFront() {
	assert(front != 0);

	Node<T>* oldNode = front;
	front = front->next;
	delete oldNode;

	if (front == 0) {
		back = 0;
	}

	size--;
}

template <typename T>
void LinkedList<T>::popBack() {
	assert(front != 0);

	if (front == back) {
		delete back;
		front = back = 0;
		return;
	}
	
	Node<T>* prevNode = getNodeAtIndex(size - 2);
	delete prevNode->next;
	prevNode->next = 0;
	
	back = prevNode;
}

template <typename T>
const T& LinkedList<T>::getFront() const {
	assert(front != 0);

	return front->data;
}

template <typename T>
const T& LinkedList<T>::getBack() const {
	assert(front != 0);

	return back->data;
}

template <typename T>
bool LinkedList<T>::isEmpty() const {
	return front == 0;
}

template <typename T>
int LinkedList<T>::getSize() const {
	return size;
}

template <typename T>
T& LinkedList<T>::operator[](int index) {
	return getNodeAtIndex(index)->data;
}

template <typename T>
const T& LinkedList<T>::operator[](int index) const {
	return getNodeAtIndex(index)->data;
}

template <typename T>
void LinkedList<T>::insertAt(int index, const T& value) {
	assert(index <= size);
	
	if (index == size) {
		pushBack(value);
		return;
	} else if (index == 0) {
		pushFront(value);
		return;
	}
	
	Node<T>* prevNode = getNodeAtIndex(index - 1);
	prevNode->next = new Node<T>(value, prevNode->next);
}

template <typename T>
void LinkedList<T>::removeAt(int index, const T& value) {
	assert(index < size);
	
	if (index == 0) {
		popFront();
	} else if (index == size - 1) {
		popBack();
	}
	
	Node<T>* prevNode = getNodeAtIndex(index - 1);
	
	Node<T>* toDelete = prevNode->next;
	prevNode->next = toDelete->next;
	
	delete toDelete;
}
