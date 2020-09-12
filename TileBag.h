#ifndef TILE_BAG_H
#define TILE_BAG_H

#include "LinkedList.h"

class TileBag {
public:
	TileBag();
	~TileBag();

	// Adds tiles to back of the queue
	void addToBag(char tile);

	// removes the tile at the front of the queue and returns the tile removed
	char removeFrontTile();

	int size();

	char at(int index);

private:
	// Where the tiles are stored
	LinkedList* tileBag;
};

#endif // TILE_BAG_H