#pragma once
#include<exception>
using namespace std;

template <class T> class queue;
template <class T> class node;

template <class T>
class queue {
private:
	node<T>* head;


public:
	queue();
	~queue();
	void push(T newNum);
	T pop(); //If you pop on an empty queue, program throws exception, crashes
	bool isEmpty();



};

template <class T>
class node {
public:
	node(T myInitialValue);
	~node();
	T getValue();//returns the stored value from the noder to the next node
	void setNext(node<T>* newNext);
	void changeValue(T newValue);//sets value to newValue
	node<T>* getNext();

private:
	T value;
	node<T>* next;

};

#include "queue.h"

template <class T>
queue<T>::queue() {
	head = nullptr;
}
template <class T>
queue<T>::~queue() {
	delete head;
	head = nullptr;
}
template <class T>
void queue<T>::push(T newNum) {
	node<T>* temp = new node<T>(newNum);
	if (head == nullptr) {
		head = temp;
		temp = nullptr;
	}
	else {
		node<T>* runner = head;
		while (runner->getNext() != nullptr)
			runner = runner->getNext();
		runner->setNext(temp);
		runner = nullptr;
		temp = nullptr;
	}
}
template <class T>
T queue<T>::pop() {
	T temp;
	if (head != nullptr) {
		temp = head->getValue();
		node<T>* deleteMe = head;
		head = head->getNext();
		deleteMe->setNext(nullptr);
		delete deleteMe;
		deleteMe = nullptr;
		return temp;
	}
	throw exception();//you popped from an empty queue
}
template <class T>
bool queue<T>::isEmpty() {
	return head == nullptr;
}
template <class T>
node<T>::node(T myInitialValue) {
	value = myInitialValue;
	next = nullptr;
}
template <class T>
node<T>::~node() {
	if (next) {
		delete next;
		next = nullptr;
	}
}
template <class T>
T node<T>::getValue() {
	return value;
}

template <class T>
void node<T>::setNext(node<T>* newNext) {
	next = newNext;
}
template <class T>
void node<T>::changeValue(T newValue) {
	value = newValue;
}
template <class T>
node<T>* node<T>::getNext() {
	return this->next;
}