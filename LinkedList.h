#ifndef LINKED_LIST_H
#define LINKED_LIST_H

class Node {
public:
    Node(int data, Node* next);
    Node(Node& other);

    int data;
    Node* next;
};

class LinkedList {
public:
    LinkedList();
    ~LinkedList();

    int size();
    void clear();
    int get(int i );
    void addFront(int data);
    void addBack(int data);
    void removeFront(int data);

private:
    Node* head;
    Node* tail;
    int length;
};

#endif // LINKED_LIST_H