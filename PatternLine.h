#include "Types.h"

#ifndef PATTERN_H
#define PATTERN_H

class PatternLine {
public:
	PatternLine(int size);
	~PatternLine();

	void setColour(Colour colour);
	Colour getColour();

private:
	// colour of this pattern line
	Colour colour;

	// size of the array
	int size;
	
	// current numTiles
	int currentSize;

	// 1d array of tiles
	char* tiles;
};


#endif // PATTERN_H