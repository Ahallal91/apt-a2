#include "LinkedList.h"

Node::Node(int data, Node* next) {
    this->data = data;
    this->next = next;
}

Node::Node(Node& other) :
    data(other.data),
    next(other.next) {
}

LinkedList::LinkedList() {
    this->head = nullptr;
    this->tail = nullptr;
    length = 0;
}

LinkedList::~LinkedList() {
    clear();
}

int LinkedList::size() {
    return length;
}

void LinkedList::clear() {
    Node* current = head;
    for(int i = 0; i < length; ++i) {
        Node* temp = current->next;
        delete current;
        current = nullptr;
        current = temp;
    }
    tail = nullptr;
    head = nullptr;
    length = 0;
}

int LinkedList::get(int index) {
    int retValue = -1;
    if(index >= 0 && index < length) {
        int count = 0;
        Node* current = head;
        while(count < index) {
            current = current->next;
            count++;
        }
        retValue = current->data;
    }   
    return retValue;
}

void LinkedList::addFront(int data) {
    Node* tempNode = new Node(data, head);  
    if(head == nullptr) {
        tail = tempNode;
    }
    head = tempNode;
    length++;
}

void LinkedList::addBack(int data) {
    Node* tempNode = new Node(data, nullptr);
    if(head == nullptr && tail == nullptr) {
        head = tempNode;
        tail = tempNode;
    } else {   
        tail->next = tempNode;
        tail = tempNode;
    }
    length++;
}

void LinkedList::removeFront(int data) {
    if(head != nullptr && tail != nullptr) {
        if (head != tail) {
            Node* tempNode = head;
            head = head->next;
            delete tempNode;
            tempNode = nullptr;
        } else {
            delete head;
            head = nullptr;
            tail = nullptr;
        }
        length--;
    } 
    
}