#ifndef PLAYER_BOARD_H
#define PLAYER_BOARD_H

#include <vector>
#include "PatternLine.h"

//class PatternLine;

class PlayerBoard {
public:
	PlayerBoard();
	~PlayerBoard();

    // WALL METHODS
	
	// Sets the tile at row position and colour of the tile (no need for x)
    bool setWallTile(int y, char tile);

	// Removes the tile at wall position x, y and sets it back to empty
	// void removeWallTile(int x, int y);

	// Returns the tile at wall position x, y
	char getWallTile(int x, int y);

	// PATTERN LINE METHODS

	// Returns the Pattern Line of a specific row
	PatternLine* getPatternLine(int row);

	// BROKEN LINE METHODS

	// Adds a tile to the end of the broken line if not full
	bool addBrokenTile(char tile);

	// Returns the tile at an index of the broken line
	char getBrokenTile(int index);

	// Returns the amount of tiles in the broken line
	int getBrokenSize();

	// Clears the broken tiles
	void clearBrokenLine();

private:
	// The Wall (2D 5x5 char array)
	char** wall;

	// Array of pattern line objects
	PatternLine** patternLines;

	// Broken Line
	std::vector<char>* brokenLine;

};

#endif