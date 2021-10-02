#ifndef PLAYER_BOARD_H
#define PLAYER_BOARD_H

#include <vector>
#include <map>
#include <tuple>
#include "PatternLine.h"

// Broken Line config
#define NUM_BROKEN_TILES		7 
#define ADV_NUM_BROKEN_TILES	8

class PlayerBoard {
public:
	PlayerBoard();
	PlayerBoard(PlayerBoard& other);
	PlayerBoard(PlayerBoard&& other);
	~PlayerBoard();

	// toggle for advanced and greyboard mode.
	PlayerBoard(bool advancedMode, bool greyBoard);
	// WALL METHODS

	// Sets the tile at wall position x, y to the corresponding pattern tile
	bool setWallTile(int x, int y, char tile);

	// Removes the tile at wall position x, y and sets it back to empty
	void removeWallTile(int x, int y);

	// Returns the tile at wall position x, y
	char getWallTile(int x, int y);

	// Returns the best place to put a tile to get combo points for AI mode.
	// it also returns the tiles colour.
	std::tuple<int, int, char> getWallCombo(int y, int previousX);

	// Returns false if tile passed in matches any in the same column
	// used for greyBoard mode.
	bool checkWallCol(int x, char tile); 
	// PATTERN LINE METHODS

	// Returns the Pattern Line of a specific row
	PatternLine* getPatternLine(int row);
	
	// returns a map of weighted by size patternLines for AI mode.
	std::map<int, int> getAvailablePatternLines();

	// BROKEN LINE METHODS

	// Adds a tile to the end of the broken line if not full
	bool addBrokenTile(char tile);

	// Returns the tile at an index of the broken line
	char getBrokenTile(int index);

	// Returns true if the players broken line contains the FIRST tile
	bool brokenLineHasFirst();
	
	// Returns the amount of tiles in the broken line
	int getBrokenSize();

	// Clears the broken tiles
	void clearBrokenLine();

	// clears the playerWall
	void clearPlayerWall();

private:
	// returns a tuple of the pattern wall at x, y co-ords. used in getWallCombo method.
	std::tuple<int, int, char> getWallCharForCombo(int y, int x);
	// The Wall (2D 5x5 char array)
	char** wall;

	// Array of pattern line objects
	PatternLine** patternLines;

	// Broken Line
	std::vector<char>* brokenLine;

	// wallSize
	int wallSize;

	// broken Tiles
	int numBrokenTiles;

	// toggle for greyboard mode
	bool greyBoard;

	// toggle for advanced mode;
	bool advancedMode;
};

#endif