#ifndef TILE_BAG_H
#define TILE_BAG_H

#include "LinkedList.h"
#include "Types.h"

class TileBag {
public:
	TileBag();
	~TileBag();
	void addToBag(Colour tile);
	void removeFrontTile();

private:
	LinkedList* tileBag;
};

#endif // TILE_BAG_H