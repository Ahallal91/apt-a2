#ifndef TILE_BAG_H
#define TILE_BAG_H

#include "LinkedList.h"
#include <string>

class TileBag {
public:
	// default constructor to create an empty tile bag
	TileBag();

	// constructor to create a tile bag from a file
	TileBag(std::string fileName);

	// copyConstructor
	TileBag(TileBag& other);

	// delete constructor
	~TileBag();

	// Adds tiles to back of the queue
	void addToBag(char tile);

	// removes the tile at the front of the queue and returns the tile removed
	char removeFrontTile();

	// returns the current tilebag as a string;
	std::string toString();

private:
	// Where the tiles are stored
	LinkedList* tileBag;
};

#endif // TILE_BAG_H