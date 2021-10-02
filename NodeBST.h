#ifndef NODE_BST_H
#define NODE_BST_H

#include "Node.h"

class NodeBST : public Node {
public:
    NodeBST(char data, NodeBST* left, NodeBST* right);
    NodeBST(NodeBST& other);
    ~NodeBST();

    NodeBST* left;
    NodeBST* right;
};

#endif // NODE_BST_H