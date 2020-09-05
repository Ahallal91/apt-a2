#include "TileBag.h"
#include "Types.h"
#include "Reader.h"

//TODO overload constructor to take in a file (save file)
TileBag::TileBag() {
	this->tileBag = new LinkedList();
	Reader reader;
	reader.readTileBag(*this->tileBag, "TileBag.txt");
}

TileBag::~TileBag() {
	delete tileBag;
}

void TileBag::addToBag(char tile) {
	tileBag->addBack(tile);
}

void TileBag::removeFrontTile() {
	tileBag->removeFront();
}