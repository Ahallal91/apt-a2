#include "TileBag.h"
#include "Types.h"
#include "FileHandler.h"

TileBag::TileBag() {
	this->tileBag = new LinkedList();
}

TileBag::TileBag(std::string fileName) {
 	this->tileBag = new LinkedList();
 	FileHandler reader;
 	reader.readTileBag(*this->tileBag, fileName);
}

TileBag::TileBag(TileBag& other) {
	this->tileBag = new LinkedList(*other.tileBag);
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

std::string TileBag::toString() {
	std::string retValue = "";
	for(unsigned int i = 0; i < tileBag->size(); ++i) {
		retValue += tileBag->get(i);
	}
	return retValue;
}