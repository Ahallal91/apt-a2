#include "BST.h"
   
BST::BST() {
    this->root = nullptr;
}

BST::~BST() {
    clear(root);
}

void BST::clear() {
    clear(root);
}

bool BST::contains(const char data) const {
   return contains(root, data);
}

int BST::count(const char data) {
   int amount = 0;
   count(root, data, amount);
   return amount;
}

void BST::count(NodeBST* node, const char data, int& amount) {
   if(node != nullptr) {
      count(node->left, data, amount);

      if(node->data == data) {
         amount++;
      }
      count(node->right, data, amount);
   }
}

void BST::add(const char data) {
   root = add(root, data);
}

void BST::remove(const char data) {
    root = remove(root, data);
}

char BST::getRootValue() {
   char retValue = '\0';
   if (root != nullptr) {
      retValue = root->data;
   }
   return retValue;
}

NodeBST* BST::get(const char data) const {
   return get(root, data);
}

std::string BST::dfs() {
   std::string retValue = "";

   dfs(root, retValue);

   return retValue;
}

void BST::dfs(NodeBST* node, std::string& bstItems) {
   if(node != nullptr) {
      dfs(node->left, bstItems);

      bstItems.append(1, node->data);
      bstItems.append(" ");

      dfs(node->right, bstItems);
   }
}

bool BST::contains(NodeBST* node, const char data) const {
   bool returnValue = false;

   if (node == nullptr) {
      returnValue = false;
   } else if (data == node->data) {
      returnValue = true;
   } else {
      if (data < node->data) {
         returnValue = contains(node->left, data);
      } else {
         returnValue = contains(node->right, data);
      }
   }

   return returnValue;
}

NodeBST* BST::get(NodeBST* node, const char data) const {
   NodeBST* returnValue = nullptr;

   if (node == nullptr) {
      returnValue = nullptr;
   } else if (data == node->data) {
      returnValue = node;
   } else {
      if (data < node->data) {
         returnValue = get(node->left, data);
      } else {
         returnValue = get(node->right, data);
      }
   }

   return returnValue;
}

NodeBST* BST::add(NodeBST* node, const char data) {
   if (node == nullptr) {
      node = new NodeBST(data, nullptr, nullptr);
   } else {
      if (data < node->data) {
         node->left = add(node->left, data);

      } else {
         node->right = add(node->right, data);
      }
   }

   return node;
}

void BST::clear(NodeBST* node) {
    if(node != nullptr) {

        clear(node->left);
        clear(node->right);

        delete node;
    }
}

NodeBST* BST::FindMax(NodeBST* node) {
   NodeBST* retValue = nullptr;
   if (node == nullptr) {
      retValue = nullptr;
   } else {
      while (node->right != nullptr) {
         node = node->right;
      }
      retValue = node;
   }
   return retValue;
}

NodeBST* BST::remove(NodeBST* node, char data) {
   NodeBST* retValue = nullptr;
   
   if (node == nullptr) {
      retValue = nullptr;
   } else if (data < node->data) {
      node->left = remove(node->left, data);
      retValue = node;
   } else if (data > node->data) {
      node->right = remove(node->right, data);
      retValue = node;
   } else {
      if (node->right == nullptr && node->left == nullptr) {
         // node has no children
         delete node;
         node = nullptr;
      } else if (node->right == nullptr) {
         // node has 1 child on left
         NodeBST* temp = node;
         node = node->left;
         retValue = node;
         delete temp;
      } else if (node->left == nullptr) {
         // node has 1 child on right
         NodeBST* temp = node;
         node = node->right;
         retValue = node;
         delete temp;
      } else {
         // when node has 2 children find the max of left branch and move it up.
         NodeBST* temp = FindMax(node->left);
         node->data = temp->data;
         node->left = remove(node->left, temp->data);
         retValue = node;
      }
   }
   return retValue;
}