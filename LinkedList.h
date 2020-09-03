#ifndef LINKED_LIST_H
#define LINKED_LIST_H

class Node {
public:
    Node(char data, Node* next);
    Node(Node& other);

    char data;
    Node* next;
};

class LinkedList {
public:
    LinkedList();
    ~LinkedList();

    int size();
    void clear();
    char get(int i );
    void addFront(char data);
    void addBack(char data);
    void removeFront();

private:
    Node* head;
    Node* tail;
    int length;
};

#endif // LINKED_LIST_H