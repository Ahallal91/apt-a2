#ifndef NODE_H
#define NODE_H

class Node {
public:
    Node(char data);
    Node(Node& other);

    char data;
};

#endif // NODE_H