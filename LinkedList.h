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

    unsigned int size() const;

    // deletes all items in the list
    void clear();
    char get(const unsigned int i) const;
    void addFront(char data);
    void addBack(char data);

    // removes the first item in the list.
    void removeFront();

private:
    Node* head;
};

#endif // LINKED_LIST_H