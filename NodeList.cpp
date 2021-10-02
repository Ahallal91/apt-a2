#include "NodeList.h"

NodeList::NodeList(char data, NodeList* prev, NodeList* next) :
    Node(data),
    next(next),
    prev(prev)
{
}

NodeList::NodeList(NodeList& other) :
    Node(other),
	next(other.next),
    prev(other.prev) 
{
}
