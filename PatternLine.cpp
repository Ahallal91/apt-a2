#include "PatternLine.h"
#include "Types.h"

PatternLine::PatternLine(int size):
	tile(EMPTY),
	size(size),
	currentSize(0) {
	this->tiles = new char[size];

	// Initialise all tiles to empty tiles
	for (int i = 0; i < size; i++) {
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

	if (currentSize < size) {
		if (currentSize == 0 && tile != FIRST) {
			this->tile = tile;
		}
		if(this->tile == tile) {
			tiles[currentSize] = tile;
			currentSize++;
			success = true;
		}
	}
	return success;
}

void PatternLine::removeTile(int index) {
	if (index >= 0 && index < currentSize) {
		tiles[index] = EMPTY;
		currentSize--;
	}
}

int PatternLine::getSize() {
	return this->size;
}

int PatternLine::getCurrentSize() {
	return this->currentSize;
}

bool PatternLine::isFull() {
	return (currentSize == size);
}

void PatternLine::clear() {
	for (int i = 0; i < currentSize; ++i) {
		tiles[i] = EMPTY;
	}
	currentSize = 0;
}
