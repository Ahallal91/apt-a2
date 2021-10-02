#ifndef SINGLE_FACTORY_H
#define SINGLE_FACTORY_H

#include <string>

class BST;

class SingleFactory {
public:

    SingleFactory();
    ~SingleFactory();

    void clear();

    bool contains(const char tile) const;

    // you cannot add more then 4 items in a factory. Defensive: Must be a valid tile
    bool add(const char tile);

    // remove item from the factory. Factory cannot be empty.
    bool remove(const char tile);

    char get(const char tile) const;

    int length();

    // returns true if the size is 0 and there are no remaining chars.
    bool empty();

    // returns the top tile left in the factory.
    char getRemaining();

    // returns a string of characters in the factory
    std::string toString();

    // returns the amount of a type of tile there is
    int getTileCount(const char tile);
private:
    BST* singleFactory;
    int size;
};

#endif // SINGLE_FACTORY_H