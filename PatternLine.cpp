#include "PatternLine.h"

PatternLine::PatternLine(int size):
	colour(NO_COLOUR),
	size(size),
	currentSize(0) {
	this->tiles = new char[size];
}

PatternLine::~PatternLine() {
	delete[] this->tiles;
}

void PatternLine::setColour(Colour colour) {
	this->colour = colour;
}

Colour PatternLine::getColour() {
	return this->colour;
}