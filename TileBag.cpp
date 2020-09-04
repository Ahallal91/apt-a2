#include "TileBag.h"

TileBag::TileBag() {
    this->tileBag = new LinkedList();
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