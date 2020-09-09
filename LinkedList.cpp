#include "LinkedList.h"
#include <stdexcept>

Node::Node(char data, Node* next) {
	this->data = data;
	this->next = next;
}

Node::Node(Node& other):
	data(other.data),
	next(other.next) {}

LinkedList::LinkedList() {
	this->head = nullptr;
}

LinkedList::~LinkedList() {
	clear();
	delete head;
}

unsigned int LinkedList::size() {
	unsigned int count = 0;
    Node* current = head;
    while(current != nullptr) {
        current = current->next;
        count++;
    }
    return count;
}

void LinkedList::clear() {
	Node* current = head;
    for(unsigned int i = 0; i < size(); ++i) {
        Node* temp = current->next;
        delete current;
        current = nullptr;
        current = temp;
    }
    head = nullptr;
}

char LinkedList::get(unsigned int index) {
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
	Node* tempNode = new Node(data, head);  
    head = tempNode;
}

void LinkedList::addBack(char data) {
	Node* tempNode = new Node(data, nullptr);
    if(head == nullptr) {
        head = tempNode;
    } else {  
        Node* current = head;
        while(current->next != nullptr) {
            current = current->next;
        } 
        current->next = tempNode;
    }
}

void LinkedList::removeFront() {
	if (head != nullptr) {
        Node* tempNode = head;
        head = head->next;
        delete tempNode;
        tempNode = nullptr;
    }
}