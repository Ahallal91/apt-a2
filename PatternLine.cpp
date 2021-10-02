#include "PatternLine.h"
#include "Types.h"

PatternLine::PatternLine(int size):
	tile(EMPTY),
	size(size),
	currentSize(0) {
	this->tiles = new char[size];

	this->clear();
}

PatternLine::PatternLine(PatternLine& other) {
	this->tile = other.tile;
	this->size = other.size;
	this->currentSize = other.currentSize;
	this->tiles = new char[size];
	for(int i = 0; i < size; ++i) {
		tiles[i] = other.tiles[i];
	}
}

PatternLine::PatternLine(PatternLine&& other) {
	this->tile = other.tile;
	this->size = other.size;
	this->currentSize = other.currentSize;
	this->tiles = new char[size];
	for(int i = 0; i < size; ++i) {
		tiles[i] = other.tiles[i];
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
		if (this->tile == tile) {
			tiles[currentSize] = tile;
			currentSize++;
			success = true;
		}
	}
	return success;
}

int PatternLine::getSize() {
	return this->size;
}

int PatternLine::sizeDifference() {
	return size - (currentSize);
}

int PatternLine::getCurrentSize() {
	return this->currentSize;
}

bool PatternLine::isFull() {
	return currentSize == size;
}

// clears the pattern line
void PatternLine::clear() {
	for (int i = 0; i < size; i++) {
		tiles[i] = EMPTY;
	}
	this->currentSize = 0;
	this->setTileType(EMPTY);
}