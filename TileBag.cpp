#include "TileBag.h"
#include "Types.h"

TileBag::TileBag() {
    this->tileBag = new LinkedList();
}

TileBag::~TileBag() {
    delete tileBag;
}

void TileBag::addToBag(char tile) {
    tileBag->addBack(tile);
}

char TileBag::removeFrontTile() {
    char retValue = tileBag->get(0);
    tileBag->removeFront();
    return retValue;
}