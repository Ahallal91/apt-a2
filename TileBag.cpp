#include "TileBag.h"
#include "FileHandler.h"

TileBag::TileBag() {
	this->tileBag = new LinkedList();
	this->tileBagString = "";
}

TileBag::TileBag(std::string fileName) {
 	this->tileBag = new LinkedList();
 	FileHandler reader;
 	reader.readTileBag(*this->tileBag, tileBagString, fileName);
}

TileBag::TileBag(const TileBag& other) {
	this->tileBag = new LinkedList(*other.tileBag);
}

TileBag::~TileBag() {
	delete tileBag;
}

void TileBag::addToBag(char tile) {
	tileBag->addBack(tile);
	tileBagString.append(1, tile);
}

char TileBag::removeFrontTile() {
	char retValue = tileBag->front();
	tileBag->removeFront();
	return retValue;
}

std::string TileBag::initialTileBagString() {
	return tileBagString;
}