#include "Node.h"

Node::Node(char data, Node* prev, Node* next) :
    data(data),
    next(next),
    prev(prev)
{
}

Node::Node(Node& other) :
	data(other.data),
	next(other.next),
    prev(other.prev) 
{
}
