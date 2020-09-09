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

    // deletes all items in the list
    void clear();
    char get(int i);
    void addFront(char data);
    void addBack(char data);

    // removes the first item in the list.
    void removeFront();

private:
    Node* head;
};

#endif // LINKED_LIST_H