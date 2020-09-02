#ifndef PLAYER_BOARD_H
#define PLAYER_BOARD_H

class PatternLine;

class PlayerBoard {
public:
	PlayerBoard();
	~PlayerBoard();

	// Set the tile at wall position x, y
	void setWallTile(char tile, int x, int y);

	// Get the tile at wall position x, y
	char getWallTile(int x, int y);

private:
	// The Wall (2D 5x5 char array)
	char** wall;

	// Array of pattern line objects
	PatternLine** patternLines;

	// Broken Line

};

#endif