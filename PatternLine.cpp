#include "PatternLine.h"
#include "Types.h"

PatternLine::PatternLine(int size):
	tile(EMPTY),
	size(size),
	currentSize(0) {
	this->tiles = new char[size];
}

PatternLine::~PatternLine() {
	delete[] this->tiles;
}

void PatternLine::setTile(char tile) {
	this->tile = tile;
}

char PatternLine::getTile() {
	return this->tile;
}