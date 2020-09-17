#ifndef LINKED_LIST_H
#define LINKED_LIST_H

class Node {
public:
    Node(char data, Node* prev, Node* next);
    Node(Node& other);
    Node(Node&& other);

    char data;
    Node* next;
    Node* prev;
};

class LinkedList {
public:
    LinkedList();
    LinkedList(LinkedList& other);
    LinkedList(LinkedList&& other);
    ~LinkedList();

    void clear();

    unsigned int size() const;
    char get(const unsigned int i) const;

    void addFront(char data);
    void addBack(char data);

    void removeFront();
    void removeBack();

private:
    Node* head;
    Node* tail;
};

#endif // LINKED_LIST_H