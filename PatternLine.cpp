#include "PatternLine.h"
#include "Types.h"

PatternLine::PatternLine(int size):
	tile(EMPTY),
	size(size),
	currentSize(0) {
	this->tiles = new char[size];

	// Initialise all tiles to empty tiles
	for(int i = 0; i < size; i++) {
		tiles[i] = EMPTY;
	}
}

PatternLine::~PatternLine() {
	delete[] this->tiles;
}

void PatternLine::setTileType(char tile) {
	this->tile = tile;
}

char PatternLine::getTileType() {
	return this->tile;
}

bool PatternLine::addTile(char tile) {
	bool success = false;

	if(currentSize < size) {
		tiles[currentSize] = tile;
		currentSize++;
		success = true;
	}

	return success;
}

void PatternLine::removeTile(int index) {
	if(index >= 0 && index < currentSize) {
		tiles[index] = EMPTY;
		currentSize--;
	}
}

char PatternLine::getTile(int index) {
	char tile = '\0';

	if(index >= 0 && index < size) {
		tile = tiles[index];
	}

	return tile;
}

int PatternLine::getSize() {
	return this->size;
}

int PatternLine::getCurrentSize() {
	return this->currentSize;
}