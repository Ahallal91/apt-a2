#include <stdexcept>

#include "Node.h"
#include "LinkedList.h"

LinkedList::LinkedList() {
	this->head = nullptr;
    this->tail = nullptr;
}

LinkedList::LinkedList(LinkedList& other) {
    Node* current = other.head;
    while(current != nullptr) {
        addBack(current->data);
        current = current->next;
    }
    this->head  = other.head;
    this->tail = other.tail;
}

LinkedList::~LinkedList() {
	clear();
}

unsigned int LinkedList::size() const {
	unsigned int count = 0;
    Node* current = head;
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
        Node* current = head;
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

void LinkedList::addFront(char data) {
    Node* toAdd = new Node(data, nullptr, head); 
    if(head == nullptr) {
        head = toAdd;
        tail = toAdd;
    } else {
        head->prev = toAdd;
    }
    head = toAdd;
}

void LinkedList::addBack(char data) {
	Node* toAdd = new Node(data, tail, nullptr);
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
        Node* toDelete = head;
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
        Node* toDelete = tail;
        tail = tail->prev;
 
        if(tail == nullptr) {
            head = nullptr;
        } else {
            tail->next = nullptr;
        }
        delete toDelete;
    }
}