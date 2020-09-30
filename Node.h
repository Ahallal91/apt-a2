#ifndef NODE_H
#define NODE_H

class Node {
public:
    Node(char data, Node* prev, Node* next);
    Node(Node& other);
    Node(Node&& other);

    char data;
    Node* next;
    Node* prev;
};

#endif // NODE_H