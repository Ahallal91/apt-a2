
#ifndef BST_H
#define BST_H

#include "NodeBST.h"
#include <iostream>

class BST {
public:

   BST();
   ~BST();

   // deletes all nodes in the tree.
   void clear();
   
   // contract: we don't modify the data given
   bool contains(const char data) const;

   // contract: we don't modify the data given
   void add(const char data);

   // contract: we don't modify the data given
   void remove(const char data);

   // returns a node that matches the data given.
   NodeBST* get(const char data) const;

   // this returns the value of the root node if the BST still has items in it.
   char getRootValue();
   
   // returns a string of all the items in the tree. each item is spaced with empty space.
   std::string dfs();

   // returns a count of how many of a type of char there is.
   int count(const char data);
private:
   NodeBST* root;

   // helper method for contains
   bool contains(NodeBST* node, const char data) const;

   // helper method for add
   NodeBST* add(NodeBST* node, const char data);

   // helper method for get
   NodeBST* get(NodeBST* node, const char data) const;

   // helper method for clear
   void clear(NodeBST* node);

   // helper method for remove to reconnect when removing a node with 2 children
   NodeBST* FindMax(NodeBST* node);

   // helper method for remove
   NodeBST* remove(NodeBST* node, char data);
   
   // helper method for dfs
   void dfs(NodeBST* node, std::string& bstItems);

   // helper method for count
   void count(NodeBST* node, const char data, int& amount);

};

#endif // BST_H