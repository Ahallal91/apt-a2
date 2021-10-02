#include <stdexcept>
#include <iostream>
#include "NodeList.h"
#include "LinkedList.h"

LinkedList::LinkedList() {
	this->head = nullptr;
    this->tail = nullptr;
}

LinkedList::LinkedList(const LinkedList& other) {
    NodeList* toAdd = new NodeList(*other.head);
    while(toAdd != nullptr) {
      addBack(toAdd->data);
      toAdd = toAdd->next;
    }
    delete toAdd;
}

LinkedList::~LinkedList() {
	clear();
}

unsigned int LinkedList::size() const {
	unsigned int count = 0;
    NodeList* current = head;
    while(current != nullptr) {
        current = current->next;
        count++;
    }
    return count;
}

void LinkedList::clear() {
    while(head != nullptr) {
        removeFront();
    }
}

char LinkedList::get(const unsigned int index) const {
	char retValue = '\0';
	if(index < size()) {
        unsigned int count = 0;
        NodeList* current = head;
        while(count < index) {
            current = current->next;
            count++;
        }
        retValue = current->data;
    } else {
		throw std::out_of_range("LinkedList::get - index out of range.");
	}
	return retValue;
}

char LinkedList::front() {
    char retValue = '\0';
    if(head != nullptr) {
        retValue = head->data;
    }
    return retValue;
}

char LinkedList::back() {
    char retValue = '\0';
    if(tail != nullptr) {
        retValue = tail->data;
    }
    return retValue;
}

void LinkedList::addFront(char data) {
    NodeList* toAdd = new NodeList(data, nullptr, head); 
    if(head == nullptr) {
        head = toAdd;
        tail = toAdd;
    } else {
        head->prev = toAdd;
    }
    head = toAdd;
}

void LinkedList::addBack(char data) {
	NodeList* toAdd = new NodeList(data, tail, nullptr);
    if(tail == nullptr) {
        head = toAdd;
        tail = toAdd;
    } else {
        tail->next = toAdd;
    }
    tail = toAdd;
}

void LinkedList::removeFront() {
    if (tail != nullptr) {
        NodeList* toDelete = head;
        head = head->next;
 
        if(head == nullptr) {
            tail = nullptr;
        } else {
            head->prev = nullptr;
        }
        delete toDelete;
    }
}

void LinkedList::removeBack() {
    if (tail != nullptr) {
        NodeList* toDelete = tail;
        tail = tail->prev;
 
        if(tail == nullptr) {
            head = nullptr;
        } else {
            tail->next = nullptr;
        }
        delete toDelete;
    }
}