#include "NodeBST.h"

NodeBST::NodeBST(char data, NodeBST* left, NodeBST* right) :
    Node(data),
    left(left),
    right(right)
{
}

NodeBST::NodeBST(NodeBST& other) :
	Node(other),
    left(other.left),
    right(other.right)
{
}

NodeBST::~NodeBST() {}