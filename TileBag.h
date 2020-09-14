#ifndef TILE_BAG_H
#define TILE_BAG_H

#include "LinkedList.h"

class TileBag {
public:
	// default constructor
	TileBag();

	// reads tilebag string into tilebag
	// TileBag(std::string fileName);

	// copyConstructor
	TileBag(TileBag& other);

	// moveConstructor
	TileBag(TileBag&& other);

	// delete constructor
	~TileBag();

	// Adds tiles to back of the queue
	void addToBag(char tile);

	// removes the tile at the front of the queue and returns the tile removed
	char removeFrontTile();

	int size();

	char at(const unsigned int index) const;

private:
	// Where the tiles are stored
	LinkedList* tileBag;
};

#endif // TILE_BAG_H