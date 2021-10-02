#ifndef NODE_LIST_H
#define NODE_LIST_H

#include "Node.h"

class NodeList : public Node{
public:
    NodeList(char data, NodeList* prev, NodeList* next);
    NodeList(NodeList& other);

    NodeList* next;
    NodeList* prev;
};

#endif // NODE_LIST_H