#ifndef TILE_BAG_H
#define TILE_BAG_H

#include "LinkedList.h"
#include "Types.h"

class TileBag {
public:
	TileBag();
	~TileBag();

	// Adds tiles to back of the queue
	void addToBag(char tile);

	// removes the tile at the front of the queue
	void removeFrontTile();

private:
	// Where the tiles are stored
	LinkedList* tileBag;
};

#endif // TILE_BAG_H