#include "TileBag.h"
#include "Types.h"
#include "FileHandler.h"

//TODO overload constructor to take in a file (save file)
TileBag::TileBag() {
	this->tileBag = new LinkedList();
	FileHandler reader;
	reader.readTileBag(*this->tileBag, "TileBag.txt");
}

TileBag::~TileBag() {
	delete tileBag;
}

void TileBag::addToBag(char tile) {
	tileBag->addBack(tile);
}

char TileBag::removeFrontTile() {
	const unsigned int start = 0;
	char retValue = tileBag->get(start);
	tileBag->removeFront();
	return retValue;
}