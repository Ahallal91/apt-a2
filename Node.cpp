#include "Node.h"

Node::Node(char data) :
    data(data)
{
}

Node::Node(Node& other) :
	data(other.data)
{
}
